#include "judge.h"
//#include <iostream>
//using namespace std;

long long factorials[] = {1l,1l,2l,6l,24l,120l,720l,5040l,40320l,362880l,3628800l,39916800l,479001600l,6227020800l,87178291200l,1307674368000l,20922789888000l,355687428096000l,6402373705728000l,121645100408832000l,2432902008176640000l,};

//long long factorial(int n) {
//    long long res = 1;

//    for (int i = 2; i <= n; ++i) {
//        res *= i;
//    }
//    return res;
//}


inline long long komb(int k, int n) {
    return factorials[n] / factorials[k] / factorials[n-k];
}

int nodes[21];
int f[21];


class KOD : public iKOD {
public:
    virtual long long countCodes(int n, int codeLengths[20]) {

        long long res = 1;

        for (int i = 0; i < 21; ++i) {
            nodes[i] = f[i] = 0;
        }

//        cout << "{";
//        for (int i = 0; i < 21; ++i) {
//            cout << factorial(i) << "l,";
//        }
//        cout << "}" << endl;

        nodes[0] = 1;

        int maxLen = codeLengths[0];

        for (int i = 0; i < n; ++i) {
            ++f[codeLengths[i]];
            if (codeLengths[i]>maxLen) {
                maxLen = codeLengths[i];
            }
        }

        for (int i = 1; i < 20; i++) {
            nodes[i] = nodes[i-1]*2 - f[i];
        }
        nodes[20] = 0;

//        cout << "counts:" << endl;
//        for (int i = 0; i <= maxLen; ++i) {
//            cout << i << ": " << f[i]  << " " << nodes[i] << endl;
//        }
//        cout << endl;

        for (int i = 1; i <= maxLen; ++i) {
            res *= factorials[f[i]] * komb(nodes[i],nodes[i-1]*2);
        }

        return res;
    }
};

int main() {
    KOD k;
    judge::run(&k);
}
