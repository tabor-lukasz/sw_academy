#include "judge.h"
#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

namespace {

const int LEN = 64;
const int BUF_LEN = LEN + 1;
const int MAX_SIZE = 43000;
const int BUF_SIZE = 3 * MAX_SIZE + 5;
const int MEMORY_SIZE = 8 * 1024 * 1024;

char strings[BUF_SIZE][BUF_LEN];
int unusedCount;
int unused[BUF_SIZE];

int name[MAX_SIZE];
int surname[MAX_SIZE];
int pesel[MAX_SIZE];
int itemsSize;

long long seed;
int pseudo_rand() {
    seed = seed * 13477581 + 1;
    return (seed & 0x7FFFFFFF) % 1000000007;
}

int mode;

char buf1[BUF_LEN];
char buf2[BUF_LEN];
char buf3[BUF_LEN];

void intSwap(int &a, int &b) { int t=a; a=b; b=t; }

char memory[MEMORY_SIZE];


string TestPrefix = "NAZ0";
string TestCase = "";
string TestSuffixOut = ".out";
string TestSuffixIn = ".in";

//string TestCases = "e";
string TestCases = "abcdefghi1234567899999";


void run1(INaz *solution, ifstream& ins, ifstream& outs) {
    ins >> unusedCount;
    int maxSize; ins >> maxSize;
    int opCount; ins >> opCount;
    for (int i=0; i<unusedCount; ++i) {
        ins >> strings[i];
        unused[i] = i;
    }
    solution->init(maxSize);
    char buf[BUF_LEN];
    for (int i=0; i<opCount; ++i) {
        int cmd; ins >> cmd;
        if (2 == cmd) {
            int name; ins >> name;
            int surname; ins >> surname;
            int pesel; ins >> pesel;
            solution->addCitizen(strings[name], strings[surname], strings[pesel]);
        } else if (3 == cmd) {
            int pesel; ins >> pesel;
            solution->delCitizen(strings[pesel]);
        } else if (4 == cmd) {
            int pesel; ins >> pesel;
            solution->getNameByPesel(strings[pesel], buf);
            string answer = buf;
            string expected;
            outs >> expected;
            if (answer.compare(expected)) {
                cout << i << " " << answer << "\t" << expected << endl;
            }
        } else if (5 == cmd) {
            int pesel; ins >> pesel;
            solution->getSurnameByPesel(strings[pesel], buf);
            string answer = buf;
            string expected;
            outs >> expected;
            if (answer.compare(expected)) {
                cout << i << " " << answer << "\t" << expected << endl;
            }
        } else if (6 == cmd) {
            int name; ins >> name;
            solution->getPeselByName(strings[name], buf);
            string answer = buf;
            string expected;
            outs >> expected;
            if (answer.compare(expected)) {
                cout << i << " " << answer << "\t" << expected << endl;
            }
        } else if (7 == cmd) {
            int surname; ins >> surname;
            solution->getPeselBySurname(strings[surname], buf);
            string answer = buf;
            string expected;
            outs >> expected;
            if (answer.compare(expected)) {
                cout << i << " " << answer << "\t" << expected << endl;
            }
        }
    }
}

void run2(INaz *solution, ifstream& ins, ifstream& outs) {
    int maxSize;
    int opCount;
    if (TestCase.c_str()[0] > '9') {
        ins >> maxSize;
        ins >> opCount;
        ins >> seed;
    } else {
        maxSize = 43000;
        opCount = 1000000;
        seed = rand() % 1000000007;
    }

    solution->init(maxSize);

    const char *LETTERS = "aaabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//    string sss = LETTERS;
//    cout << sss.size() << endl;
    for (int i=0; i<BUF_SIZE; ++i) {
        for (int j=0; j<LEN; ) {
            int rnd = pseudo_rand();
            strings[i][j++] = LETTERS[rnd & 0x3f]; rnd >>= 6;
            strings[i][j++] = LETTERS[rnd & 0x3f]; rnd >>= 6;
            strings[i][j++] = LETTERS[rnd & 0x3f]; rnd >>= 6;
            strings[i][j++] = LETTERS[rnd & 0x3f]; rnd >>= 6;
        }
        strings[i][LEN] = 0;
        if (i % 128 == 127) strings[i][8 + pseudo_rand() % 56] = 0;
    }

    for (int i=0; i<BUF_SIZE; ++i) unused[i] = i;
    unusedCount = BUF_SIZE;
    itemsSize = 0;

    char hhash[64];
    for (int i=0; i<64; ++i) hhash[i] = 0;

    while (opCount > 0) {
        int rnd = pseudo_rand() % 8;
        if (rnd <= 2) { // add
            if (itemsSize == maxSize) continue;

            intSwap(unused[unusedCount-1], unused[pseudo_rand() % unusedCount]);
            name[itemsSize] = unused[--unusedCount];
            intSwap(unused[unusedCount-1], unused[pseudo_rand() % unusedCount]);
            surname[itemsSize] = unused[--unusedCount];
            intSwap(unused[unusedCount-1], unused[pseudo_rand() % unusedCount]);
            pesel[itemsSize] = unused[--unusedCount];

            for (int i=0; i<BUF_LEN; ++i) buf1[i] = strings[name[itemsSize]][i];
            for (int i=0; i<BUF_LEN; ++i) buf2[i] = strings[surname[itemsSize]][i];
            for (int i=0; i<BUF_LEN; ++i) buf3[i] = strings[pesel[itemsSize]][i];


            solution->addCitizen(buf1, buf2, buf3);
            ++itemsSize;

        } else {
            if (0 == itemsSize) continue;
            int pos = pseudo_rand() % itemsSize;
            if (rnd == 3) { // del
                for (int i=0; i<BUF_LEN; ++i) buf3[i] = strings[pesel[pos]][i];

                solution->delCitizen(buf3);

                unused[unusedCount++] = name[pos];
                unused[unusedCount++] = surname[pos];
                unused[unusedCount++] = pesel[pos];
                --itemsSize;
                name[pos] = name[itemsSize];
                surname[pos] = surname[itemsSize];
                pesel[pos] = pesel[itemsSize];
            } else if (rnd == 4) {
                for (int i=0; i<BUF_LEN; ++i) buf3[i] = strings[pesel[pos]][i];
                solution->getNameByPesel(buf3, buf1);
                for (int i=0; buf1[i]; ++i) hhash[i] ^= buf1[i];
            } else if (rnd == 5) {
                for (int i=0; i<BUF_LEN; ++i) buf3[i] = strings[pesel[pos]][i];
                solution->getSurnameByPesel(buf3, buf2);
                for (int i=0; buf2[i]; ++i) hhash[i] ^= buf2[i];
            } else if (rnd == 6) {
                for (int i=0; i<BUF_LEN; ++i) buf1[i] = strings[name[pos]][i];
                solution->getPeselByName(buf1, buf3);
                for (int i=0; buf3[i]; ++i) hhash[i] ^= buf3[i];
            } else { // rnd == 7 //
                for (int i=0; i<BUF_LEN; ++i) buf2[i] = strings[surname[pos]][i];
                solution->getPeselBySurname(buf2, buf3);
                for (int i=0; buf3[i]; ++i) hhash[i] ^= buf3[i];
            }
        }

        --opCount;
    }

    string answer = "";

    for (int i=0; i<64; ++i) {
        int x = hhash[i];
        answer += "0123456789ABCDEF"[x & 15];
        answer += "0123456789ABCDEF"[(x >> 4) & 15];
    }

    if (TestCase.c_str()[0] > '9') {

        string expected;
        outs >> expected;

        if (expected.compare(answer)) {
            cout << " " << expected << "\t" << answer << endl;
        }
    }
}

} // namespace


int Judge::memorySize() {
    return MEMORY_SIZE;
}

void Judge::memoryRead(int offset, int size, char *buf) {
    if (offset < 0 || offset + size > MEMORY_SIZE)
        exit(1);
    for (int i=0; i<size; ++i)
        buf[i] = memory[offset + i];
}

void Judge::memoryWrite(int offset, int size, char *buf) {
    if (offset < 0 || offset + size > MEMORY_SIZE)
        exit(1);
    for (int i=0; i<size; ++i)
        memory[offset + i] = buf[i];
}

void Judge::run(INaz *solution) {

    srand(time(0));

    for (auto cc : TestCases) {
        auto begin = chrono::steady_clock::now();
        TestCase = cc;
        cout << cc << " ";
        ifstream ins(TestPrefix + TestCase + TestSuffixIn);
        ifstream outs(TestPrefix + TestCase + TestSuffixOut);

        ins >> mode;

        if (1 == mode) run1(solution, ins, outs);
        if (2 <= mode) run2(solution, ins, outs);

        auto end = chrono::steady_clock::now();
        cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
    }
}

