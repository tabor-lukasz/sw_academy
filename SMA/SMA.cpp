#include "judge.h"

int positions[5000];
int tmp[5000];
int nn;

int insertAndGreaterThan(int num) {
    int beg = 0;
    int end = nn-1;
    int mid = (end+beg)/2;

    int cnt = 0;
    num--;

    while (true) {
        if (num > mid) {
            tmp[mid]++;
            beg = mid + 1;
            mid = (end+beg)/2;
        } else {
            cnt += tmp[mid];

            if (mid == num) {
                tmp[mid]++;
                return cnt;
            }

            end = mid - 1;
            mid = (end+beg)/2;
        }
    }
}

class SMA : public ISMA {
public:
    int sortPancakes(int n, int *p, int *mv) {
        nn = n;
        for (int i = 0; i < n; ++i) {
            tmp[i] = 0;
            positions[p[i]-1] = i;
        }

        for (int i = n - 1; i >= 0; --i) {
            positions[p[i]-1] += insertAndGreaterThan(p[i]);
        }

        int curr = n;
        int cnt = 0;
        while (curr > 1) {
            auto pos = positions[curr-1];
            if (pos != n - curr) {
                if (pos != n -1) {
                    mv[cnt++] = pos;
                    mv[cnt++] = n-curr;
                    mv[cnt++] = n-curr + 1;
                    mv[cnt++] = pos + 1;
                } else {
                    mv[cnt++] = n-curr;
                    mv[cnt++] = n-curr + 1;
                }
            }
            --curr;
        }
        return cnt;
    }
};

SMA solution;
int main() {
    Judge::run(&solution);
    return 0;
}
