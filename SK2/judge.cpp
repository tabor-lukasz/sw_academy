#include "judge.h"
#include <iostream>
#include <iomanip>

#include <fstream>
#include <chrono>

#define DBG


using namespace std;

namespace {

long long seed;
int pseudo_rand() {
    seed = seed * 13477581 + 1;
    return (seed & 0x7FFFFFFF) % 1000000007;
}

int db[100][100][100];
int q[8][8];
const int mod = 256;

const int MAX_QUERY_COUNT = 500000;

string TestPrefix = "res/SK20";
//string TestCases= "abcdefg";
string TestCases= "z";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

} // namespace

void Judge::run(ISK2 *solution) {

    for (auto cc : TestCases) {

        auto begin = chrono::high_resolution_clock::now();

        ifstream ins(TestPrefix + cc + TestSuffixIn);
        ifstream outs(TestPrefix + cc + TestSuffixOut);

        ins >> seed;
        int count; ins >> count;
        if (count > MAX_QUERY_COUNT) {
            cerr << "Input data corrupted. Given query count: " << count << "\n";
            exit(1);
        }
        for (int i=0; i<100; ++i)
            for (int j=0; j<100; ++j)
                for (int k=0; k<100; ++k)
                    db[i][j][k] = pseudo_rand() % mod;

#ifdef DBG
        auto begin1 = chrono::high_resolution_clock::now();
#endif
        solution->database(db);
#ifdef DBG
        auto end1 = chrono::high_resolution_clock::now();
#endif

        long long hash1 = 123987;
        long long hash2 = hash1;
        for (int tc=0; tc<count; ++tc) {

            int id = pseudo_rand() % 100;
            int x = pseudo_rand() % 93;
            int y = pseudo_rand() % 93;
            for (int i=0; i<8; ++i) {
                for (int j=0; j<8; ++j) {
                    q[i][j] = db[id][x+i][y+j];
//                    std::cout << setw(4)<< q[i][j];;
                }
//                std::cout << std::endl;
            }
//            std::cout << std::endl;


            x = pseudo_rand() % 4;
            y = pseudo_rand() % 4;
            for (int i=0; i<5; ++i)
                for (int j=0; j<5; ++j)
                    q[x+i][y+j] = pseudo_rand() % mod;

//            for (int i=0; i<8; ++i) {
//                for (int j=0; j<8; ++j) {
//                    std::cout << setw(4) << q[i][j];
//                }
//                std::cout << std::endl;
//            }
//            std::cout << std::endl;

            int result = solution->query(q);

            if (id != result) {
                cout << tc << endl;;
            }

            hash1 = (hash1 * 1337 +     id) % 1000000007;
            hash2 = (hash2 * 1337 + result) % 1000000007;
        }

        if (hash1 == hash2) {
#ifdef DBG
            cout << "Solution correct! Congratulations! " << hash2 << endl;
#endif
        } else {
            cout << "Something went wrong! Try again... " << hash2 << endl;
        }

        auto end = chrono::high_resolution_clock::now();
#ifdef DBG
        cout << "Time1: " << dec << cc << "\t" << chrono::duration_cast<chrono::milliseconds>(end1-begin1).count() << endl;
#endif
        cout << "Time: " << dec << cc << "\t" << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << endl;

    }
}

