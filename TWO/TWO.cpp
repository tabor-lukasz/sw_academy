#include "judge.h"
//#include <algorithm>
//#include <iostream>
//#include <iomanip>
//#include <list>
//#include <vector>

//using namespace std;

const int MAX_SUM = 32768;
const int MAX_N = 128;
static int table[MAX_N][MAX_SUM+1];
int excluded[MAX_N];
int checkId = 2;
int excludeId = 2;

template <typename T>
void merge(T arr[], int l, int m, int r, bool oper(T a, T b))
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    T L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if ( oper(L[i],R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(T arr[], int l, int r, bool oper(T a, T b) = [](T a, T b){return a < b;})
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m, oper);
        mergeSort(arr, m+1, r, oper);

        merge(arr, l, m, r,oper);
    }
}

template <typename T>
class List {

    template<typename K>
    class ListNode {
    public :

        ListNode() {}
        ListNode(const K& other) {
            value = other;
        }

        K value;
        ListNode* next = nullptr;
        ListNode* prev = nullptr;
    };

public:

    ~List() {
        while(!empty()) {
            pop_front();
        }
    }

    bool empty() const {
        return root == nullptr;
    }

    void push_back(const T& element) {
        if (!root) {
            last = root = new ListNode<T>(element);
        } else {
            last->next = new ListNode<T>(element);
            last->next->prev = last;
            last = last->next;
        }
        ++_size;
    }

    void push_front(const T& element) {
        if (!root) {
            last = root = new ListNode<T>(element);
        } else {
            root->prev = new ListNode<T>(element);
            root->prev->next = root;
            root = root->prev;
        }
        ++_size;
    }

    T front() {
        return root->value;
    }

    T back() {
        return last->value;
    }

    void pop_front() {
        if (root) {
            auto tmp = root;
            if (root->next) {
                root->next->prev = nullptr;
            }
            root = root->next;

            --_size;
            if (_size == 0) {
                last = nullptr;
            }

            delete tmp;
        }
    }

    void pop_back() {
        if (last) {
            auto tmp = last;
            if (last->prev) {
                last->prev->next = nullptr;
            }
            last = last->prev;

            --_size;
            if (_size == 0) {
                root = nullptr;
            }

            delete tmp;
        }
    }

    unsigned size() const {return _size;}

    ListNode<T>* begin() const {
        return root;
    }

    void erase(ListNode<T>* element) {
        if (element == root) {
            pop_front();
            return;
        }

        if (element == last) {
           pop_back();
            return;
        }

        element->next->prev = element->prev;
        element->prev->next = element->next;
        delete element;
        --_size;
    }

private:
    ListNode<T>* root = nullptr;
    ListNode<T>* last = nullptr;
    unsigned _size = 0;
};

//void print(int n, int sum, const int* h) {
//    cout << setw(3) << " "<< "  ";
//    for (int j = 0; j <= sum/2; ++j) {
//        cout << setw(3) <<  j << " ";
//    }
//    cout << endl;
//    for (int i = 0; i < n; ++i) {
//        cout << setw(3) << h[i] << ": ";
//        for (int j = 0; j <= sum/2; ++j) {
//            cout << setw(3) <<  table[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//}

void solveRucksack(int n, int sum, const int *h) {

    if (sum > MAX_SUM)
        throw "2323";

    checkId++;
    for (int i = 0;i <= sum;++i) {
        table[0][i] = 0;
    }
    table[0][0] = checkId;
    table[0][h[0]] = checkId;
    for (int i = 1;i < n;++i) {
        table[i][0] = checkId;
        for (int j = 1;j <= sum;++j) {
            if (j < h[i]) {
                table[i][j] = table[i-1][j];
            } else if(table[i-1][j] || table[i-1][j-h[i]]) {
                table[i][j] = checkId;
            } else {
                table[i][j] = 0;
            }
        }
    }
}

void exclude(int n, int sum, const int *h) {
    ++excludeId;

    int currentSum = sum/2;
    int currentN = n-1;

    while (currentSum > 0) {
        if (!currentN || (table[currentN-1][currentSum] == 0)) {
            excluded[currentN] = excludeId;
            currentSum -= h[currentN];
        }
        --currentN;
    }

    if (currentSum != 0)
        throw 234;
}

bool checkRucksack(int n, int target, const int *h) {
    ++checkId;
    int currentSum = target/2;
    int currentN = n-1;

    struct node {
        int sum;
        int n;
    };

    List<node> nodes;

    while (table[currentN][currentSum] && excluded[currentN] != excludeId) {
            nodes.push_back({currentSum,currentN--});
    }

    while (!nodes.empty()) {
        node n = nodes.front();
        if (n.sum - h[n.n] == 0) {
            return true;
        }
        nodes.pop_front();

        int next = n.n -1;
        int newSum = n.sum - h[n.n];
        if (newSum < 0) {
            continue;
        }
        while (next >= 0) {
            if (table[next][newSum] == 0) {
                break;
            }

            if (excluded[next] != excludeId) {
                if (table[next][newSum] != checkId) {
                    table[next][newSum] = checkId;
                    nodes.push_back({newSum,next});
                }
            }
            --next;
        }
    }
    return false;

}

int ccc = 0;

class TWO : public ITWO {
public:
    int getMaxTowerHeight(int n, int *h) {

        mergeSort<int>(h,0,n-1,[](int a, int b){return a>b;});


        int sum = 0;
        for (int i = 0;i<n;++i) {
            sum += h[i];
        }
        sum = (sum/2)*2;

        solveRucksack(n,sum,h);

        while (sum > 0) {
            if (table[n-1][sum] && table[n-1][sum/2] && table[n-2][sum/2]) {
                exclude(n,sum,h);
                if (checkRucksack(n,sum,h)) {
                    return sum/2;
                }
            }
            sum -=2;
        }
        return 0;
    }
};

TWO solution;
int main() {
    Judge::run(&solution);
    return 0;
}

