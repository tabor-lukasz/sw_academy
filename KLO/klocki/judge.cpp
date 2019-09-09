#include "judge.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <chrono>

string TestPrefix = "data/KLO0";
string TestCases= "abcde";
//string TestCases= "a";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

namespace {
const int N = 7;
int a[N];
int b[N];
int c[N];
}

void Judge::run(IKLO *solution) {

    for (auto testCase : TestCases) {
        auto begin = chrono::high_resolution_clock::now();
        ifstream ins(TestPrefix + testCase + TestSuffixIn);
        ifstream outs(TestPrefix + testCase + TestSuffixOut);
        int tc; ins >> tc;
        for (int t=0; t<tc; ++t) {
            int n; ins >> n;
            for (int i=0; i<n; ++i) {
                ins >> a[i];
                ins >> b[i];
                ins >> c[i];
            }
            int res = solution->maxTowerHeight(n, a, b, c);
            int expected;
            string str;
            outs >> str;
            outs>> expected;
            if (res != expected)
                cout << testCase << t<< " #" << t << ": " << res << " " << expected << endl;
            else {
//                cout << testCase << t<< " #" << t << ": OK" << endl;
            }
        }

        auto end = chrono::high_resolution_clock::now();

        cout << testCase << "\t" << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << endl;
    }
}

