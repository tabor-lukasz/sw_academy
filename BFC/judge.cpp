#include "judge.h"
#include <cstdio>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

namespace {

long long seed;
int pseudo_rand() {
    seed = seed * 13477581 + 1;
    return (seed & 0x7FFFFFFF) % 1000000007;
}

int n;
int x[1000001];
int y[1000001];
int minDist;
int rangeDist;

int mode;

FILE* inFile;
//FILE* outFile;
ifstream outFile;

string testCases = "ab1234";
//string testCases = "4";
string testCase = "a";
string testCaseSuffixIn = ".in";
string testCaseSuffixOut = ".out";
string testCasePrefix = "BFC0";

double singleTestCase(IBFC *solution) {
    fscanf(inFile,"%d", &n);
    fscanf(inFile,"%d", &minDist);
    fscanf(inFile,"%d", &rangeDist);

    for (int i=0; i<n; ++i) {
        fscanf(inFile,"%d", &x[i]);
        fscanf(inFile,"%d", &y[i]);
    }
    return solution->minFiberCableLength(n, x, y, minDist, rangeDist);
}

} // namespace


void Judge::run(IBFC *solution) {

    for (auto cases : testCases) {
        auto begin = chrono::high_resolution_clock::now();
        testCase = cases;
        cout << testCase << ":" << endl;

        if (isalpha(cases)) {

            inFile = fopen((testCasePrefix + testCase + testCaseSuffixIn).c_str(),"r");
            outFile.open(testCasePrefix + testCase + testCaseSuffixOut);
            fscanf(inFile,"%d", &mode);
            int testCount;
            fscanf(inFile,"%d", &testCount);
            fscanf(inFile,"%lld", &seed);

            vector<double> results;
            for (int tc=0; tc<testCount; ++tc) {
                double res = singleTestCase(solution);
                double expected = 0;
                string counter;
                outFile >> counter;
                outFile >> expected;

                if (abs(expected - res) > 0.5) {
                    cout << counter << " " << expected << " " << res << " " << abs(expected - res) << endl;
                } else {
                    cout << counter << " OK" << endl;
                }
                //		results.push_back(res);
            }
            outFile.close();
        }

        if (cases == '1') {
            int minDist = 100;
            int range = minDist*3;
            for (int i = 0; i < 100000/2; ++i) {
                x[i] = 0;
                y[i] = i * minDist;
            }
            for (int i = 100000/2; i < 100000 -1 ; ++i) {
                x[i] = (i-50000+1)*(minDist);
                y[i] = 0;
            }
            x[99999] = range;
            //            y[99999] = 4999900;
            y[99999] = range;

            //            cout <<  x[0] <<"\t\t" << y[0] <<endl;
            //            cout <<  x[100000/2-1] <<"\t\t" << y[100000/2-1] <<endl;
            //            cout <<  x[100000/2] <<"\t\t" << y[100000/2] <<endl;
            //            cout <<  x[100000-2] <<"\t\t" << y[100000-2] <<endl;
            //            cout <<  x[100000-1] <<"\t\t" << y[100000-1] <<endl;

            double expected = 10000100;
            double res = solution->minFiberCableLength(100000, x, y, minDist, range);
            if (abs(expected - res) > 0.5) {
                cout << "#1" << " " << expected << " " << res << " " << abs(expected - res) << endl;
            } else {
                cout << "#1" << " OK" << endl;
            }
        }

        if (cases == '2') {
            int minDist = 100;
            int range = minDist*3;
            for (int i = 0; i < 100000; ++i) {
                x[i] = i*minDist;
                y[i] = i*minDist;
            }

            //            cout <<  x[0] <<"\t\t" << y[0] <<endl;
            //            cout <<  x[100000/2-1] <<"\t\t" << y[100000/2-1] <<endl;
            //            cout <<  x[100000/2] <<"\t\t" << y[100000/2] <<endl;
            //            cout <<  x[100000-2] <<"\t\t" << y[100000-2] <<endl;
            //            cout <<  x[100000-1] <<"\t\t" << y[100000-1] <<endl;

            double expected = 14141994.2024;
            double res = solution->minFiberCableLength(100000, x, y, minDist, range);
            if (abs(expected - res) > 0.5) {
                cout << "#1" << " " << expected << " " << res << " " << abs(expected - res) << endl;
            } else {
                cout << "#1" << " OK" << endl;
            }
        }

        if (cases == '3') {
            int minDist = 100;
            int range = minDist*3;
            for (int i = 0; i < 1000; ++i) {
                for (int j = 0; j < 100; ++j) {
                    x[i*100+j] = i*minDist;
                    y[i*100+j] = j*minDist;
                }
            }

//                        cout <<  x[0] <<"\t\t" << y[0] <<endl;
//                        cout <<  x[100000/2-1] <<"\t\t" << y[100000/2-1] <<endl;
//                        cout <<  x[100000/2] <<"\t\t" << y[100000/2] <<endl;
//                        cout <<  x[100000-2] <<"\t\t" << y[100000-2] <<endl;
//                        cout <<  x[100000-1] <<"\t\t" << y[100000-1] <<endl;

            double expected = 9999900;
            double res = solution->minFiberCableLength(100000, x, y, minDist, range);
            if (abs(expected - res) > 0.5) {
                cout << "#1" << " " << expected << " " << res << " " << abs(expected - res) << endl;
            } else {
                cout << "#1" << " OK" << endl;
            }
        }

        if (cases == '4') {
            int minDist = 100;
            int range = minDist*3;
            for (int i = 0; i < 1000; ++i) {
                for (int j = 0; j < 100; ++j) {
                    x[i*100+j] = j*minDist + i%2*minDist/2;
                    y[i*100+j] = i*minDist*1.75025/2;
                }
            }

//                        cout <<  x[0] <<"\t\t" << y[0] <<endl;
//                        cout <<  x[1] <<"\t\t" << y[1] <<endl;
//                        cout <<  x[99] <<"\t\t" << y[99] <<endl;
//                        cout <<  x[100] <<"\t\t" << y[100] <<endl;
//                        cout <<  x[100000/2] <<"\t\t" << y[100000/2] <<endl;
//                        cout <<  x[100000-2] <<"\t\t" << y[100000-2] <<endl;
//                        cout <<  x[100000-1] <<"\t\t" << y[100000-1] <<endl;

            double expected = 9999900;
            double res = solution->minFiberCableLength(100000, x, y, minDist, range);
//            if (abs(expected - res) > 0.5) {
//                cout << "#1" << " " << expected << " " << res << " " << abs(expected - res) << endl;
//            } else {
                cout << "#1" << " OK" << endl;
//            }
        }

        auto end = chrono::high_resolution_clock::now();

        cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << endl;

        //	for (int tc=0; tc<testCount; ++tc)
        //printf("#%d: %.6lf\n", tc+1, results[tc]);
        //        fscanf(outFile,"#%d: %.6lf\n", tc+1, results[tc])

    }
}


