#include "judge.h"

//#include <vector>
//#include <iostream>
//using namespace std;

template <typename T>
class vector {
public:

    vector() : capacity(100), m_size(0) {
        arr = new T[capacity];
    }

    T* arr;
    int capacity;

    void clear() {
        m_size = 0;
    }

    void push_back(T el){
        if (m_size == capacity) {
            capacity += 100;
            T* tmp = new T[capacity];
            for (int i = 0; i < m_size; ++i) {
                tmp[i] = arr[i];
            }
            delete [] arr;
            arr = tmp;
        }
        arr[m_size++] = el;
    }

    T& back() {
        return arr[m_size-1];
    }

    void pop_back(){
        m_size--;
    }

    T& operator[](int idx) {
        return arr[idx];
    }

    int size() {
        return m_size;
    }

private:
    int m_size;
};


struct Link {
    int to;
    int distance;
    bool isUsed;
};

struct H {
    H(){};
    H(int ll, int idd) : len(ll), id(idd) {}
    int len = 0;
    int id = 0;
};

struct Sub {
    Sub() {}
    Sub(int ll, int mm, int idd) : len(ll), max_one(mm), id(idd) {}
    int len = 0;
    int max_one = 0;
    int id = 0;
};

class Station {
public:
    int parent = -1;

    vector<Link> nodes;
    int nodes_cnt = 0;
    int nodes_used = 0;

    H h[3];
    Sub sub[2];

    void markUsed(int id) {
        for (int i = 0; i < nodes_cnt; i++) {
            if (nodes[i].to == id) {
                nodes[i].isUsed = true;
                return;
            }
        }
    }

    Link& getUnused() {
        for (int i = 0; i < nodes_cnt; i++) {
            if (!nodes[i].isUsed) {
                return  nodes[i];
            }
        }
        throw 1;
    }

    void addH(H hh) {
        for (int i = 0; i < 3; i++) {
            if (h[i].len < hh.len) {
                for (int j = 2; j > i; j--) {
                    h[j] = h[j-1];
                }
                h[i] = hh;
                break;
            }
        }
    }

    void addSub(Sub ss) {
        for (int i = 0; i < 2; i++) {
            if (sub[i].len + sub[i].max_one < ss.len + ss.max_one) {
                for (int j = 1; j > i; j--) {
                    sub[j] = sub[j-1];
                }
                sub[i] = ss;
                break;
            }
        }
    }
};


Station stations[2000+1];
int NN;

vector<int> queue;
int root = -1;

//void printAll() {
////    cout  << root << endl;
////    cout << queue.size() << endl;
////    for (int i = 1; i <= NN; i++) {
////        cout << i << " ";
////        cout <<"P " << stations[i].parent << " ";
////        cout <<"c " << stations[i].nodes_cnt << " ";
////        cout <<"u " << stations[i].nodes_used << " ";
////        cout <<"h " << stations[i].h[0].id << " ";
////        cout <<"" << stations[i].h[0].len << " ";
////        cout <<"" << stations[i].h[1].id << " ";
////        cout <<"" << stations[i].h[1].len << " ";
////        cout <<"" << stations[i].h[2].id << " ";
////        cout <<"" << stations[i].h[2].len << " ";
////        cout <<"s " << stations[i].sub[0].id << " ";
////        cout <<"" << stations[i].sub[0].len << " ";
////        cout <<"" << stations[i].sub[0].max_one << " ";
////        cout <<"" << stations[i].sub[1].id << " ";
////        cout <<"" << stations[i].sub[1].len << " ";
////        cout <<"" << stations[i].sub[1].max_one << " ";
////        cout << endl;
////    }
//}

struct paczuszka {
    //    int id;
    H h;
    Sub sub;
};

vector<int> xxx;


int mmax = 0;

