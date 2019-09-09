#include "judge.h"

//#define DBG
//#include <math.h>
//#include <iostream>
//#include <map>

//#include <chrono>
//using namespace std;

#ifdef DBG
#include <iostream>
using namespace std;
#include <iomanip>

void print(const int *data, int size) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            cout << setw(4) << hex << *(data + size*i + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print(const unsigned char *data, int size) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            cout << setw(4) << hex << (int)*(data + size*i + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
#endif

static const unsigned long long masks[] = {
    0xFFFFFF0000000000,
    0xFFFF0000000000FF,
    0xFF0000000000FFFF,
    0x0000000000FFFFFF
};

#define HashTblSize  249989
#define growSize  2
#define initialCap  6

#define off 2166136261u
#define prime 16777619u

class vector {

    inline void grow() {
        capacity += growSize;
        auto tmp = new unsigned[capacity];
        for (unsigned i = 0; i < size; ++i) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
    }


public:
    unsigned* data;
    unsigned size;
    unsigned capacity;

    vector() : size(0), capacity(initialCap) {
        data = new unsigned[capacity];
    }

    inline void add(unsigned entry) {
        if (size == capacity) {
            grow();
        }

        data[size++] = entry;
        //        ++size;
    }
};

class SK2 : public ISK2 {
public:

    void database(int db[100][100][100]);

    int query(int q[8][8]);

    bool check(int idx, int x, int y, const unsigned char ldata[8][8], int type) const;

    vector hashes[HashTblSize][4];

    int (*gdb)[100][100];
    unsigned char data[100][100][100];

    inline unsigned int hash1x(const unsigned char* data, const int type) {
//        const int exx = type / 4;
        unsigned long long hash = off;
        auto mask = masks[type % 4];

        for (int i = 0; i < 8; ++i, data +=100) {
//            if (i < exx || i > exx + 4) {
                if (i == type) {
                    i += 4;
                    data += 400;
                    continue;
                } else {
                    hash ^= *(const unsigned long long*)(data);
                }
//            } else {
//                hash +=  (*(const unsigned long long*)(data)) & mask;
//            }
            hash *= prime;
            //            hash >>= 3;
        }
        return hash % HashTblSize;
    }

    inline unsigned int hash2x(const unsigned char* data, const int type) {
//        const int exx = type / 4;
        //        const unsigned long long MASK = 0x000FFFFF << (type % 4)*8;
        unsigned long long hash = off;
        auto mask = masks[type % 4];

        for (int i = 0; i < 8; ++i, data += 8) {
//            if (i < exx || i > exx + 4) {
            if (i == type) {
                i += 4;
                data += 32;
                continue;
            } else {
                hash ^= *(const unsigned long long*)(data);
//            } else {
//                hash +=  (*(const unsigned long long*)(data)) & mask;
            }
            hash *= prime;
            //            hash >>= 3;
        }

        return hash % HashTblSize;
    }

    inline unsigned int hash1y(const unsigned char* data, const int type) {
        const int exx = type / 4;
        unsigned long long hash = off;
        auto mask = masks[type % 4];

        for (int i = 0; i < 8; ++i, data +=100) {
//            if (i < exx || i > exx + 4) {
                if (i == exx) {
                    i += 4;
                    data += 400;
                    continue;
                } else {
                    hash ^= *(const unsigned long long*)(data);
                }
//            } else {
//                hash +=  (*(const unsigned long long*)(data)) & mask;
//            }
            hash *= prime;
            //            hash >>= 3;
        }
        return hash % HashTblSize;
    }

    inline unsigned int hash2y(const unsigned char* data, const int type) {
        const int exx = type / 4;
        //        const unsigned long long MASK = 0x000FFFFF << (type % 4)*8;
        unsigned long long hash = off;
        auto mask = masks[type % 4];

        for (int i = 0; i < 8; ++i, data += 8) {
//            if (i < exx || i > exx + 4) {
            if (i == exx) {
                i += 4;
                data += 32;
                continue;
            } else {
                hash ^= *(const unsigned long long*)(data);
//            } else {
//                hash +=  (*(const unsigned long long*)(data)) & mask;
            }
            hash *= prime;
            //            hash >>= 3;
        }

        return hash % HashTblSize;
    }
};

void SK2::database(int db[100][100][100]) {

    gdb = db;

//     auto begin = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            for (int k = 0;k < 100;++k) {
                data[i][j][k] = db[i][j][k];
            }
        }
    }
