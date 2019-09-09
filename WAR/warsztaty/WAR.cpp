#include "judge.h"

#include <iostream>
using namespace std;

static const int MAX_SHOPS = 5;
static const int MAX_ID = 20000000;
static const int SWT_LEVELS = 5;
static const int MAX_PARTICIPANTS = 100000;

static const int MAX_RANK = 5*MAX_ID;// - 1;

static int shops_ctn =0;
static int shops_capacity =0;

struct User {
    User() = default;
    User(int id, const char * level, int prefs[]) : current(-1) {
        switch (level[0]) {
        case 'e': {
            rank = 4*MAX_ID + (MAX_ID-id);
            break;
        }
        case 'p': {
            rank = 3*MAX_ID + (MAX_ID-id);
            break;
        }
        case 'a': {
            rank = 2*MAX_ID + (MAX_ID-id);
            break;
        }
        case 'i': {
            rank = 1*MAX_ID + (MAX_ID-id);
            break;
        }
        case 'n': {
            rank = (MAX_ID-id);
            break;
        }
        }
        for (int i = 0; i < shops_ctn; ++i) {
            this->prefs[i] = static_cast<char>(prefs[i]);
        }
    }

    static int invRank(int param) { return MAX_RANK - param;}

    int rank;
    char current;
    char prefs[MAX_SHOPS];
};

static User* usersRegister[MAX_ID+1];

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MinHeap
{
    int harr[4*MAX_PARTICIPANTS]; // pointer to array of elements in heap
    int capacity = 4*MAX_PARTICIPANTS; // maximum possible size of min heap
public:
    int heap_size = 0; // Current number of elements in min heap
    // to heapify a subtree with the root at given index
    void MinHeapify(int );

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    int extractMin();

    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap
    int getMin() { return harr[0]; }

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Inserts a new key 'k'
    void insertKey(int k);
};

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
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

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
    swap(&harr[i], &harr[parent(i)]);
    i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return 2000000000;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}

