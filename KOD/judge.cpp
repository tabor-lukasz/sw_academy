#include "judge.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

string testCases = "abcdef";
string testCasePrefix = "res/KOD0";
string testCaseSuffixIn = ".in";
string testCaseSuffixOut = ".out";

void judge::run(iKOD *k)
{
    for (auto cc : testCases) {
        auto begin = std::chrono::high_resolution_clock::now();

        ifstream ins(testCasePrefix +cc+ testCaseSuffixIn);
        ifstream outs(testCasePrefix +cc+ testCaseSuffixOut);

        int typ;
        ins >> typ;
        int n, codeLengths[20];
        ins >> n;
        for (int i = 0; i < n; ++i)
          ins >> codeLengths[i];

        long long expected;
        outs >> expected;
        auto res = k->countCodes(n, codeLengths);

        auto end = std::chrono::high_resolution_clock::now();

        if (res != expected) {
            cout << cc << " " << res << " " << expected << endl;
        } else {
            cout << cc << " " << res <<" OK " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
        }
    }
}
