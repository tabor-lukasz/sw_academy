#include "judge.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <sstream>
using namespace std;


string TestPrefix = "res/NON0";
string TestCases= "abcdefghijklmnopqrstuvw";
//string TestCases= "sw";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

const int MAX = 100;

int data[MAX][MAX];
INON *rows[MAX];
INON *columns[MAX];
int tmp[MAX];

int type;
int height, width;

void print() {
    cout << endl;
    int cnt = 0;
    for (int row=0; row<height; ++row) {
        for (int col=0; col<width; ++col) {
            if (INON::COLOR_UNKNOWN == data[row][col]) {cout << "?"; cnt++;}
            if (INON::COLOR_WHITE == data[row][col]) cout << ".";
            if (INON::COLOR_BLACK == data[row][col]) cout << "#";
        }
        cout << endl;
    }
    cout << "cnt: " << cnt << endl;
    if (cnt) {
        cout << "rows: " << endl;
        for (int i = 0;i < MAX;++i) {
            if (!rows[i])
                break;

//            rows[i]->print();
        }

        cout << "columns: " << endl;
        for (int i = 0;i < MAX;++i) {
            if (!columns[i])
                break;

//            columns[i]->print();
        }
    }
    cout << endl;
}

void check(ifstream& outs) {
    bool ok = true;
    int cnt = 0;
    for (int i = 0; i < height; ++i) {
        string expected;
        outs >> expected;

        stringstream ss;
        for (int j = 0; j < width; ++j) {
            if (INON::COLOR_UNKNOWN == data[i][j]) {ss << "?";}
            if (INON::COLOR_WHITE == data[i][j]) ss << ".";
            if (INON::COLOR_BLACK == data[i][j]) ss << "#";
        }

        string result = ss.str();

        if (result.compare(expected)) {
            for (unsigned i = 0; i < expected.size(); ++i) {
                if (expected[i] != result[i] && result[i] != '?') {
                    cnt++;
                }
            }
            ok = false;
        }
    }
    if (!ok) {
        cout << "Wrong!! " << cnt << endl;
    } else
        cout << "OK" << endl;
}

void Judge::run(INON *factory) {

    for (int i = 0; i < MAX;++i) {
        rows[i] = nullptr;
        columns[i] = nullptr;
    }

    for (auto cc : TestCases) {

        for (int i = 0; i < MAX;++i) {
//            delete rows[i];
//            delete columns[i];
            rows[i] = nullptr;
            columns[i] = nullptr;
        }

        ifstream ins(TestPrefix + cc + TestSuffixIn);
        ifstream outs(TestPrefix + cc + TestSuffixOut);

        clock_t start = clock();

        ins >> type;
        ins >> height >> width;

        for (int row=0; row<height; ++row) for (int col=0; col<width; ++col) data[row][col] = INON::COLOR_UNKNOWN;
        cout << "rows: " << endl;
        for (int row=0; row<height; ++row) {
            int k; ins >> k;
            for (int i=0; i<k; ++i) ins >> tmp[i];
            rows[row] = factory->createLine(width, k, tmp);
        }
        cout << "columns: " << endl;
        for (int col=0; col<width; ++col) {
            int k; ins >> k;
            for (int i=0; i<k; ++i) ins >> tmp[i];
            columns[col] = factory->createLine(height, k, tmp);
        }
        cout << endl;

        bool anyChange = true;
        while (anyChange) {
            anyChange = false;
            //            print();
            for (int row=0; row<height; ++row) {
                for (int col=0; col<width; ++col) {
                    if (INON::COLOR_UNKNOWN == data[row][col]) {
                        int color = rows[row]->getColor(col);
                        if (INON::COLOR_UNKNOWN != color) {
                            data[row][col] = color;
                            columns[col]->setColor(row, color);
                            //                            print();
//                            for (int i = 0; i < width; ++i) {
////                                columns[col]->print();
//                            }
                            anyChange = true;
                        }
                    }
                }
            }
            //            print();
            for (int col=0; col<width; ++col) {
                for (int row=0; row<height; ++row) {
                    if (INON::COLOR_UNKNOWN == data[row][col]) {
                        int color = columns[col]->getColor(row);
                        if (INON::COLOR_UNKNOWN != color) {
                            data[row][col] = color;
//                            if (row == 4 && col == 6) {
//                                int rrr = 9;
//                            }
                            rows[row]->setColor(col, color);
//                            for (int i = 0; i < height; ++i) {
////                                rows[row]->print();
//                            }
                            anyChange = true;
                            //                            print();
                        }
                    }
                }
            }
        }

        clock_t runningTime = clock() - start;

        print();
        check(outs);
        cout << cc << " " << (((double)runningTime) / CLOCKS_PER_SEC) << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
}

