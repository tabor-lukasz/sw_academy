//#include "judge.h"


//#include <ctime>

//#include <iostream>


//static char all[] = "qwertyuiopasdfghjklzxcvbnm";

//static char nextCh[26];

//static char prevCh[26];


//static int resCnt = 0;

//static int resIdx[65536];

//static char my_names[32768][16];

//static char my_names_buffer[32768][16];

//static char my_logins[65536][8];


//struct node;


////solution2

//struct sub_name_info {

//    //char str[8];

//    int name_idx;

//    int offset;

//};


//static sub_name_info sub_names[32768 * 9];

//static sub_name_info sub_names_buffer[32768 * 9];


//inline bool equalsLogin(const char* s1, const char* s2) {

//    return *reinterpret_cast<const long long*>(s1) == *reinterpret_cast<const long long*>(s2);

//}


//inline bool equalsName(const char* s1, const char* s2) {

//    return *reinterpret_cast<const long long*>(s1) == *reinterpret_cast<const long long*>(s2) &&

//           *reinterpret_cast<const long long*>(s1 + 8) == *reinterpret_cast<const long long*>(s2 + 8);

//}


//inline bool isNameLesser(const char* s1, const char* s2) {

//    for (int i = 0; i < 16; ++i) {

//        if (s1[i] > s2[i]) {

//            return false;

//        } else if (s1[i] < s2[i]) {

//            return true;

//        }

//    }

//    return true;

//}


//inline bool isLoginLesser(const char* s1, const char* s2) {

//    for (int i = 0; i < 8; ++i) {

//        if (s1[i] > s2[i]) {

//            return false;

//        } else if (s1[i] < s2[i]) {

//            return true;

//        }

//    }

//    return true;

//}


//struct CacheNode {

//    CacheNode(int _l_idx,int _n_idx) : l_idx(_l_idx), n_idx(_n_idx) { }


//    inline void add(int l_idx,int n_idx) {

//        if (!next) {

//            next = new CacheNode(l_idx,n_idx);

//        } else {

//            next->add(l_idx,n_idx);

//        }

//    }


//    inline int get(const char *s) {

//        if (equalsLogin(s,my_logins[l_idx])) {

//            return n_idx;

//        }


//        if (!next)

//            return -1;

//        else

//            return next->get(s);

//    }


//    CacheNode* next = nullptr;

//    int l_idx;

//    int n_idx;

//    //int size = 1;

//};


////struct listNode {

////    listNode* next = nullptr;

////    listNode* prev = nullptr;


////    sub_name_info info;

////};


//static const unsigned cache_size = 256*256;

//static const unsigned cache_mask = cache_size - 1;

//static CacheNode* solved[cache_size];


////inline void swap(int* a, int* b) {

////    tmp = *a;

////    *a = *b;

////    *b = tmp;

////}


////void mergeSort(int* data,int size) {

////    int tmp = 2;

////    while (tmp <= size) {

////        for (int i = 0; i < size/tmp; ++i) {

////            int begin = data +i*tmp;

////            int mid1 = begin + tmp;

////            int mid2 = mid1 + 1;

////            int end = begin + 2*tmp;


////            while (begin <= mid1 || mid2 <= end) {

////                if (begin <= mid1 && *begin <= *end) {

////                    ++begin;

////                } else {


////                }

////            }


////        }

////        tmp *=2;

////    }

////}


//// initialize allowed typo errors

//void init() {

//    for (char c = 'a'; c <= 'z'; ++c) {

//        int index = -1;

//        for (int i = 0; i < 26; ++i) {

//            if (all[i] == c) {

//                index = i;

//                break;

//            }

//        }

//        if (index == 0 || index == 10 || index == 19) {

//            prevCh[c-'a'] = 0;

//        } else {

//            prevCh[c-'a'] = all[index-1];

//        }


//        if (index == 9 || index == 18 || index == 25) {