void MinHeap::deleteKey(int i)
{
    decreaseKey(i, -1);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
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
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// stores rank
static MinHeap shops[MAX_SHOPS];

// stores inv rank
static MinHeap reserves[MAX_SHOPS];

class WAR : public iWAR {
public:
    virtual void init(int workshopsNum, int maxParticipants);
    virtual int registration(int byteid, char level[], int preferences[]);
    virtual int unregistration(int byteid);
};

extern void setTestCase(int);

int main() {

////    cout << sizeof (User) << endl;
////    cout << sizeof(usersRegister)/1024.0/1024.0 << endl;
////    cout << sizeof(Bucket) << endl;
////    cout << sizeof(buckets)/1024.0/1024.0 << endl;
////    cout << sizeof(workshop) << endl;
////    cout << sizeof(shops)/1024.0/1024.0 << endl;

//    cout << sizeof(usersRegister)/1024.0/1024.0  + sizeof(buckets)/1024.0/1024.0 << endl;

    WAR w;

    long sum = 0;
    auto testsCases = {0,1,2,10,11,12,13,20,30};
    auto nrOfPasses = 100;
    long max = 0;

    for (int i = 0; i < nrOfPasses; ++i) {
        cout << i << "\t";
        for (auto t : testsCases) {
            setTestCase(t);
            long time = judge::run(&w);
            cout << time << " ";
            if (time > max) {
                max = time;
            }
            if (t >= 2) {
                sum += time;
            }
        }
        cout << endl;
    }
    cout << endl << "Avg: " <<  sum / 6 / nrOfPasses << " MAX: " << max << endl;
}

//void printShops() {
//    for (int i = 0; i < shops_ctn; ++i) {
//        cout << "Shop: " << i << "\tCnt: " << shops[i].cnt << endl;
//        shops[i].users.printAsc();
//    }
//}

//void check() {
//    for (int i = 0; i < MAX_ID; i++) {
//        auto user = usersRegister[i];
//        bool tmp = false;
//        if (user && user->current >= 0) {
//            for (auto pref : user->prefs) {
//                if (pref == user->current) {
//                    auto findRes = shops[pref].users.myFind(user->rank);
//                    if (!findRes) {
//                        int ddd = 0;
//                    }
//                    findRes = reserves[pref].myFind(user->rank);
//                    if (findRes) {
//                        int ddd = 0;
//                    }
//                    tmp = true;
//                } else {
//                    auto findRes = shops[pref].users.myFind(user->rank);
//                    if (findRes) {
//                        int ddd = 0;
//                    }
//                    findRes = reserves[pref].myFind(user->rank);
//                    if ((findRes == nullptr) ^ tmp) {
//                        int ddd = 0;
//                    }
//                }
//            }
//        }
//    }
//}

//void printUserState(int id) {
//    auto user = usersRegister[id];
//    for (int i = 0; i < shops_ctn; i++) {
//        if (shops[i].users.myFind(user->rank)) {
//            cout << "1 ";
//        } else {
//            cout << "0 ";
//        }

//        if (reserves[i].myFind(user->rank)) {
//            cout << "1 ";
//        } else {
//            cout << "0 ";
//        }
//        cout << endl;
//    }
//}

void WAR::init(int workshopsNum, int maxParticipants){
    for (int i = 0; i < MAX_SHOPS; i++) {
        while (shops[i].heap_size > 0) {
            shops[i].extractMin();
        }

        while (reserves[i].heap_size) {
            reserves[i].extractMin();
        }
    }

    for (int i = 0; i <= MAX_ID; ++i) {
        if (usersRegister[i]) {
            delete usersRegister[i];
            usersRegister[i] = nullptr;
        }
    }

    shops_ctn = workshopsNum;
    shops_capacity = maxParticipants;
}

int WAR::registration(int byteid, char level[], int preferences[]) {

    usersRegister[byteid] = new User(byteid,level,preferences);

    auto& user = *usersRegister[byteid];

    for (auto pref : user.prefs) {
        if (shops[static_cast<int>(pref)].heap_size < shops_capacity) {
            shops[static_cast<int>(pref)].insertKey(user.rank);
            user.current = pref;
            break;
        }

        int to_move = 0;
        if (shops[static_cast<int>(pref)].getMin() < user.rank) {
            to_move = shops[static_cast<int>(pref)].getMin();
            shops[static_cast<int>(pref)].deleteKey(to_move);
            shops[static_cast<int>(pref)].insertKey(user.rank);
            user.current = pref;
        }

        while(to_move) {
            auto id =  MAX_ID - (to_move % (MAX_ID));
            auto& user2 = *usersRegister[id];
            for (auto pref2 : user2.prefs) {
                if (shops[static_cast<int>(pref2)].heap_size < shops_capacity) {
                    shops[static_cast<int>(pref2)].insertKey(user2.rank);
                    user2.current = pref2;
                    to_move = 0;
                    break;
                }

                if (shops[static_cast<int>(pref2)].getMin()  < user2.rank) {
                    int to_move2 = shops[static_cast<int>(pref2)].getMin();
                    shops[static_cast<int>(pref2)].deleteKey(to_move2);
                    shops[static_cast<int>(pref2)].insertKey(user2.rank);
                    user2.current = pref2;
                    to_move = to_move2;
                    break;
                }
                reserves[static_cast<int>(pref2)].insertKey(User::invRank(to_move));
            }
        }

        if (user.current < 0)
            reserves[static_cast<int>(pref)].insertKey(User::invRank(user.rank));
        else
            break;
    }
    return user.current;
}

int WAR::unregistration(int byteid) {
    auto& user = *usersRegister[byteid];

    for (auto pref : user.prefs) {
        if (pref == user.current) {
            shops[static_cast<int>(pref)].deleteKey(user.rank);

            while (reserves[static_cast<int>(pref)].heap_size > 0) {
                int to_move = User::invRank(reserves[static_cast<int>(pref)].getMin());
                auto id =  MAX_ID - (to_move % (MAX_ID));
                auto& user_to_move = *usersRegister[id];

                bool start_removing = false;
                for (auto pref2 : user_to_move.prefs) {
                    if (pref2 == pref) {
                        start_removing = true;
                        shops[static_cast<int>(pref2)].insertKey(to_move);
                    }

                    if (pref2 == user_to_move.current) {
                        shops[static_cast<int>(pref2)].deleteKey(to_move);
                        user_to_move.current = pref;
                        pref = pref2;
                        break;
                    }

                    if (start_removing) {
                        reserves[static_cast<int>(pref2)].deleteKey(User::invRank(to_move));
                    }
                }
            }
            break;
        } else {
            reserves[pref].deleteKey(User::invRank(user.rank));
        }
    }
    return user.current;
}
