#include "judge.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

string cases = "abcd";
//string cases = "b";
string prefix = "res/TWO0";
string suffixIn = ".in";
string suffixOut = ".out";

namespace {

const int MAX_N = 128;
const int MAX_SUM = 32768;

int n;
int h[MAX_N];

} // namespace


void Judge::run(ITWO *solution) {
    for (auto cc : cases) {
        auto begin = chrono::high_resolution_clock::now();
        ifstream ins(prefix + cc + suffixIn);
        ifstream outs(prefix + cc + suffixOut);

        int mode; ins >> mode;
        int tc; ins >> tc;

        for (int x=0; x<tc; ++x) {
            ins >> n;
            for (int i=0; i<n; ++i) ins >> h[i];
//            if (x < 2) {
//                int expected;
//                outs >> expected;
//                continue;
//            }
            int res = 0;
            if (3 != mode) { // 3 <=> Java
                res = solution->getMaxTowerHeight(n, h);
                int expected;
                outs >> expected;
                if (res != expected) {
                    cout  << cc << " " << x << " " << res <<  " " << expected << endl;
                } else {
//                    cout  << cc << " " << x << " OK."<< endl;
                    }
            }
//            return;
        }

        auto end = chrono::high_resolution_clock::now();
        cout << cc << " " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
    }
}