//            nextCh[c-'a'] = 0;

//        } else {

//            nextCh[c-'a'] = all[index+1];

//        }

//    }

//}


//inline void toLower(char* login) {

//    for (int i = 0; i < 8; ++i) {

//        if (login[i] < 'a') {

//            login[i] = login[i] - 'A' + 'a';

//        }

//    }

//}


//inline bool tryToMatch(const char* login, const char* name) {

//    for (int j = 0; j < 9; ++j) {

//        bool matched = true;

//        for (int i = 0; i < 8; ++i) {

//            if (login[i] != name[i + j] && nextCh[login[i] - 'a'] != name[i + j] && prevCh[login[i] - 'a'] != name[i + j]) {

//                matched = false;

//                break;

//            }

//        }

//        if (matched)

//            return true;

//    }

//    return false;

//}


//inline bool tryToMatch2(const char* login, const char* name) {

//        bool matched = true;

//        for (int i = 0; i < 8; ++i) {

//            if (login[i] != name[i] && nextCh[login[i] - 'a'] != name[i] && prevCh[login[i] - 'a'] != name[i]) {

//                matched = false;

//                break;

//            }

//        }

//        return matched;

//}


//inline int findFirstName() {

//    int first = resIdx[0];

//    for (int i = 1; i < resCnt; ++i) {

//        for (int j = 0; j < 16; ++j) {

//            if (my_names[first][j] > my_names[resIdx[i]][j]) {

//                first = resIdx[i];

//                break;

//            }

//        }

//    }

//    return first;

//}


//inline unsigned int getHash16(const char *login) {

//    unsigned int h = 0;

//    for (int i = 0; i < 8; ++i, ++login)

//        h = h*23131 + (unsigned char)*login;

//    return (h & cache_mask);

//}


//inline void cpyName(const char* src, char* dest) {

//    auto srcI = reinterpret_cast<const int*>(src);

//    auto destI = reinterpret_cast<int*>(dest);

//    for (int i = 0; i < 4; ++i) {

//        *destI = *srcI;

//    }

//}


//void sortNames(int start, int end) {

//    if (start == end)

//        return;


//    int begin = start;

//    int len = end - start + 1;

//    int mid1 = (end + start)/2;

//    int mid2 = mid1 + 1;


//    sortNames(start,mid1);

//    sortNames(mid2,end);


//    int current = 0;


//    while(begin <= mid1 && mid2 <= end) {

//        if (isNameLesser(my_names[begin], my_names[mid2])) {

//            cpyName(my_names[begin++],my_names_buffer[current++]);

//        } else {

//            cpyName(my_names[mid2++],my_names_buffer[current++]);

//        }

//    }


//    while (begin <= mid1) {

//        cpyName(my_names[begin++],my_names_buffer[current++]);

//    }


//    while(mid2 <= end) {

//        cpyName(my_names[mid2++],my_names_buffer[current++]);

//    }


//    for (int i = 0; i < len; ++i) {

//        cpyName(my_names_buffer[i],my_names_buffer[start + i]);

//    }

//}


//extern void re_init(int l_div, int n_div, int n_rnd );


//void solution1();

//void solution0();

//void solution2();


//int main()

//{

////    // initialize typo helpers

////    init();


////    // make a copy of names to avoid copy on Judge::getCitizenName

////    for (int i = 0; i < Judge::getPopulation(); ++i) {

////        Judge::getCitizenName(i,my_names[i]);

////    }


////    for (int i = 0; i < Judge::getQueryCount(); ++i) {


////        // get current querry

////        Judge::getCitizenLogin(my_logins[i]);


////        // lowercase login

////        toLower(my_logins[i]);


////        auto hash = getHash16(my_logins[i]);


////        // check if any solution for given hash exists

////        if (solved[hash]) {

////            // check if solution for given login exists

////            int answer = solved[hash]->get(my_logins[i]);

////            if (answer >= 0) {

