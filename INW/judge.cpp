#include "judge.h"
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

namespace {

class MyTimer {
public:
    MyTimer(const string& _name) : name(_name) {
        start = chrono::high_resolution_clock::now();
    }

    MyTimer(char _name) {
        name = _name;
        start = chrono::high_resolution_clock::now();
    }

    ~MyTimer() {
        cout << name << " " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
    }
private:
    string name;
    chrono::time_point<chrono::high_resolution_clock> start;
};

//string TestCases = "b";
string TestCases = "abc";
string TestCasePrefix = "res/INW0";
string TestCaseSuffixIn = ".in";
string TestCaseSuffixOut = ".out";

int mode;
int map[1000][1000];

void generateMap(int h, int w, ifstream& ins) {
    for (int i=0; i<h; ++i) for (int j=0; j<w; ++j) {
        ins >> map[i][j];
    }
}

void singleCase(IINW *sol, int nr, ifstream& ins, ifstream& outs) {
    int h; ins >> h;
    int w; ins >> w;
    generateMap(h, w,ins);

    if (nr == 4) {
        int aaa = 0;
    }

    sol->init(h, w, map);
    int res1 = sol->getInvasionDuration();
    int res2 = sol->getFinalArea();

    string sss;
    int duration;
    int area;
    outs >> sss >> duration >> area;

    if (res1 != duration || res2 != area) {
        cout << "#" << nr << ": " << res1 << "/" << duration << " " << res2 << "/" << area << endl;;
    } else {
        cout << "#" << nr << " OK" << endl;;
    }
}

} // namespace

void Judge::run(IINW *solution) {

    for (auto cc : TestCases) {
        ifstream ins(TestCasePrefix + cc + TestCaseSuffixIn);
        ifstream outs(TestCasePrefix + cc + TestCaseSuffixOut);

        MyTimer timer(cc);

        ins >> mode;
        int tc; ins >> tc;

        for (int i=0; i<tc; ++i)
            singleCase(solution, i+1,ins,outs);
    }
}

