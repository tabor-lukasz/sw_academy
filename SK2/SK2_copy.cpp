//#include "judge.h"

//#define DBG

//#ifdef DBG
//#include <iostream>
//using namespace std;
//#include <iomanip>

//void print(const int *data, int size) {
//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8 ; ++j) {
//            cout << setw(10) << *(data + size*i + j) << " ";
//        }
//        cout << endl;
//    }

//    cout << endl;
//}


//#endif

//static const unsigned HashTblSize = 249989;

//class vector {

//    inline void grow() {
//        capacity += 1;
//        auto tmp = new int[capacity];
//        for (int i = 0; i < size; ++i) {
//            tmp[i] = data[i];
//        }
//        delete[] data;
//        data = tmp;
//    }


//public:

//    int* data;
//    int size;
//    int capacity;

//    vector() : size(0), capacity(1) {
//        data = new int[capacity];
//    }

////    ~vector() {
////        delete [] data;
////    }

//    inline void add(int entry) {
//        if (size == capacity) {
//            grow();
//        }

//        data[size] = entry;
//        ++size;
//    }

//};

//const unsigned off = 2166136261;
//const unsigned prime = 16777619;

//inline unsigned int hash1(const int* data, int type) {
//    const int exx = type / 4;
//    const int exy = type % 4;

//    unsigned long long hash = off;

//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8 ; ++j) {
//            if (j == exy && i >= exx && i <= exx + 4) {
//                j += 4;
//                continue;
//            }
////            if ( (i < exx) | (i > exx + 4)) {
//                hash ^= data[i*100+j];
//                hash *= prime;
////            }
//        }
//    }
//    return hash % HashTblSize;
//}

//inline unsigned int hash2(const int* data, int type) {
//    const int exx = type / 4;
//    const int exy = type % 4;

//    unsigned long long hash = off;

//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8 ; ++j) {
//            if (j == exy && i >= exx && i <= exx + 4) {
//                j += 4;
//                continue;
//            }
////            if ( (i < exx) | (i > exx + 4)) {
//                hash ^= data[i*8+j];
//                hash *= prime;
////            }
//        }
//    }
//    return hash % HashTblSize;
//}

//class SK2 : public ISK2 {
//public:

//    void database(int db[100][100][100]);

//    int query(int q[8][8]);

//    inline bool check(int idx, int x, int y, const int ldata[8][8], int type) const;

//    vector hashes[HashTblSize][16];

//    int (*gdb)[100][100];
//    unsigned char data[100][100][100];
//};

//void SK2::database(int db[100][100][100]) {

////    unsigned xxx = sizeof (hashes);
////    auto xxx1 = xxx /1024;
////    auto xxx2 = xxx1 /1024;

//    gdb = db;

//    for (int i = 0; i < 100; ++i) {
//        for (int j = 0; j < 100; ++j) {
//            for (int k = 0;k < 100;++k) {

//            }
//        }
//    }

//    for (int i = 0; i < 100; ++i) {
//        for (int j = 0; j < 93 ; ++j) {
//            for (int k = 0;k < 93;++k) {
//                for (int cc = 0; cc < 16; ++cc) {
//                    hashes[hash1(&db[i][j][k],cc)][cc].add(i*100*100+j*100+k);
//                }
//            }
//        }
//    }
//}

//int SK2::query(int q[8][8]) {

//    for (int cc = 0; cc < 16;++cc) {
//        auto hash = hash2(&q[0][0],cc);

//        for (int i = 0; i < hashes[hash][cc].size; ++i) {
//            const auto val = hashes[hash][cc].data[i];
//            const unsigned idx = val / 10000;
//            if (check(idx,(val % 10000) / 100,val % 100,q,cc)) {
//                return idx;
//            }
//        }
//    }
//    return -1;
//}

//inline bool SK2::check(int idx, int x, int y, const int ldata[8][8], int type) const {

//    const int exx = type / 4;
//    const int exy = type % 4;

//#ifdef DBG
//    cout << "->" << endl;
//    print(&ldata[0][0],8);
//    print(&gdb[idx][x][y],100);
//    cout << "->" << endl;
//#endif

//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8; ++j) {
//            if (j == exy && i >= exx && i <= exx + 4) {
//                j += 4;
//                continue;
//            }
////            if ( (i < exx) | (i > exx + 4)) {
//                if (gdb[idx][x+i][y+j] != ldata[i][j]) {
//                    return false;
//#ifdef DBG
//                } else  {
//                    cout << ldata[i][j] << " ";
//#endif
//                }
////            }
//        }
//#ifdef DBG
//        cout << endl;
//#endif
//    }



//    return true;

//}

//SK2 solution;
//int main() {
//	Judge::run(&solution);
//	return 0;
//}

