#include "judge.h"
#include <iostream>
#include <fstream>

using namespace std;

string testCaseIn = "res/KAP0.in";
string testCaseOut = "res/KAP0.out";

void judge::run(IKAP* solution) {

    ifstream ins(testCaseIn);
    ifstream outs(testCaseOut);

    int T;
    ins >> T;
    int n;
    int data[20][5];
    for (int t = 1; t <= T; ++t) {
        ins >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 5; ++j) {
                ins >> data[i][j];
            }
        }

        int expected;
        string sss;
        outs >> sss;
        outs >> expected;
        int res = solution->maxScore(n,data);
        if (expected != res )
            cout << "#" << t << " " << expected << "\t" << res << endl;
        else {
            cout << "#" << t << " OK" << endl;
        }
    }
}