////                Judge::replyCitizenName(my_names[answer]);

////                continue;

////            }

////        }


////        // login not solved before

////        resCnt = 0;

////        for (int j = 0; j < Judge::getPopulation(); ++j) {


////            // name matched, store index

////            if (tryToMatch(my_logins[i],my_names[j])) {

////                resIdx[resCnt++] = j;

////            }

////        }


////        int answer = findFirstName(/*resCnt,resIdx,my_names*/);


////        if (solved[hash]) {

////            solved[hash]->add(i,answer);

////        } else {

////            solved[hash] = new node(i,answer);

////        }


////        Judge::replyCitizenName(my_names[answer]);


////    }


//    Judge::getPopulation();


////    auto ii = {1,4,16};

////    auto jj = {1,4};

////    auto kk = {0,2,4,8};

////    auto ll = {0,8};


//    auto ii = {1};

//    auto jj = {1};

//    auto kk = {8};

////    auto ll = {0};



//    for (auto i : ii) {

//        for (auto j : jj) {

//            for (auto k : kk) {

////                for (auto l : ll) {

//                    re_init(i,j,k);


//                    clock_t begin = clock();


//                    solution1();


//                    clock_t end = clock();


//                    auto diff0 = double(end - begin) / CLOCKS_PER_SEC ;


//                    re_init(i,j,k);


//                    begin = clock();


////                    solution2();


//                    end = clock();


//                    auto diff1 = double(end - begin) / CLOCKS_PER_SEC ;


//                    std::cout << i << " " << j << " " << k << " " << " " << std::fixed << diff0 << " " << std::fixed << diff1 << std::endl;


////                    std::cout << i << " " << j << " " << k << " " << l << " " << std::fixed << diff0 << " " << std::fixed << diff1 << std::endl;


//            }

//        }


//    }


//    return 0;

//}



//void solution1() {

//    // initialize typo helpers

//    init();


//    // make a copy of names to avoid copy on Judge::getCitizenName

//    for (int i = 0; i < Judge::getPopulation(); ++i) {

//        Judge::getCitizenName(i,my_names[i]);

//    }


//    sortNames(0,Judge::getPopulation()-1);


//    for (int i = 0; i < Judge::getQueryCount(); ++i) {


//        // get current querry

//        Judge::getCitizenLogin(my_logins[i]);


//        // lowercase login

//        toLower(my_logins[i]);


//        auto hash = getHash16(my_logins[i]);


//        // check if any solution for given hash exists

//        if (solved[hash]) {

//            // check if solution for given login exists

//            int answer = solved[hash]->get(my_logins[i]);

//            if (answer >= 0) {

//                Judge::replyCitizenName(my_names[answer]);

//                continue;

//            }

//        }


//        // login not solved before

//        resCnt = 0;

//        int answer = 0;

//        for (int j = 0; j < Judge::getPopulation(); ++j) {


//            // name matched, store index

//            if (tryToMatch(my_logins[i],my_names[j])) {

//                answer = j;

//                break;

////                resIdx[resCnt++] = j;

//            }

//        }


////        int answer = findFirstName(/*resCnt,resIdx,my_names*/);


//        if (solved[hash]) {

//            solved[hash]->add(i,answer);

//        } else {

//            solved[hash] = new CacheNode(i,answer);

//        }


//        Judge::replyCitizenName(my_names[answer]);


//    }

//}


//void solution0() {

//    for (int i = 0; i < Judge::getPopulation(); ++i) {

//        Judge::getCitizenName(i,my_names[i]);

//    }


//    char login[8];

//    for (int i = 0; i < Judge::getQueryCount(); ++i) {


//        // get current querry

//        Judge::getCitizenLogin(login);


//        // no matches for current login

//        resCnt = 0;


//        // lowercase login

//        toLower(login);


//        // find possible names

//        for (int j = 0; j < Judge::getPopulation(); ++j) {