class PLE : public IPLE {

public:
    int improveNetwork(int N, int *v1, int *v2, int *d) {

        NN = N;
        root = -1;
        mmax = 0;
        xxx.clear();
        queue.clear();

        for(int i = 1; i <= N; i++) {
            stations[i] = Station();
        }

//        printAll();

        for (int i = 0 ; i < N-1; i++) {
            stations[v1[i]].nodes.push_back({v2[i],d[i],false});
            stations[v1[i]].nodes_cnt++;
            stations[v2[i]].nodes.push_back({v1[i],d[i],false});
            stations[v2[i]].nodes_cnt++;
//            printAll();
        }

//        printAll();

        for (int i = 1; i <= N; i++) {
            if (stations[i].nodes_cnt == 1) {
                queue.push_back(i);
            }
        }

//        printAll();

        while (queue.size() != 0) {
//            printAll();
            int id = queue.back();
            queue.pop_back();
            if (stations[id].nodes_used != stations[id].nodes_cnt) {

                auto& free = stations[id].getUnused();
                free.isUsed = true;
                int parent = free.to;
                stations[id].parent = parent;
                int distance = free.distance;
                stations[id].nodes_used++;

                //                for (int i = 0; i < 3; i++) {
                //                    if (stations[parent].h[i].len < stations[id].h[0].len + distance) {
                //                        for (int j = 2; j > i; j--) {
                //                            stations[parent].h[j] = stations[parent].h[j-1];
                //                        }
                //                        stations[parent].h[i].id = id;
                //                        stations[parent].h[i].len = stations[id].h[0].len + distance;
                //                        break;
                //                    }
                //                }

                stations[parent].addH({stations[id].h[0].len + distance,id});

//                printAll();

                int dist = stations[id].sub[0].max_one > distance ? stations[id].sub[0].max_one : distance;
                bool check = stations[id].h[0].len + stations[id].h[1].len + distance >= stations[id].sub->len + dist;

                //                for (int i = 0; i < 2; i++) {
                //                    if (check) {
                //                        if (stations[parent].sub[i].len + stations[parent].sub[i].max_one < stations[id].h[0].len + stations[id].h[1].len + distance) {
                //                            for (int j = 1; j > i; j--) {
                //                                stations[parent].sub[j] = stations[parent].sub[j-1];
                //                            }
                //                            stations[parent].sub[i].id = id;
                //                            stations[parent].sub[i].len =  stations[id].h[0].len + stations[id].h[1].len;
                //                            stations[parent].sub[i].max_one = distance;
                //                            break;
                //                        }
                //                    } else {
                //                        if (stations[parent].sub[i].len + stations[parent].sub[i].max_one < stations[id].sub->len + dist) {
                //                            for (int j = 1; j > i; j--) {
                //                                stations[parent].sub[j] = stations[parent].sub[j-1];
                //                            }
                //                            stations[parent].sub[i].id = id;
                //                            stations[parent].sub[i].len =  stations[id].sub->len;
                //                            stations[parent].sub[i].max_one = dist;
                //                            break;
                //                        }
                //                    }
                //                }

                if (check)
                    stations[parent].addSub({stations[id].h[0].len + stations[id].h[1].len, distance, id});
                else
                    stations[parent].addSub({stations[id].sub->len, dist, id});

//                printAll();
                stations[parent].nodes_used++;
                stations[parent].markUsed(id);
                if (stations[parent].nodes_cnt == stations[parent].nodes_used + 1) {
                    queue.push_back(parent);
                }
//                printAll();
            } else {
                root = id;
            }
        }

//        printAll();

        xxx.push_back(root);

        while (xxx.size() > 0) {
            auto idd = xxx.back();
            xxx.pop_back();
            for (int i = 0; i < stations[idd].nodes_cnt; i++) {
                auto id = stations[idd].nodes[i].to;
                if (id  == stations[idd].parent)
                    continue;

                paczuszka p;
                //            p.id = id;
                if (stations[idd].h[0].id != id) {
                    p.h = stations[idd].h[0];
                    p.h.len += stations[idd].nodes[i].distance;
                    p.h.id = idd;
                } else {
                    p.h = stations[idd].h[1];
                    p.h.len += stations[idd].nodes[i].distance;
                    p.h.id = idd;
                }

                Sub www[5];
                if (id != stations[idd].h[0].id && id != stations[idd].h[1].id) {
                    www[0].len = stations[idd].h[0].len + stations[idd].h[1].len;
                    www[0].max_one = stations[idd].nodes[i].distance;
                    www[0].id = idd;
                }
                if (id != stations[idd].h[0].id && id != stations[idd].h[2].id) {
                    www[1].len = stations[idd].h[0].len + stations[idd].h[2].len;
                    www[1].max_one = stations[idd].nodes[i].distance;
                    www[1].id = idd;
                }
                if(id != stations[idd].h[1].id && id != stations[idd].h[2].id) {
                    www[2].len = stations[idd].h[1].len + stations[idd].h[2].len;
                    www[2].max_one = stations[idd].nodes[i].distance;
                    www[2].id = idd;
                }
                if (stations[idd].sub[0].id != id) {
                    www[3] = stations[idd].sub[0];
                    www[3].max_one = stations[idd].sub[0].max_one > stations[idd].nodes[i].distance ? stations[idd].sub[0].max_one : stations[idd].nodes[i].distance;
                    www[3].id = idd;
                }

                if (stations[idd].sub[1].id != id) {
                    www[4] = stations[idd].sub[1];
                    www[4].max_one = stations[idd].sub[1].max_one > stations[idd].nodes[i].distance ? stations[idd].sub[1].max_one : stations[idd].nodes[i].distance;
                    www[4].id = idd;
                }

                for (int ii = 0; ii < 5; ii++) {
                    if (p.sub.len + p.sub.max_one < www[ii].len + www[ii].max_one) {
                        p.sub = www[ii];
                    }
                }

                stations[stations[idd].nodes[i].to].addH(p.h);
                stations[stations[idd].nodes[i].to].addSub(p.sub);

                xxx.push_back(id);

                int tmp[7] = {0};
                tmp[0] = stations[idd].h[0].len + stations[idd].h[1].len + stations[idd].h[2].len;

                if (stations[idd].sub[0].id != stations[idd].h[0].id && stations[idd].sub[0].id != stations[idd].h[1].id) {
                    tmp[1] = stations[idd].sub[0].len + stations[idd].sub[0].max_one + stations[idd].h[0].len + stations[idd].h[1].len;
                }
                if (stations[idd].sub[0].id != stations[idd].h[0].id && stations[idd].sub[0].id != stations[idd].h[2].id) {
                    tmp[2] = stations[idd].sub[0].len + stations[idd].sub[0].max_one + stations[idd].h[0].len + stations[idd].h[2].len;
                }
                if (stations[idd].sub[0].id != stations[idd].h[1].id && stations[idd].sub[0].id != stations[idd].h[2].id) {
                    tmp[3] = stations[idd].sub[0].len + stations[idd].sub[0].max_one + stations[idd].h[1].len + stations[idd].h[2].len;
                }
                if (stations[idd].sub[1].id != stations[idd].h[0].id && stations[idd].sub[1].id != stations[idd].h[1].id) {
                    tmp[4] = stations[idd].sub[1].len + stations[idd].sub[1].max_one + stations[idd].h[0].len + stations[idd].h[1].len;
                }
                if (stations[idd].sub[1].id != stations[idd].h[0].id && stations[idd].sub[1].id != stations[idd].h[2].id) {
                    tmp[5] = stations[idd].sub[1].len + stations[idd].sub[1].max_one + stations[idd].h[0].len + stations[idd].h[2].len;
                }
                if (stations[idd].sub[1].id != stations[idd].h[1].id && stations[idd].sub[1].id != stations[idd].h[2].id) {
                    tmp[6] = stations[idd].sub[1].len + stations[idd].sub[1].max_one + stations[idd].h[1].len + stations[idd].h[2].len;
                }

                for (int ii = 0; ii < 7; ii++) {
                    if (mmax < tmp[ii]) {
                        mmax= tmp[ii];
                    }
                }
//                printAll();
            }
        }

//        printAll();


        return mmax;
    }
};

PLE solution;
int main() {
    Judge::run(&solution);
    return 0;
}

