#include "judge.h"

static long long (*gcost)[8];
static int gn;
static int gk;
static long long minCost;

bool users[15];

class NAD : public INAD {
public:
    long long getMinimumCost(int nn, int kk, long long cc[15][8]) {

        gcost = cc;
        gn = nn;
        gk = kk;

        minCost = 0;
        for (int i = 0; i < kk; ++i) {
            minCost += cc[i][i];
        }

        for (int i =0; i <gn; ++i) {
            users[i] = 0;
        }

        match(0,0);

        return minCost;
    }


    void match(int k,long long cost) {
        if (cost >= minCost)
            return;

        if (k == gk) {
            minCost = cost;
            return;
        }

        for (int i = 0; i < gn; ++i) {
            if (!users[i]) {
                users[i] = 1;
                match(k+1,cost + gcost[i][k]);
                users[i] = 0;
            }
        }
    }
};

NAD solution;
int main() {
    Judge::run(&solution);
    return 0;
}
