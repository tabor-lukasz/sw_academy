#include "judge.h"
#include <iostream>
#include <fstream>

#include <chrono>
#include <algorithm>

using namespace std;

const int MAX_WORKSHOPS = 5;

const string TestPrefix = "WAR0";
string TestName = "a";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

static char levelch[] = {'e','x','p','e','r','t',0};

struct uuser {
    char* level = levelch;
    int prefs[5] = {0,1,2,3,4};
    int id;
};

static uuser users[500000];
static int random1[500000];
static int random2[500000];


static int callsNum = 0;
static int workshopsNum = 0;
static int maxParticipants = 0;

int testCase = 3;
int subCase = 2;

void setTestCase(int nr) {
    testCase = nr/10;
    subCase = nr % 10;

    if (testCase == 0) {
        if (subCase == 0) {
            TestName = "a";
        }

        if (subCase == 1) {
            TestName = "b";
        }

        if (subCase == 2) {
            TestName = "c";
        }
    }
}

static const char* levels[] = {"expert", "pro", "adv", "int", "non"};


long judge::run(iWAR *w)
{
    for (int i = 0; i < 500000; i++) {
        users[i].id = 20000000 - i;
        if (testCase == 2) {
            random1[i] = i;
            random2[i] = i;
            users[i].level = const_cast<char*>(levels[rand() % 5]);
        } else {
            users[i].level = const_cast<char*>(levels[0]);
        }

        if (testCase == 3) {
            for (int j = 0; j <5; ++j) {
                if (i < 100000) {
                    users[i].prefs[j] = j;
                }

                if (i >= 100000 && i < 200000) {
                    users[i].prefs[j] = j;
                }

                if (i >= 200000 && i < 300000) {
                    users[i].prefs[j] = (j + 1) % 5;
                }

                if (i >= 300000) {
                    users[i].prefs[j] = j;
                }

            }
        } else {
            for (int j = 0; j <5; ++j) {
                users[i].prefs[j] = j;
            }
        }
    }

    auto begin = chrono::steady_clock::now();

    int cnt = 0;
    if (testCase == 0) {
        ifstream ins(TestPrefix + TestName + TestSuffixIn);
        ifstream outs(TestPrefix + TestName + TestSuffixOut);
        int typ;
        ins >> typ;
        ins >> workshopsNum >> maxParticipants >> callsNum;
        w->init(workshopsNum, maxParticipants);
        for (int i = 0; i < callsNum; ++i) {
            if (i == 200001) {
                int www = 0;
            }
            int result;
            int answer;
            outs >> answer;
            int op;
            ins >> op;
            if (op == 0) {
                int byteid;
                char level[15];
                int preferences[MAX_WORKSHOPS];
                ins >> byteid >> level;
                for (int j = 0; j < workshopsNum; ++j)
                    ins >> preferences[j];
                result = w->registration(byteid, level, preferences);
            } else {
                int byteid;
                ins >> byteid;
                result = w->unregistration(byteid);
            }

            if (result != answer) {
                cout <<"WRONG:    " << i << ": " << "expected: " << answer << "\t" << "got: " << result << endl;
            } else {
                ++cnt;
//                cout << i << " OK" << endl;
            }
        }
    }

    if (testCase == 1) {
        callsNum = 500000;
        cnt = callsNum;
        workshopsNum = 5;
        maxParticipants = 100000;
        w->init(workshopsNum, maxParticipants);

        for (int i = 0; i < callsNum/2; ++i) {
            if (subCase == 0 || subCase == 1) {
                auto res = w->registration(users[250000 -1 - i].id,users[i].level,users[i].prefs);
                if (res != (i/100000)) {
                    cout << i << endl;
                    --cnt;
                }
            } else {
                auto res = w->registration(users[i].id,users[i].level,users[i].prefs);
                if (res != 0) {
                    cout << i << endl;
                    --cnt;
                }
            }
        }

        for (int i = 0; i < callsNum/2; ++i) {
            if (subCase == 1 || subCase == 2) {
                auto res = w->unregistration(users[250000-1-i].id);
                if (res != 0) {
                    cout << i << endl;
                    --cnt;
                }
            } else {
                auto res = w->unregistration(users[i].id);
                if (res != ((250000-1-i)/100000)) {
                    cout << i << endl;
                    --cnt;
                }
            }
        }
    }

    if (testCase == 2) {
        std::srand(std::time(0));
        random_shuffle(random1,random1+250000-1);
        random_shuffle(random2,random2+250000-1);
        callsNum = 500000;
        cnt = callsNum;
        workshopsNum = 5;
        maxParticipants = 100000;
        w->init(workshopsNum, maxParticipants);

        for (int i = 0; i < callsNum/2; ++i) {
            //            if (787 == i) {
            //                int aaa = 0;
            //            }
//                        cout << i << endl;
            auto res = w->registration(users[random1[i]].id,users[i].level,users[i].prefs);
        }

        for (int i = 0; i < callsNum/2; ++i) {
            //            cout << i + callsNum/2 << endl;
            auto res = w->unregistration(users[random2[i]].id);
        }
    }

    if (testCase == 3) {
        callsNum = 500000;
        cnt = callsNum;
        workshopsNum = 5;
        maxParticipants = 100000;
        w->init(workshopsNum, maxParticipants);

        for (int i = 0; i < 100000; ++i) {
            auto res = w->registration(users[500000-i-1].id,users[i].level,users[i].prefs);
            if (res != 0) {
                cout << i << endl;
                --cnt;
            }
        }

        for (int i = 0; i < 100000; ++i) {
            auto res = w->registration(users[250000-i-1].id,users[i].level,users[i].prefs);
            if (res != 1) {
                cout << i << endl;
                --cnt;
            }
        }

        auto res = w->registration(users[0].id,users[0].level,users[0].prefs);
        if (res != 2) {
            cout <<" XXX " << endl;
            --cnt;
        }
        res = w->unregistration(users[500000-1].id);
        if (res != 0) {
            cout <<" XXX2 " << endl;
            --cnt;
        }

        for (int i = 0; i < 150000; ++i) {
//            if (i == 100000) {
//                cout << i << endl;
//            }
            res = w->registration(users[400000-i-1].id,users[i].level,users[i].prefs);
            if (res != 0) {
                cout <<" XXX3 " << endl;
                --cnt;
            }
            res = w->unregistration(users[400000-1-i].id);
            if (res != 0) {
                cout << i << endl;
                --cnt;
            }
        }
    }

    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    //    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
    //    cout << callsNum << " " << 1.0*cnt/1.0/callsNum << endl;
}