//            // name matched, store index

//            if (tryToMatch(login,my_names[j])) {

//                resIdx[resCnt++] = j;

//            }

//        }


//        // in case of multiple matches find alphabetically first

//        int answer = findFirstName(/*resCnt,resIdx,my_names*/);


//        Judge::replyCitizenName(my_names[answer]);

//    }

//}


//void sortSubnamesBySubname(int start, int end) {

//    if (start == end)

//        return;


//    int begin = start;

//    int len = end - start + 1;

//    int mid1 = (end + start)/2;

//    int mid2 = mid1 + 1;


//    sortSubnamesBySubname(start,mid1);

//    sortSubnamesBySubname(mid2,end);


//    int current = 0;


//    while(begin <= mid1 && mid2 <= end) {

//        if (isLoginLesser(my_names[sub_names[begin].name_idx] + sub_names[begin].offset, my_names[sub_names[mid2].name_idx] + sub_names[mid2].offset)) {

//            sub_names_buffer[current++] = sub_names[begin++];

//        } else {

//            sub_names_buffer[current++] = sub_names[mid2++];

//        }

//    }


//    while (begin <= mid1) {

//        sub_names_buffer[current++] = sub_names[begin++];

//    }


//    while(mid2 <= end) {

//        sub_names_buffer[current++] = sub_names[mid2++];

//    }


//    for (int i = 0; i < len; ++i) {

//        sub_names[start + i] = sub_names_buffer[i];

//    }

//}


//void sortSubnamesByName(int start, int end) {

//    if (start == end)

//        return;


//    int begin = start;

//    int len = end - start + 1;

//    int mid1 = (end + start)/2;

//    int mid2 = mid1 + 1;


//    sortSubnamesBySubname(start,mid1);

//    sortSubnamesBySubname(mid2,end);


//    int current = 0;


//    while(begin <= mid1 && mid2 <= end) {

//        if (isNameLesser(my_names[sub_names[begin].name_idx], my_names[sub_names[mid2].name_idx])) {

//            sub_names_buffer[current++] = sub_names[begin++];

//        } else {

//            sub_names_buffer[current++] = sub_names[mid2++];

//        }

//    }


//    while (begin <= mid1) {

//        sub_names_buffer[current++] = sub_names[begin++];

//    }


//    while(mid2 <= end) {

//        sub_names_buffer[current++] = sub_names[mid2++];

//    }


//    for (int i = 0; i < len; ++i) {

//        sub_names[start + i] = sub_names_buffer[i];

//    }

//}


//inline void shiftSubnames(int begin, int end) {

//    for (;begin < end;++begin) {

//        sub_names[begin] = sub_names[begin + 1];

//    }

//}


//inline int removeDuplicateSubnames(int count) {

//    for (int i = 0; i < count;) {

//        if (equalsLogin(my_names[sub_names[i].name_idx] + sub_names[i].offset,my_names[sub_names[i+1].name_idx] + sub_names[i+1].offset)) {

//            if (isNameLesser(my_names[sub_names[i].name_idx], my_names[sub_names[i+1].name_idx])) {

//                shiftSubnames(i,count);

//            } else {

//                shiftSubnames(i+1,count);

//            }

//            --count;

//        } else {

//            ++i;

//        }

//    }

//    return count;

//}


//void solution2() {

//    // initialize typo helpers

//    init();


//    clock_t begin = clock();


//    // make a copy of names to avoid copy on Judge::getCitizenName

//    for (int i = 0; i < Judge::getPopulation(); ++i) {

//        Judge::getCitizenName(i,my_names[i]);

//        for (int j = 0; j < 9; ++j) {

//            sub_names[i*9+j].name_idx = i;

//            sub_names[i*9+j].offset = j;

//        }

//    }


//    clock_t end = clock();


////    std::cout << double(end - begin) / CLOCKS_PER_SEC << " " ;


////    for (int i = 0; i < Judge::getPopulation()*9; ++i) {

