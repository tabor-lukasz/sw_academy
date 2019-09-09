#include "judge.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <set>
#include <random>

using namespace std;

string testCases = "";
string testCasePrefix = "res/NAD0";
string testCaseSuffixIn = ".in";
string testCaseSuffixOut = ".out";


namespace {

long long cost[15][8];

} // namespace

void Judge::run(INAD *solution) {

    auto begin = std::chrono::high_resolution_clock::now();

    ifstream ins(testCasePrefix + testCaseSuffixIn);
    ifstream outs(testCasePrefix + testCaseSuffixOut);

    int mode; ins >> mode;

    int tc; ins >> tc;

    for (int t=1; t<=tc; ++t) {
        int n; ins >> n;
        int k; ins >> k;
        for (int i=0; i<n; ++i) for (int j=0; j<k; ++j) ins >> cost[i][j];

        long long res = solution->getMinimumCost(n, k, cost);

        string txt;
        outs >> txt;
        int expected;
        outs >> expected;
        if (res != expected) {
            cout << "#" << t << " " << res << " " << expected << endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    cout << "time: " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;

    {
        string tc = "XXX1";
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 15; ++j) {
                cost[j][i] = j + 1;
            }
        }

        auto res = solution->getMinimumCost(15,8,cost);
        auto expected = 36;
        if (res != expected) {
            cout << "#" << tc << " " << res << " " << expected << endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        cout << tc << " " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;
    }

    {
        string tc = "XXX2";
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 15; ++j) {
                cost[14-j][i] = j + 1;
            }
        }

        auto res = solution->getMinimumCost(15,8,cost);
        auto expected = 36;
        if (res != expected) {
            cout << "#" << tc << " " << res << " " << expected << endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        cout << tc << " " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;
    }

    {
        string tc = "XXX3";
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 15; ++j) {
                cost[j][7-i] = j + 1;
            }
        }

        auto res = solution->getMinimumCost(15,8,cost);
        auto expected = 36;
        if (res != expected) {
            cout << "#" << tc << " " << res << " " << expected << endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        cout << tc << " " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;
    }

    {
        string tc = "XXX4";
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 15; ++j) {
                cost[14-j][7-i] = j + 1;
            }
        }

        auto res = solution->getMinimumCost(15,8,cost);
        auto expected = 36;
        if (res != expected) {
            cout << "#" << tc << " " << res << " " << expected << endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        cout << tc << " " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;
    }

    {
        string tc = "YYY1";
        srand(time(0));
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 15; ++j) {
                cost[j][i] = rand();
            }
        }

        auto res = solution->getMinimumCost(15,8,cost);
//        auto expected = 36;
//        if (res != expected) {
//            cout << "#" << tc << " " << res << " " << expected << endl;
//        }

        auto end = std::chrono::high_resolution_clock::now();
        cout << tc << " " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;
    }


}

