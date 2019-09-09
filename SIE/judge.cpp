#include "judge.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

string TestPrefix = "data/SIE0";
//string TestCases= "abcde";
//string TestCases= "a";
//string TestCases= "1";
string TestCases= "2";
//string TestCases= "3";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

void judge::run(iSIE *s)
{

    for (auto testCase : TestCases) {
        auto begin = chrono::high_resolution_clock::now();
        if (testCase == 'a') {
            ifstream _ins(TestPrefix + TestSuffixIn);
            ifstream _outs(TestPrefix + TestSuffixOut);
            int _typ;
            _ins >> _typ;
            int _callsNum;
            _ins >> _callsNum;
            for (int _i = 0; _i < _callsNum; ++_i)
            {
                int _op;
                _ins >> _op;
                if (_op == 0)
                {
                    int idNew, idExisting, linkThroughput;
                    _ins >> idNew >> idExisting >> linkThroughput;
                    s->addServer(idNew, idExisting, linkThroughput);
                } else if (_op == 1)
                {
                    int id;
                    _ins >> id;
                    int expected;
                    _outs >> expected;
                    auto res = s->directLinks(id);
                    if (res != expected) {
                        cout << "#"  << _i << " " << res << " " << expected << endl;
                    } else {
                        cout << "OK" << endl;
                    }
                } else if (_op == 2)
                {
                    int id1, id2;
                    _ins >> id1 >> id2;
                    int expected;
                    _outs >> expected;
                    auto res = s->connectionThroughput(id1, id2);
                    if (res != expected) {
                        cout << "#"  << _i << " " << res << " " << expected << endl;
                    } else {
                        cout << "OK" << endl;
                    }
                } else if (_op == 3)
                {
                    int id1, id2, newThroughput;
                    _ins >> id1 >> id2 >> newThroughput;
                    s->improveThroughput(id1, id2, newThroughput);
                }
            }
        } else if (testCase == '1') {
            for (int i =1 ; i<=500000; i++) {
                s->addServer(i,i-1,1000);
            }
            int res = s->connectionThroughput(0,500000);
            if (res != 1000) {
                cout << testCase << " " << 1 << endl;
            }

            for (int i =0 ; i+2<=50000; i+=3) {
                s->improveThroughput(i,i+2,1100);
            }

            res = s->directLinks(3*11234-1);
            if (res != 3) {
                cout << testCase << " " << 2 << endl;
            }

            for (int i =0 ; i+4<=50000; i+=6) {
                s->improveThroughput(i,i+4,1050);
            }

            res = s->directLinks(6*1234 + 3);
            if (res != 1) {
                cout << testCase << " " << 3 << endl;
            }

            res = s->directLinks(6*1234 + 2);
            if (res != 2) {
                cout << testCase << " " << 4 << endl;
            }

            res = s->connectionThroughput(6*3254+2,6*3254+4);
            if (res != 1050) {
                cout << testCase << " " << 5 << endl;
            }

            res = s->connectionThroughput(0,500000);
            if (res != 1000) {
                cout << testCase << " " << 6 << endl;
            }
        } else if (testCase == '2') {
            for (int i =1 ; i<=500000; i++) {
                s->addServer(i,(i-1)/50*50,1000);
            }

            int res = s->directLinks(15050);
            if (res != 51) {
                cout << testCase << " " << 1 << endl;
            }

            res = s->connectionThroughput(0,500000);
            if (res != 1000) {
                cout << testCase << " " << 2 << endl;
            }
            s->improveThroughput(0,500000,2000);

            res = s->directLinks(50);
            if (res != 50) {
                cout << testCase << " " << 3 << endl;
            }
        } else if (testCase == '3') {
            for (int i =1 ; i<=250000; i++) {
                s->addServer(i,0,1000);
            }

            for (int i =250001 ; i<=500000; i++) {
                s->addServer(i,1,1000);
            }

            int res = s->directLinks(0);
            if (res != 250000) {
                cout << testCase << " " << 1 << endl;
            }

            for (int i = 0; i < 500000; i++) {
                if (i % 100 == 0) {
                    cout << i << endl;
                }
                int rnd1 = rand() % 500001;
                int rnd2 = rand() % 500001;
                while (rnd1 == rnd2) {
                    rnd2 = rand() % 500001;
                }

                res = s->connectionThroughput(rnd1,rnd2);
                if (res != 1000) {
                    cout << testCase << " " << 2 << endl;
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();

        cout << testCase << "\t" << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << endl;
    }
}
