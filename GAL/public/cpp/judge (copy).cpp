#include "judge.h"
#include <cstdio>

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <sstream>

#include <chrono>

using namespace std;
const int SIZE = 100;
int PRINT_SIZE = 100;
int RAND_SIZE = 100;
int MAGIC = 1;

const int MOD = 1000000097;

const string TestPrefix = "GAL0";
string TestName = "a";
string TestNames = "abcdefgh123";
//string TestNames = "ch";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

enum Type { Produkcja, Handel, Przetwarzanie, Ataki, Podatki };
enum Print { None, Hash, Full };

long long outputArray[SIZE][SIZE];
char command[100];
igalaxy* program = 0;

long seed = 0;
int _rand() {
    seed = seed * 134775813 + 1;
    return (int)((seed & 0x7FFFFFFF) % 100000007);
}

int hasha = 0;

void testSummary(Print print, ifstream& ifsOut) {
    ::hasha = 0;
    outputArray[_rand() % SIZE][_rand() % SIZE] = 123;

    if (program)
        program->summary(outputArray);

    for (int i = 0; i < PRINT_SIZE; i++) {
        for (int j = 0; j < PRINT_SIZE; j++) {
            long long x;
            ifsOut >> x;
            if (x != outputArray[i][j]) {
//                cout << endl << i << " " << j << ": " << x << " " << outputArray[i][j] <<  endl;
            }
            if (print == Full) cout << setw(3) << outputArray[i][j] % 1000 << " ";
            hasha *= 13;
            hasha += (int)(outputArray[i][j] % MOD);
        }
        if (print == Full) cout << endl;
    }
    int hashRef;
    ifsOut >> hashRef;
    if (hasha != hashRef) {
        cout << hasha << " " << hashRef << endl;
    }

    if (print != None) cout <<hasha * MAGIC << endl;
    if (print == Full) cout << endl;
}

void judge::run(igalaxy* solution) {
    program = solution;

    for (int k = 0; k < TestNames.size(); ++k) {
        auto begin = chrono::steady_clock::now();
        TestName = "";
        TestName += TestNames[k];

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                stringstream ss;
                ss << "(";
                ss << i;
                ss << ",";
                ss << j;
                ss << ")=Produkcja(0)";
                string s = ss.str();
                char buffer[50];
                strcpy(buffer,s.c_str());
                solution->report(buffer);
            }
        }

        solution->check();

        cout << TestName << " ";

        if (isalpha(TestName.c_str()[0])) {

            ifstream ifsIn(TestPrefix + TestName + TestSuffixIn);
            ifstream ifsOut(TestPrefix + TestName + TestSuffixOut);

            int mode;
            ifsIn >> mode;

            int n, type;
            int a, b, c, d, e, f, g, h;
            PRINT_SIZE = 10;
            ifsIn >> n;

            string commandStr;

            for (int i = 0; i < n; i++) {
                ifsIn >> type;
                if (type == 0) {
                    testSummary(None,ifsOut);
                    continue;
                }

                ifsIn >> commandStr;
//                cout << commandStr << endl;
                strcpy(command,commandStr.c_str());
                //      for (int j = 0; j < 10; ++j) {
                ifsOut >> commandStr;
                //      }

                //      scanf("%s", command);
                solution->report(command);
                //printf("%s\n", command);
            }
        } else {
            if (TestName.c_str()[0] == '1' || TestName.c_str()[0] == '2') {
                for (int i = 0; i < 15000; i++) {
//                    cout << i << endl;
                    stringstream ss;
                    int id = rand() % 130;
                    int x,y;
                    char buff[50];
                    long long out[100][100];
                    if (id < 100 && id > 1) {
                        x = id;
                        y = id;
                        ss << "(";
                        ss << x;
                        ss << ",";
                        ss << y;
                        ss << ")=";
                        int ccc = rand()%2;
                        if (ccc == 0) {
                            ss << "Handel((";
                            ss << x;
                            ss << ",";
                            ss << y -1;
                            ss << "),(";
                            ss << x - 1;
                            ss << ",";
                            ss << y;
                            ss << "))";
                        } else {
                            int xx = x-10;
                            int yy = y-10;
                            if (xx<0) xx = 0;
                            if (yy<0) yy = 0;
                            ss << "Ataki((";
                            if (TestName.c_str()[0] == '1') {
                                ss << xx;
                                ss << ",";
                                ss << yy;
                            } else if (TestName.c_str()[0] == '2') {
                                ss << 0;
                                ss << ",";
                                ss << 0;
                            }
                            ss << "),(";
                            ss << x;
                            ss << ",";
                            ss << y;
                            ss << "))";
                        }
                        string sss = ss.str();
                        //                    cout << sss << " 1" << endl;
                        strcpy(buff,sss.c_str());
                        solution->report(buff);
                        //                    cout << sss << " 2" << endl;
                    } else {
                        //                    cout << "summary1";
                        solution->summary(out);
                        //                    cout << "summary2";
                    }
                    //                cout << " " << i  << endl;
                }
            } else if (TestName.c_str()[0] == '3') {
                for (int i = 1; i < 100; ++i) {
                    for (int j = 1; j < 100; j++) {
                        int xx = i-10 > 0 ? i-10 : 0;
                        int yy = j-10 > 0 ? j-10 : 0;
                        stringstream ss;
                        char buff[50];
                        ss << "(";
                        ss << i;
                        ss << ",";
                        ss << j;
                        ss << ")=";
                        ss << "Ataki((";
                        ss << xx;

                        ss << ",";
                        ss << yy;
                        ss << "),(";
                        ss << i;
                        ss << ",";
                        ss << j;
                        ss << "))";
                        string sss = ss.str();
                        strcpy(buff,sss.c_str());
                        solution->report(buff);
                    }
                }

                for (int i = 0; i < 15000; i++) {
//                    cout << i << endl;
                    stringstream ss;
                    int id = rand() % 130;
                    int x,y;
                    char buff[50];
                    long long out[100][100];
                    if (id < 100 && id > 1) {
                        x = id;
                        y = id;
                        ss << "(";
                        ss << x;
                        ss << ",";
                        ss << y;
                        ss << ")=";
                        int ccc = rand()%2;
                        if (ccc == 0) {
                            ss << "Handel((";
                            ss << x;
                            ss << ",";
                            ss << y -1;
                            ss << "),(";
                            ss << x - 1;
                            ss << ",";
                            ss << y;
                            ss << "))";
                        } else {
                            int xx = x-10;
                            int yy = y-10;
                            if (xx<0) xx = 0;
                            if (yy<0) yy = 0;
                            ss << "Ataki((";
                            ss << xx;
                            ss << ",";
                            ss << yy;
                            ss << "),(";
                            ss << x;
                            ss << ",";
                            ss << y;
                            ss << "))";
                        }
                        string sss = ss.str();
                        //                    cout << sss << " 1" << endl;
                        strcpy(buff,sss.c_str());
                        solution->report(buff);
                        //                    cout << sss << " 2" << endl;
                    } else {
                        //                    cout << "summary1";
                        solution->summary(out);
                        //                    cout << "summary2";
                    }
                    //                cout << " " << i  << endl;
                }
            }
        }
        auto end = chrono::steady_clock::now();
        cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
    }
    cout << endl;
}
