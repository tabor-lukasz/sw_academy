#include "judge.h"
#include <iostream>
#include <string>
#include <set>

#include <fstream>
#include <chrono>

using namespace std;

string testCases = "abcdeX";
//string testCases = "c";
string testCasePrefix = "res/SUD0";
string testCaseSuffixIn = ".in";
string testCaseSuffixOut = ".out";

void Judge::run(ISUD *solution) {
    for (auto cc : testCases) {

        auto begin = std::chrono::high_resolution_clock::now();

        ifstream ins(testCasePrefix + cc + testCaseSuffixIn);
        ifstream outs(testCasePrefix + cc + testCaseSuffixOut);

        int mode; ins >> mode;

        int board[9][9];

        for (int i=0; i<9; ++i) {
            string s; ins >> s;
            for (int j=0; j<9; ++j) board[i][j] = s[j] - '0';
        }

        solution->solve(board);

        string ss;

        string expected[9];

        for (int i=0; i<9; ++i) {
//            for (int j=0; j<9; ++j) {
                outs >> expected[i];
//            }
        }

        bool print = false;

        for (int i=0; i<9; ++i) {
            for (int j=0; j<9; ++j) {
                if ((expected[i][j] - '0') != board[i][j]) {
                    print = true;
//                    cout << cc << " " << i << " " << j << endl;
                }
            }
        }

        if (print) {
            for (int i=0; i<9; ++i) {
                for (int j=0; j<9; ++j) {
                    cout << expected[i][j] << " ";
                }
                cout << " ";
                for (int j=0; j<9; ++j) {
                    cout << board[i][j] << " ";
                }

                cout << " ";
                for (int j=0; j<9; ++j) {
                    cout << expected[i][j] - board[i][j] - '0'<< " ";
                }
                cout << endl;
            }
        }
        else {
            auto end = std::chrono::high_resolution_clock::now();
            cout << cc << " OK " << std::chrono::duration_cast<chrono::milliseconds>(end-begin).count() <<endl;
        }
    }

}

