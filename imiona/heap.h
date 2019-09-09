#ifndef HEAP_H
#define HEAP_H

#include "utils.h"

//static int helpersCount;

struct substHelper {
    char substr[8];
    int fitst_name_idx;

    inline bool operator<(const substHelper& other) {
        return isLoginLesser(substr,other.substr);
    }

    inline bool operator>=(const substHelper& other) {
        return !isLoginLesser(substr,other.substr);
    }
};


static substHelper heap[32768*9];
static int heap_size = 0;

inline int heapParent(int v)
{
    return (v-1) / 2;
}

inline int heapLeftChild(int v)
{
    return 2 * v + 1;
}


inline int heapRightChild(int v)
{
    return 2 * v + 2;
}

//wstawia podana wartosc do kopca
void Insert (substHelper x)
{
    heap[heap_size] = x;
    heap_size++;
    int v = heap_size;
    while (v != 0 &&  heap[heapParent(v)] < heap[v])
    {
        substHelper tmp = heap[v];
        heap[v] = heap[heapParent(v)];
        heap[heapParent(v)] = tmp;
        v= heapParent(v);
    }
}

//Usuwa wierzcholek kopca
substHelper Remove()
{
//    if (pos==0)
//        return;

    substHelper rval =heap[0];

    heap[0] = heap[heap_size];
    heap_size--;

    int v = 1;
    while(true) {
        if (heapLeftChild(v) > heap_size)
            break;
//        auto a = heap[heapLeftChild(v)];
        if (heapRightChild(v) > heap_size) {
            if (heap[v] >= heap[heapLeftChild(v)])
                break;
            substHelper tmp = heap[v];
            heap[v] = heap[heapLeftChild(v)];
            heap[heapLeftChild(v)] = tmp;
            v=heapLeftChild(v);
        }
        else if (heap[heapRightChild(v)] < heap[heapLeftChild(v)]) {
            if (heap[v] >= heap[heapLeftChild(v)])
                break;
            substHelper tmp = heap[v];
            heap[v] = heap[heapLeftChild(v)];
            heap[heapLeftChild(v)] = tmp;
            v=heapLeftChild(v);
        }
        else {
            if (heap[v] >= heap[heapRightChild(v)])
                break;
            substHelper tmp = heap[v];
            heap[v] = heap[heapRightChild(v)];
            heap[heapRightChild(v)] = tmp;
            v=heapRightChild(v);
        }
    }

    return rval;
}

#endif // HEAP_H
