#include "judge.h"

//#define DBG
#ifdef DBG
#include <iostream>
using namespace std;
#endif

int positions[5000];
//int offsets[5000];
int tmp[5000];
int nn;

#ifdef DBG
int tmp_dbg[5000];
int *pp;
#endif

#ifdef DBG
void swap(int idx1) {
    for (int i = idx1; i < nn; ++i) {
        tmp_dbg[i] = pp[i];
    }

    for (int i = idx1; i < nn; ++i) {
        pp[i] = tmp_dbg[nn - i -1 + idx1];
    }

    for (int  i =0; i < nn; i++) {
        cout << pp[i] << " ";
    }
    cout << endl;
}
#endif

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

class PYS : public IPYS {
public:
	int sortPancakes(int n, int *p, int *mv) {


#ifdef DBG
        pp = p;
        for (int i = 0; i < n; ++i) {
            cout << p[i] << " ";
        }
        cout << endl;
#endif
        nn = n;
        for (int i = 0; i < n; ++i) {
            tmp[i] = 0;
            positions[p[i]-1] = i;
//            offsets[i] = 0;
        }

        for (int i = n - 1; i >= 0; --i) {
            positions[p[i]-1] += insertAndGreaterThan(p[i]);
//            offsets[p[i]-1] = insertAndGreaterThan(p[i]);
        }

#ifdef DBG
        cout << endl;
        for (int i = 0; i < n; ++i) {
            cout << p[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << positions[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << offsets[i] << " ";
        }
        cout << endl;
        cout << endl;
#endif

        int curr = n;
        int cnt = 0;
        while (curr > 1) {
//            auto pos = positions[curr-1] + offsets[curr-1];
            auto pos = positions[curr-1];
            if (pos != n - curr) {
                if (pos != n -1) {
                    mv[cnt++] = pos;
#ifdef DBG
                    swap(pos);
#endif
                    mv[cnt++] = n-curr;
#ifdef DBG
                    swap(n-curr);
#endif
                    mv[cnt++] = n-curr + 1;
#ifdef DBG
                    swap(n-curr + 1);
#endif
                    mv[cnt++] = pos + 1;
#ifdef DBG
                    swap(pos + 1);
#endif
                } else {
                    mv[cnt++] = n-curr;
#ifdef DBG
                    swap(n-curr);
#endif
                    mv[cnt++] = n-curr + 1;
#ifdef DBG
                    swap(n-curr + 1);
#endif
                }
            }
            --curr;
        }
#ifdef DBG
        cout << endl;
        cout << endl;
#endif

        return cnt;
	}
};

PYS solution;
int main() {
	Judge::run(&solution);
	return 0;
}

