#include "judge.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <tgmath.h>

#define DBG
using namespace std;

namespace {

string TestPrefix = "res/PYS0";
//string TestCases= "abcdefghx";
string TestCases= "x";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

long long seed;
int pseudoRand() {
    seed = seed * 13477581 + 1;
    return (seed & 0x7fffffff) % 1000000007;
}

int pancakes[MAX_N];
int pancakesOrg[MAX_N];
int moves[MAX_MOVES];

void randomShuffle(int n) {
    for (; n>1; --n) {
        int pos = pseudoRand() % n;
        int tt = pancakes[pos];
        pancakes[pos] = pancakes[n-1];
        pancakes[n-1] = tt;
    }
}

bool partialVerify(int n, int cnt) {
    int x = 1 + (pseudoRand() % n);
    int y = x;
    while (x == y)
        y = 1 + (pseudoRand() % n);

    int posx = -1;
    int posy = -1;
    for (int i=0; i<n; ++i) {
        if (pancakesOrg[i] == x) posx = i;
        if (pancakesOrg[i] == y) posy = i;
    }

    for (int i=0; i<cnt; ++i) {
        if (posx >= moves[i])
            posx = n - 1 + moves[i] - posx;
        if (posy >= moves[i])
            posy = n - 1 + moves[i] - posy;
    }

    if (x + posx != n || y + posy != n) {
        cout << "Error. Pancakes are not sorted!\n";
        return false;
    }
    return true;
}

void changeSeed() {
    // THE BODY OF THIS FUNCTION CAN BE DIFFERENT IN FINAL JUDGE
}

void verify(int n, int cnt) {
    // THE BODY OF THIS FUNCTION CAN BE DIFFERENT IN FINAL JUDGE
    static vector<int> v;
    if (v.empty()) {
        v.reserve(200000);
    }

    if (n > 0) {
    } else {
        v.push_back(0);
        for (int i=0; i<(int)v.size(); ++i)
            cout << v[i] << " ";
        cout << "\n";
    }
}

} // namespace

void Judge::run(IPYS *solution) {

    for (auto cc : TestCases) {

        auto begin = chrono::high_resolution_clock::now();

        ifstream ins(TestPrefix + cc + TestSuffixIn);
        ifstream outs(TestPrefix + cc + TestSuffixOut);

        int mode; ins >> mode;
        int TC; ins >> TC;
        int n; ins >> n;
        ins >> seed;
//        seed = 12346;
        changeSeed();

        vector<int> fullVerify(TC, 0);
        fullVerify[pseudoRand() % TC] = 1;
        fullVerify[pseudoRand() % TC] = 1;
        fullVerify[pseudoRand() % TC] = 1;

        long long hhash = 0;
        for (int tc=0; tc<TC; ++tc) {
//            if (tc % 100 == 0) {
//                cout << tc << endl;
//            }
            for (int i=0; i<n; ++i)
                pancakes[i] = i+1;
            randomShuffle(n);
            for (int i=0; i<n; ++i)
                pancakesOrg[i] = pancakes[i];
            int cnt = solution->sortPancakes(n, pancakes, moves);
            if (cnt < 0 || cnt > MAX_MOVES) {
                cout << "Error. Number of moves negative or exceeds the limit.\n";
                continue;
            }
            if (fullVerify[tc] != 0)
                verify(n, cnt);

            hhash = (hhash * 10007 + (partialVerify(n, cnt) ? (tc+1) : 0)) % 1000000007;
        }
        long long expected;
        string ss;
        outs >> ss;
        outs >> expected;
        //cout << "Final hash: " << hhash << "\n";
        if (expected != hhash) {
            cout << "Final hash: " << hhash << " " << expected << endl;
        }
//        verify(0, 0);

        auto end = chrono::high_resolution_clock::now();

//        cout << cc << " Time: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << endl;
        cout << TC * log2(TC) << " " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count()/1000000.0 << endl;
    }
}