////        for (int j =0; j < 16; j++) {

////            std::cout << my_names[sub_names[i].name_idx][j];

////        }


////        std::cout << " ";


////        for (int j =0; j < 8; j++) {

////            std::cout << my_names[sub_names[i].name_idx][sub_names[i].offset + j];

////        }


////        std::cout << std::endl;

////    }


//    begin = clock();


//    sortSubnamesBySubname(0,Judge::getPopulation()*9 -1);


//    end = clock();


////    std::cout << double(end - begin) / CLOCKS_PER_SEC << " " ;


////    std::cout << std::endl;

////    for (int i = 0; i < Judge::getPopulation()*9; ++i) {

////        for (int j =0; j < 16; j++) {

////            std::cout << my_names[sub_names[i].name_idx][j];

////        }


////        std::cout << " ";


////        for (int j =0; j < 8; j++) {

////            std::cout << my_names[sub_names[i].name_idx][sub_names[i].offset + j];

////        }


////        std::cout << std::endl;

////    }


//    begin = clock();


//    int newCount = removeDuplicateSubnames(Judge::getPopulation()*9);


////    std::cout << 1.0 * newCount / Judge::getPopulation() / 9 << std::endl;


//    end = clock();


////    std::cout << double(end - begin) / CLOCKS_PER_SEC << " " ;


////    std::cout << std::endl;

////    for (int i = 0; i < newCount; ++i) {

////        for (int j =0; j < 16; j++) {

////            std::cout << my_names[sub_names[i].name_idx][j];

////        }


////        std::cout << " ";


////        for (int j =0; j < 8; j++) {

////            std::cout << my_names[sub_names[i].name_idx][sub_names[i].offset + j];

////        }


////        std::cout << std::endl;

////    }


//    begin = clock();


//    sortSubnamesByName(0,newCount -1);


//    end = clock();


////    std::cout << double(end - begin) / CLOCKS_PER_SEC << " " ;


////    std::cout << std::endl;

////    for (int i = 0; i < newCount; ++i) {

////        for (int j =0; j < 16; j++) {

////            std::cout << my_names[sub_names[i].name_idx][j];

////        }


////        std::cout << " ";


////        for (int j =0; j < 8; j++) {

////            std::cout << my_names[sub_names[i].name_idx][sub_names[i].offset + j];

////        }


////        std::cout << std::endl;

////    }


////    begin = clock();

//    double diff =0;


//    for (int i = 0; i < Judge::getQueryCount(); ++i) {


//        // get current querry

//        Judge::getCitizenLogin(my_logins[i]);


//        // lowercase login

//        toLower(my_logins[i]);


//        auto hash = getHash16(my_logins[i]);


//        // check if any solution for given hash exists

//        if (solved[hash]) {

//            // check if solution for given login exists

//            int answer = solved[hash]->get(my_logins[i]);

//            if (answer >= 0) {

//                Judge::replyCitizenName(my_names[answer]);

//                continue;

//            }

//        }


//        // login not solved before

//        int answer;


//        //resCnt = 0;

//        begin = clock();

//        for (int j = 0; j < newCount; ++j) {

//            // name matched, store index

//            if (tryToMatch2(my_logins[i],my_names[sub_names[j].name_idx] + sub_names[j].offset)) {

//                answer = sub_names[j].name_idx;

//                break;

//                //resIdx[resCnt++] = j;

//            }

//        }


//        end = clock();


//        diff += double(end - begin) / CLOCKS_PER_SEC;


////        int answer = findFirstName(/*resCnt,resIdx,my_names*/);


//        if (solved[hash]) {

//            solved[hash]->add(i,answer);

//        } else {

//            solved[hash] = new CacheNode(i,answer);

//        }


//        Judge::replyCitizenName(my_names[answer]);

//    }


////    end = clock();


////    std::cout << diff << " "  << std::endl;

//}
