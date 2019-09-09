#include "judge.h"
#include <iostream>
#include <string>
#include <set>

#include <fstream>
#include <chrono>

using namespace std;

namespace {

	char info[MAX_INFO_LEN];
	char info2[MAX_INFO_LEN];

} // namespace

string testCases = "";
string testPrefix = "res/DRZ0";
string testSuffixIn = ".in";
string testSuffixOut = ".out";


void Judge::run(IDRZ *solution) {

    ifstream ins(testPrefix + testSuffixIn);
    ifstream outs(testPrefix + testSuffixOut);

    auto begin = chrono::high_resolution_clock::now();

    int mode; ins >> mode;

	while (true) {
        int cmd; ins >> cmd;
		if (0 == cmd) {
			break;
		} else if (1 == cmd) {
            ins >> info;
			int res = solution->addCitizenInfo(info);

            int expected;
            outs >> expected;

            if (res != expected) {
                cout << res << " " << expected << endl;
            }
		} else if (2 == cmd) {
            ins >> info;
			int res = solution->delCitizenInfo(info);

            int expected;
            outs >> expected;

            if (res != expected) {
                cout << res << " " << expected << endl;
            }
		} else if (3 == cmd) {
            ins >> info;
            ins >> info2;
			solution->modifyCitizen(info, info2);
		} else if (4 == cmd) {
            ins >> info;
			int res = solution->familyMemberCount(info);

            int expected;
            outs >> expected;

            if (res != expected) {
                cout << res << " " << expected << endl;
            }
		}
	}

    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
}