//    auto end = chrono::high_resolution_clock::now();

//     cout << "cpy: " << dec << "\t" << chrono::duration_cast<chrono::microseconds>(end-begin).count() << endl;

    for (unsigned i = 0; i < 100; ++i) {
        for (unsigned j = 0; j < 93 ; ++j) {
            for (unsigned k = 0;k < 93;++k) {
                for (unsigned cc = 0; cc < 4; ++cc) {
                                        //if (i == 94 && j == 39 && k == 37 && cc == 7) {
//                                            print(&data[i][j][k],100);
//                                            cout << hex <<  hash1x(&data[i][j][k],cc) << endl;
//                                            auto ppp = 1;
//                                        }
                    hashes[hash1x(&data[i][j][k],cc)][cc].add( (i<<16) | (j << 8) | k);
                    //                    hashes[hash1(&data[i][j][k],cc)][cc].add(i*100*100+j*100+k);
                }
            }
        }
    }

//    std::map<int,int> hist;

//    for (auto& vector : hashes) {
//        auto mm = hist.find(vector->size);

//        if (mm != hist.end()) {
//            mm->second++;
//        } else {
//            hist[vector->size] = 1;
//        }
//    }

//    for (auto& pp : hist) {
//        std::cout << pp.first << " " << pp.second << std::endl;
//    }
//    std::cout << std::endl;

}

int SK2::query(int q[8][8]) {

    unsigned char qq[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            qq[i][j] = q[i][j];
        }
    }

//    print(&qq[0][0],8);

    for (int cc = 0; cc < 4; ++cc) {
        auto hash = hash2x(&qq[0][0],cc);
        for (int cc1 = 0; cc1 < 4; ++cc1) {

        for (unsigned i = 0; i < hashes[hash][cc].size; ++i) {
            const auto val = hashes[hash][cc].data[i];
            if (check(val >> 16, (val >> 8) & 0xFF ,val & 0xFF,qq,cc*4 + cc1)) {
                return val >> 16;
            }
        }
        }
    }
    return -1;
}

bool SK2::check(int idx, int x, int y, const unsigned char ldata[8][8], int type) const {

#ifdef DBG
//        bool pp = false;
//        if (idx == 94)
//            pp = true;
//        if (pp) {
//            cout << type << " ->" << endl;
//            print(&ldata[0][0],8);
//            print(&data[idx][x][y],100);
//            cout << "->" << endl;
//        }
#endif
    const int exx = type / 4;
    auto mask = masks[type % 4];
    const unsigned char* dataStart = &data[idx][x][y];
    const unsigned char* ldataStart = &ldata[0][0];
    for (int i = 0; i < 8; ++i, dataStart += 100, ldataStart+=8) {
        if (i < exx || i > exx + 4) {
//                            if (pp) {
//                        cout << setw(20) << hex << (*(const unsigned long long *)(ldataStart)) << endl;
//                        cout << setw(20) << hex << (*(const unsigned long long *)(dataStart)) << endl;
//                            }
            if ((*(const unsigned long long *)(ldataStart)) ^ (*(const unsigned long long *)(dataStart))) {
                return false;
            }

        } else {
//                            if (pp) {
//                        cout << setw(20) << hex << (*(const unsigned long long *)(ldataStart)) << endl;
//                        cout << setw(20) << hex << (*(const unsigned long long *)(dataStart)) << endl;
//                        cout << setw(20) << hex << ((*(const unsigned long long *)(ldataStart)) ^ (*(const unsigned long long *)(dataStart))) << endl;
//                        cout << setw(20) << hex << mask << endl;
//                                        }
            if (((*(const unsigned long long *)(ldataStart)) ^ (*(const unsigned long long *)(dataStart))) & mask) {
                return false;
            }

        }
    }
#ifdef DBG
    cout << endl;
#endif
    return true;
}

SK2 solution;
int main() {
    Judge::run(&solution);
    return 0;
}

