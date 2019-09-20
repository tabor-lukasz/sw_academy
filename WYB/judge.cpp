#include "judge.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

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



string TestCases = "ab";
string TestCasePrefix = "res/WYB0";
string TestCaseSuffixIn = ".in";
string TestCaseSuffixOut = ".out";

namespace {
const int MAX_N = 2000;

int ver1[MAX_N];
int ver2[MAX_N];
int dist[MAX_N];

} // namespace

void Judge::run(IWYB *solution) {

    for (auto cc : TestCases) {

        ifstream ins(TestCasePrefix + cc + TestCaseSuffixIn);
        ifstream outs(TestCasePrefix + cc + TestCaseSuffixOut);

        MyTimer timer(cc);

        int T, N;

        ins >> T;
        for (int i = 0; i < T; i++) {
            ins >> N;
            for (int j = 0; j < N - 1; j++) {
                ins >> ver1[j] >> ver2[j] >> dist[j];
            }
            int ret = solution->improveNetwork(N, ver1, ver2, dist);

            int expected;
            outs >> expected;
            if (expected != ret){
                cout << cc << " " << ret << " " << expected << endl;
            } else {
                cout << cc << " OK\n";
            }
        }

    }
    return;
}


//Plik wejściowy zawiera maksymalnie 1000 testów (wywołań funkcji) 1 <= T <= 1000,
//Liczba stacji w jednym schemacie N jest z zakresu 4 <= N <= 2000,
//W pliku każda stacja ma unikalny numer Id. 1 <= Id <= N,
//Liczba tuneli pomiedzy stacjami N-1,
//Długość tunelu d jest w zakresie 1 <= d <= 20,
//Jedna stacja może mieć więcej niż 2 tunele dochodzące do niej,
//Tylko jeden tunel może byc przeniesiony.
//Po przesunieciu tunelu musi byc możliwy dojazd do każdej ze stacji metra z dowolnej innej.
