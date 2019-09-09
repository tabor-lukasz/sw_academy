#ifndef HEAP_H
#define HEAP_H


#define HEAP_SIZE 100000*25

void swap(int *x, int *y);

// A class for Min Heap
template <typename T>
class MinHeap
{
    const int capacity = HEAP_SIZE; // maximum possible size of min heap
    T harr[HEAP_SIZE]; // pointer to array of elements in heap

public:
    MinHeap(){}
    int heap_size = 0; // Current number of elements in min heap
    // to heapify a subtree with the root at given index
    void MinHeapify(int );

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    T extractMin();

    // Decreases key value of key at index i to new_val
//    void decreaseKey(int i, T new_val);

    // Returns the minimum key (key at root) from min heap
    T getMin() { return harr[0]; }

    // Deletes a key stored at index i
//    void deleteKey(int i);

    // Inserts a new key 'k'
    void insert(T k) {
        if (heap_size == capacity)
        {
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
};

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
//template <class T>
//void MinHeap<T>::decreaseKey(int i, T new_val)
//{
//    harr[i] = new_val;
//    while (i != 0 && harr[parent(i)] > harr[i])
//    {
//    swap(&harr[i], &harr[parent(i)]);
//    i = parent(i);
//    }
//}

// Method to remove minimum element (or root) from min heap
template <class T>
T MinHeap<T>::extractMin()
{
    if (heap_size <= 0)
        return T();
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    T root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}

//template <class T>
//void MinHeap<T>::deleteKey(int i)
//{
//    decreaseKey(i, T::getMinimum());
//    extractMin();
//}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
template <class T>
void MinHeap<T>::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
template <class T>
void swap(T *x, T *y)
{
    T temp = *x;
    *x = *y;
    *y = temp;
}

#endif // HEAP_H
