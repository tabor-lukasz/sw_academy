#include "judge.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

namespace {

int mode;

int population;
int queryCount;
int nextQuery;
char names[32768][16];
char logins[65536][8];
char buf[32];
char testCase[] = "IMI0j";
char answers[32768][16];

void init() {
    static bool doInit = true;
    if (doInit == false) return;
    doInit = false;
    std::string inFile = testCase;
    inFile += ".in";
    ifstream input(inFile);
    input >> mode >> population >> queryCount;
    for (int i=0; i<population; ++i) {
        input >> buf;
        for (int j=0; j<16; ++j) names[i][j] = buf[j];
    }
    for (int i=0; i<queryCount; ++i) {
        input >> buf;
        for (int j=0; j<8; ++j) logins[i][j] = buf[j];
    }

    std::string outFile = testCase;
    outFile += ".out";
    ifstream output(outFile);

    for (int i=0; i<queryCount; ++i) {
        output >> buf;
        for (int j=0; j<16; ++j) answers[i][j] = buf[j];
    }

} // init()

} // namespace

void re_init(int l_div, int n_div, int l_rnd, int n_rnd ) {
    nextQuery = 0;
    population = 32768/n_div;
    queryCount = 65536/l_div;

    for (int i = 0; i < population; i++) {

        for (int j=0; j<n_rnd; ++j)  {
            names[i][j] = std::rand() % 26 + 'a';
        }

        for (int j=n_rnd; j<16; ++j)  {
            names[i][j] = 'f';
        }

    }

    for (int i = 0; i < queryCount; i++) {
        //        for (int j=0; j<8; ++j) logins[i][j] = 'd';

        for (int j=0; j<l_rnd ; ++j)  {
            logins[i][j] = std::rand() % 26 + 'a';
        }

        for (int j=l_rnd; j<8; ++j)  {
            logins[i][j] = 'd';
        }
    }
}

int Judge::getPopulation() {
    init();
    return population;
}

void Judge::getCitizenName(int id, char *name) {
    init();
    for (int i=0; i<16; ++i)
        name[i] = names[id][i];
}

int Judge::getQueryCount() {
    init();
    return queryCount;
}

void Judge::getCitizenLogin(char *login) {
    init();
    for (int j=0; j<8; ++j)
        login[j] = logins[nextQuery][j];
    ++nextQuery;
}

void Judge::replyCitizenName(char *name) {
//    init();
//    for (int j=0; j<16; ++j)
//        if (answers[nextQuery - 1][j] != name[j]) {
//            cout << "-" << endl;
//            string login(logins[nextQuery-1],8);
//            string ss_ok(answers[nextQuery - 1],16);
//            string ss_bad(name,16);
//            cout << login << endl;
//            cout << ss_ok << endl;
//            cout << ss_bad << endl;
//            return;
//        }
//    for (int i = 0; i < 16; ++i) {
//        cout << name[i];
//    }
//    cout <<" OK" << endl;
}

