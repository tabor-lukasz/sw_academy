#include "judge.h"

//#include <iostream>
//#include <iomanip>
//using namespace std;

class KAP : public IKAP {
    virtual int maxScore(int n, int data[][5]);
};

int main(){
    KAP solution;
    judge::run(&solution);
}

struct field {
    int states[6] = {-1,-1,-1,-1,-1,-1};
};

struct line {
    field fields[5];
};

//void print(line ll) {
//    for (int k=5; k >=0; --k) {
//        for (int j = 0; j < 5;++j) {
//            cout << setw(3) <<  ll.fields[j].states[k] << "  ";
//        }
//        cout << endl;
//    }
//}

int KAP::maxScore(int n, int data[][5]) {

    line currLine;

    for (int i =0;i<5;++i) {
        for (int j = 0; j < 6;++j) {
            currLine.fields[i].states[j] = -1;
        }
    }
    currLine.fields[2].states[5] = 0;

//    if (n == 11) {
//        int aa = 0;
//    }
//    cout << 0 << endl;
//    print(currLine);

    for (int i =n-1;i >= 0;--i) {
        for (int j = 0; j < 5; ++j) {
            if (data[i][j] == 2) {
                data[i][j] = -1;
            }
        }

        line nextLine;


        for (int j = 0; j < 5;++j) {
            for (int k=0; k < 6; ++k) {
                if (currLine.fields[j].states[k] >= 0) {
                    for (int z = j-1; z <= j+1; ++z) {
                        if ((z > 4) || (z < 0)) {
                            continue;
                        }

                        int currScore = currLine.fields[j].states[k];
                        if (k > 0) {
                            int newScore = currScore + (data[i][z] > 0 ? 1 : 0);
                            if (newScore > nextLine.fields[z].states[k-1]) {
                                nextLine.fields[z].states[k-1] = newScore;
                            }
                        } else {
                            int newScore = currScore + data[i][z];
                            if (newScore > nextLine.fields[z].states[0]) {
                                nextLine.fields[z].states[0] = newScore;
                            }
                        }

                        if (k == 5) {
                            int newScore = currScore + data[i][z];
                            if (newScore > nextLine.fields[z].states[k]) {
                                nextLine.fields[z].states[k] = newScore;
                            }
                        }
                    }
                }
            }
        }
        currLine = nextLine;
//        cout << n - i << endl;
//        print(currLine);
//        cout << endl;
    }

    int max = -1;
    for (int j = 0; j < 5;++j) {
        for (int k=0; k < 6; ++k) {
            if (max < currLine.fields[j].states[k]) {
                max = currLine.fields[j].states[k];
            }
        }
    }

    return max;
}
