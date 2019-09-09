#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "sortmerge.h"
#include "listlinked.h"

using namespace std;

int main()
{

    int arr1[] = {1,4,2,6,3,8,4,5,6,0};
    int arr2[] = {1,4,2,6,3,8,4,5,6,0};

    unsigned arr_size = sizeof (arr1)/sizeof (arr1[0]);

    std::sort(arr1,arr1 + arr_size);
    mergeSort(arr2,0,arr_size-1);

    for (unsigned i = 0; i < arr_size; ++i) {
        if (arr1[i] != arr2[i]) {
            std::cout << "Merde sort asc!" << std::endl;
        }
    }

    std::sort(arr1,arr1 + arr_size,std::greater<int>());
    mergeSort<int>(arr2,0,arr_size-1,[](int a, int b){return a > b;});

    for (unsigned i = 0; i < arr_size; ++i) {
        if (arr1[i] != arr2[i]) {
            std::cout << "Merde sort desc!" << std::endl;
        }
    }


    std::list<int> lst1;
    List<int> lst2;

    auto values = {2,5,4,7,2,3,1};

    for (auto el : values) {
        lst1.push_back(el);
        lst2.push_back(el);
    }

    lst2.pop_back();
    lst1.pop_back();
    lst1.pop_front();
    lst2.pop_front();

    if (lst1.size() != lst2.size()) {
        cout << "List size" << endl;
    }
    {
    auto curr = lst2.begin();
    for (auto itr = lst1.begin(); itr != lst1.end(); itr++, curr = curr->next) {
        if (*itr != curr->value) {
            cout << "List iter!" << endl;
        }
    }

    }



    cout << "Hello World!" << endl;
    return 0;
}
