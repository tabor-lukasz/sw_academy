#ifndef HEAP_H
#define HEAP_H

// Prototype of a utility function to swap two integers
template<typename T> void swap(T *x, T *y) {
    T temp = *x;
    *x = *y;
    *y = temp;
}

// A class for HEAP
template<typename T>
class Heap
{
    const int capacity;
    T* harr; // pointer to array of elements in heap
public:

    Heap(int maxSize, bool isMin = true) : capacity(maxSize) {
        harr = new T[capacity];
    }

    ~Heap() {delete[] harr;}

    int heap_size = 0; // Current number of elements in min heap
    // to heapify a subtree with the root at given index
    void Heapify(int );

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    T extractRoot();

    // Decreases key value of key at index i to new_val
    void changeKey(int i, int T);

    // Returns the minimum key (key at root) from min heap
    T getRoot() { return harr[0]; }

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Inserts a new key 'k'
    void insertKey(T k);
};

// Inserts a new key 'k'
void Heap::insertKey(T k)
{
    if (heap_size == capacity)
    {
        throw 2;
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

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void Heap::changeKey(int i, T new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
T Heap::extractRoot()
{
    if (heap_size < 1)
        throw 1;

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    auto root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    Heapify(0);

    return root;
}

void Heap::deleteKey(int i)
{
    changeKey(i, T::getMinPossible());
    extractRoot();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void Heap::Heapify(int i)
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
        Heapify(smallest);
    }
}

#endif // HEAP_H
