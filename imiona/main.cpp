#include "judge.h"

#include <ctime>
#include <iostream>

#include "globals.h"
#include "utils.h"

//static substHelper helpers[32768*9];
//static substHelper helpers_buffer[32768*9];

//void sortHelpers(int start, int end) {

//    if (start >= end)
//        return;

//    int len = end - start + 1;
//    int sstart = start;

//    int mid1 = (start + end)/2;
//    int mid2 = mid1 + 1;

//    sortHelpers(start,mid1);
//    sortHelpers(mid2,end);

//    int current = start;

//    for (int i = 0; i < len; ++i) {
//        if (start <= mid1 && mid2 <= end) {
//            if (isLoginLesser(helpers[start].substr,helpers[mid2].substr)) {
//                helpers_buffer[start++] = helpers[current];
//                //                cpyLogin(my_names[start++],my_names_buffer[current]);
//            } else {
//                helpers_buffer[mid2++] = helpers[current];
//                //                cpyName(my_names[mid2++],my_names_buffer[current]);
//            }
//        } else if (start <= mid1) {
//            helpers_buffer[start++] = helpers[current];
//            //            cpyName(my_names[start++],my_names_buffer[current]);
//        } else {
//            helpers_buffer[mid2++] = helpers[current];
//            //            cpyName(my_names[mid2++],my_names_buffer[current]);
//        }
//        ++current;
//    }

//    for (int i = 0; i < len; ++i) {
//        helpers[i + sstart] = helpers_buffer[i + sstart];
////        my_names_buffer[i + sstart], my_names[i + sstart]);
//    }
//}

struct SolvedListNode {

    SolvedListNode(int _l_idx,int _n_idx) : l_idx(_l_idx), n_idx(_n_idx) { }

    inline void add(int l_idx,int n_idx) {
        if (!next) {
            next = new SolvedListNode(l_idx,n_idx);
        } else {
            next->add(l_idx,n_idx);
        }
    }

    inline int get(const char *s) {
        if (equalsLogin(s,my_logins[l_idx])) {
            return n_idx;
        }

        if (!next)
            return -1;
        else
            return next->get(s);
    }

    SolvedListNode* next = nullptr;
    int l_idx;
    int n_idx;
    //int size = 1;
};

static SolvedListNode* solved[solved_cache_size];

struct SolvedSubstrListNode {

    SolvedSubstrListNode(const char* substr,int _n_idx, int depth = 1) : n_idx(_n_idx) {
        cpyLogin(substr,subString);
//        size = depth;
//        if (size > max_size) {
//            max_size = size;
//        }
//        if (size > 10)
//            std::cout << size << std::endl;
    }

    inline void addOrUpdate(const char* substr,int _n_idx) {

//        if (equalsLogin(substr,"zeyqmcwr")) {
//            int aaa = 1;
//        }

//        if (equalsLogin(substr,"epygneco")) {
//            int aaa = 1;
//        }

        if (equalsLogin(substr,subString)) {
            if (isNameLesser(my_names[_n_idx],my_names[n_idx])) {
                n_idx = _n_idx;
            }
            return;
        }

//        if (max_size < size) {
//            std::cout<< max_size << std::endl;
//        }

        if (!next) {
            next = new SolvedSubstrListNode(substr,_n_idx,size + 1);

        } else {
            next->addOrUpdate(substr,_n_idx);
        }
    }

    inline int get(const char *s) {
        if (equalsLogin(s,subString)) {
            return n_idx;
        }

        if (!next)
            return -1;
        else
            return next->get(s);
    }

    SolvedSubstrListNode* next = nullptr;
    char subString[8];
    int n_idx;
    int size = 1;
    static int max_size;
};

int SolvedSubstrListNode::max_size = 0;

static SolvedSubstrListNode* solved_substr[solved_substr_cache_size];

inline int findFirstName() {
    int first = resIdx[0];
    for (int i = 1; i < resCnt; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (my_names[first][j] > my_names[resIdx[i]][j]) {
                first = resIdx[i];
                break;
            }
        }
    }
    return first;
}


//void initHelpers(int size) {
//    int helpersCount = 0;
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < 9; ++j) {
//            cpyLogin(my_names[i] + j,helpers[i].substr);
//            helpers[i].fitst_name_idx = i;
//            ++helpersCount;
//        }
//    }

//}


extern void re_init(int l_div, int n_div, int l_rnd, int n_rnd );

void solution1();
void solution0();
void solution2();
void solution3();
void solution4();

int main()
{
    Judge::getPopulation();

    auto ii = {1,2,4,8,16,24,32,64};
//    auto ii = {16,32};
    auto jj = {1,2};
    auto kk = {0,1,2,3,4};
    auto ll = {16};

//    auto ii = {100};
//    auto jj = {1};
//    auto kk = {8};
//    auto ll = {16};

    for (auto i : ii) {
        for (auto j : jj) {
            for (auto k : kk) {
                for (auto l : ll) {
                    re_init(i,j,k,l);

                    clock_t begin = clock();

                    solution1();

                    clock_t end = clock();

                    auto diff0 = double(end - begin) / CLOCKS_PER_SEC ;

                    re_init(i,j,k,l);

                    begin = clock();

//                    solution2();

                    end = clock();

                    auto diff1 = double(end - begin) / CLOCKS_PER_SEC ;

                    re_init(i,j,k,l);

                    begin = clock();

//                    solution3();

                    end = clock();

                    auto diff2 = double(end - begin) / CLOCKS_PER_SEC ;

                    re_init(i,j,k,l);

                    begin = clock();

                    solution4();

                    end = clock();

                    auto diff3 = double(end - begin) / CLOCKS_PER_SEC ;

                    std::cout << i << " " << j << " " << k << " " << l << "\t\t" << std::fixed << diff0 << " "  << std::fixed << diff1 << " " << std::fixed << diff2 << " " << std::fixed << diff3 << std::endl;
                }
            }
        }

    }

    return 0;
}


void mergeSortSubstrTbl(int start, int end) {
    if (start == end) {
        return;
    }

    int mid1 = (start + end)/2;
    int mid2 = mid1 + 1;

    mergeSortSubstrTbl(start,mid1);
    mergeSortSubstrTbl(mid2,end);

    int merge_start = start;

    int current = 0;

    while (merge_start <= mid1 && mid2 <= end) {
        if (isLoginLesser(my_names[0] + my_names_substr_idx[merge_start], my_names[0] + my_names_substr_idx[mid2])) {
            my_names_substr_idx_buffer[current++] = my_names_substr_idx[merge_start++];
        } else {
            my_names_substr_idx_buffer[current++] = my_names_substr_idx[mid2++];
        }
    }

    for (;merge_start <= mid1; ++merge_start, ++current ) {
        my_names_substr_idx_buffer[current] = my_names_substr_idx[merge_start];
    }

    for (;mid2 <= end; ++mid2, ++current ) {
        my_names_substr_idx_buffer[current] = my_names_substr_idx[mid2];
    }

    for (int i = 0; i <= end - start; ++i) {
        my_names_substr_idx[start + i] = my_names_substr_idx_buffer[i];
    }
}

inline void shiftSubstrLeft(int pos, int size) {
    for (; pos < size; ++pos) {
        my_names_substr_idx[pos] = my_names_substr_idx[pos + 1];
    }
}

// non list solution
inline void removeDuplicatesFromSubstrTbl(int& size) {
    for (int i = 0; i < size;) {
        if (equalsLogin(my_names[0] + my_names_substr_idx[i], my_names[0] + my_names_substr_idx[i + 1])) {
            if (isNameLesser(my_names[my_names_substr_idx[i]/16],my_names[my_names_substr_idx[i+1]/16])) {
                shiftSubstrLeft(i + 1,size);
            } else {
                shiftSubstrLeft(i,size);
            }
            size--;
        } else {
            i++;
        }
    }
}

struct listNode {

    listNode(int idx = -1) : substrIdx(idx) {}

    listNode* next = nullptr;
    listNode* prev = nullptr;

    int substrIdx;
};


void solution3() {
    // initialize typo helpers
    init();

    clock_t begin = clock();

    for (int i = 0; i < Judge::getPopulation(); ++i) {
        Judge::getCitizenName(i,my_names[i]);

        for (int j = 0; j < 9; ++j) {

            my_names_substr_idx[i*9+j] = i*16+j;
        }
    }
    int substr_cnt = Judge::getPopulation()*9;

    clock_t end = clock();
    auto diff0 = double(end - begin) / CLOCKS_PER_SEC ;
    begin = clock();
    mergeSortSubstrTbl(0,substr_cnt-1);

    end = clock();
    auto diff1 = double(end - begin) / CLOCKS_PER_SEC ;
    begin = clock();
    removeDuplicatesFromSubstrTbl(substr_cnt);

    end = clock();
    auto diff2 = double(end - begin) / CLOCKS_PER_SEC ;
    begin = clock();
    int a = 0;

    for (int i = 0; i < Judge::getQueryCount(); ++i) {

        // get current querry
        Judge::getCitizenLogin(my_logins[i]);

        // lowercase login
        toLower(my_logins[i]);

//        char ccc[9];
//        ccc[8] = 0;
//        cpyLogin(my_logins[i],ccc);

        resCnt = 0;
        int substr_idx = 0;
        int j = 0;
        char variant[8];
        while (substr_idx < substr_cnt && j < 3*3*3*3*3*3*3*3) {
            if (getSubstVariantAsc(j,my_logins[i],variant)) {

//                char ccc2[9];
//                ccc2[8] = 0;
//                cpyLogin(my_names[0] + my_names_substr_idx[substr_idx],ccc2);

                if (equalsLogin(variant,my_names[0] + my_names_substr_idx[substr_idx])) {
                    resIdx[resCnt++] = my_names_substr_idx[substr_idx]/16;
                    substr_idx++;
                    continue;
                }

                if (isLoginLesser(variant,my_names[0] + my_names_substr_idx[substr_idx])) {
                    j++;
                } else {
                    substr_idx++;
                }
            } else {
                ++j;
            }
        }

        int answer = findFirstName();

//        if (solved[hash]) {
//            solved[hash]->add(i,answer);
//        } else {
//            solved[hash] = new SolvedListNode(i,answer);
//        }

        Judge::replyCitizenName(my_names[answer]);
    }

    end = clock();
    auto diff3 = double(end - begin) / CLOCKS_PER_SEC ;


    std::cout << diff0 << " " << diff1 << " " << diff2 << " " << diff3 << std::endl;
}


void solution2() {
    // initialize typo helpers
    init();

    clock_t begin = clock();

    // make a copy of names to avoid copy on Judge::getCitizenName
    for (int i = 0; i < Judge::getPopulation(); ++i) {
        Judge::getCitizenName(i,my_names[i]);
//        names_sorted_indexes[i]=i;
        for (int j = 0; j < 9; ++j) {

//            cpyLogin(my_names[i] + j,my_names_substr[i*9+j]);

            auto hash = getSolvedSubstrHash16(my_names[i] + j);
            if (solved_substr[hash]) {
                solved_substr[hash]->addOrUpdate(my_names[i] + j,i);
            } else {
                solved_substr[hash] = new SolvedSubstrListNode(my_names[i] + j,i);
            }
        }
    }

    clock_t end = clock();
    auto diff0 = double(end - begin) / CLOCKS_PER_SEC ;

    double diff1a=0, diff1b = 0, diff1c = 0;


    for (int i = 0; i < Judge::getQueryCount(); ++i) {

        // get current querry
        begin = clock();
        Judge::getCitizenLogin(my_logins[i]);

        if (equalsLogin("ZruWNvWt",my_logins[i])) {
            int zzz = 0;
        }

        // lowercase login
        toLower(my_logins[i]);



        auto hash = getSolvedHash16(my_logins[i]);

        if (solved[hash]) {
            // check if solution for given login exists
            int answer = solved[hash]->get(my_logins[i]);
            if (answer >= 0) {
                Judge::replyCitizenName(my_names[answer]);
                continue;
            }
        }

        end = clock();
        diff1a += double(end - begin) / CLOCKS_PER_SEC;



        resCnt = 0;
        for (int j = 0; j < 3*3*3*3*3*3*3*3; ++j) {
            char variant[8];
            if (getSubstVariant(j,my_logins[i],variant)) {

                auto hash2 = getSolvedSubstrHash16(variant);
                if (solved_substr[hash2]) {
//                    begin = clock();
                    auto index = solved_substr[hash2]->get(variant);
//                    end = clock();
                    diff1b += double(end - begin) / CLOCKS_PER_SEC;
                    if (index >= 0)
                        resIdx[resCnt++] = index;
                }

            }
        }


//        std::cout << double(end - begin) / CLOCKS_PER_SEC << " ";
        begin = clock();

        int answer = findFirstName();

        if (solved[hash]) {
            solved[hash]->add(i,answer);
        } else {
            solved[hash] = new SolvedListNode(i,answer);
        }

        Judge::replyCitizenName(my_names[answer]);
        end = clock();
        diff1c += double(end - begin) / CLOCKS_PER_SEC;
    }

//    end = clock();
//    auto diff1 = double(end - begin) / CLOCKS_PER_SEC ;

//    std::cout << diff0 << " " << diff1a << " " << diff1b << " " << diff1c << std::endl;
}


void solution1() {
    // initialize typo helpers
    init();

    // make a copy of names to avoid copy on Judge::getCitizenName
    for (int i = 0; i < Judge::getPopulation(); ++i) {
        Judge::getCitizenName(i,my_names[i]);
//        names_sorted_indexes[i]=i;
    }

//    sortNames(0, Judge::getPopulation() - 1);

    for (int i = 0; i < Judge::getQueryCount(); ++i) {

        // get current querry
        Judge::getCitizenLogin(my_logins[i]);

        // lowercase login
        toLower(my_logins[i]);

        auto hash = getSolvedHash16(my_logins[i]);

        // check if any solution for given hash exists
        if (solved[hash]) {
            // check if solution for given login exists
            int answer = solved[hash]->get(my_logins[i]);
            if (answer >= 0) {
                Judge::replyCitizenName(my_names[answer]);
                continue;
            }
        }

        // login not solved before
        resCnt = 0;
        for (int j = 0; j < Judge::getPopulation(); ++j) {

            // name matched, store index
            if (tryToMatch(my_logins[i],my_names[j])) {
                resIdx[resCnt++] = j;
            }
        }

        int answer = findFirstName(/*resCnt,resIdx,my_names*/);

        if (solved[hash]) {
            solved[hash]->add(i,answer);
        } else {
            solved[hash] = new SolvedListNode(i,answer);
        }

        Judge::replyCitizenName(my_names[answer]);

    }
}

inline void cpyName(const char* src, char* dest) {
    auto srcI = reinterpret_cast<const int*>(src);
    auto destI = reinterpret_cast<int*>(dest);
    for (int i = 0; i < 4; ++i) {
        *(destI + i) = *(srcI + i);
    }
}

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

static const unsigned cache_size = 256*256;
static const unsigned cache_mask = cache_size - 1;

static char my_names_buffer[32768][16];

inline unsigned int getHash16(const char *login) {
    unsigned int h = 0;
    for (int i = 0; i < 8; ++i, ++login)
        h = h*23131 + (unsigned char)*login;
    return (h & cache_mask);
}

void sortNames(int start, int end) {
    if (start == end)
        return;

    int begin = start;
    int len = end - start + 1;
    int mid1 = (end + start)/2;
    int mid2 = mid1 + 1;

    sortNames(start,mid1);
    sortNames(mid2,end);

    int current = 0;

    while(begin <= mid1 && mid2 <= end) {
        if (isNameLesser(my_names[begin], my_names[mid2])) {
            cpyName(my_names[begin++],my_names_buffer[current++]);
        } else {
            cpyName(my_names[mid2++],my_names_buffer[current++]);
        }
    }

    while (begin <= mid1) {
        cpyName(my_names[begin++],my_names_buffer[current++]);
    }

    while(mid2 <= end) {
        cpyName(my_names[mid2++],my_names_buffer[current++]);
    }

    for (int i = 0; i < len; ++i) {
        cpyName(my_names_buffer[i],my_names[start + i]);
    }
}

inline bool equals(const char* s1, const char* s2) {
    const long long* i1 = reinterpret_cast<const long long*>(s1);
    const long long* i2 = reinterpret_cast<const long long*>(s2);

    return *i1 == *i2;
}

struct node {

    node(int _l_idx,int _n_idx) : l_idx(_l_idx), n_idx(_n_idx) { }

    inline void add(int l_idx,int n_idx) {
        if (!next) {
            next = new node(l_idx,n_idx);
        } else {
            next->add(l_idx,n_idx);
        }
    }

    inline int get(const char *s) {
        if (equals(s,my_logins[l_idx])) {
            return n_idx;
        }

        if (!next)
            return -1;
        else
            return next->get(s);
    }

    node* next = nullptr;
    int l_idx;
    int n_idx;
};

static node* solved2[cache_size];

void solution0() {
    // initialize typo helpers
    init();

    // make a copy of names to avoid copy on Judge::getCitizenName
    for (int i = 0; i < Judge::getPopulation(); ++i) {
        Judge::getCitizenName(i,my_names[i]);
    }

    sortNames(0,Judge::getPopulation()-1);

    for (int i = 0; i < Judge::getQueryCount(); ++i) {

        // get current querry
        Judge::getCitizenLogin(my_logins[i]);

        // lowercase login
        toLower(my_logins[i]);

//        auto hash = getHash16(my_logins[i]);

        // check if any solution for given hash exists
//        if (solved2[hash]) {
//            // check if solution for given login exists
//            int answer = solved2[hash]->get(my_logins[i]);
//            if (answer >= 0) {
//                Judge::replyCitizenName(my_names[answer]);
//                continue;
//            }
//        }

        // login not solved before
        int answer = 0;
        for (int j = 0; j < Judge::getPopulation(); ++j) {

            // name matched, store index
            if (tryToMatch(my_logins[i],my_names[j])) {
                answer = j;
                break;
            }
        }

//        if (solved2[hash]) {
//            solved2[hash]->add(i,answer);
//        } else {
//            solved2[hash] = new node(i,answer);
//        }

        Judge::replyCitizenName(my_names[answer]);

    }
    return;
}


struct CacheNode {
    CacheNode(int _l_idx,int _n_idx) : l_idx(_l_idx), n_idx(_n_idx) { }

    inline void add(int l_idx,int n_idx) {
        if (!next) {
            next = new CacheNode(l_idx,n_idx);
        } else {
            next->add(l_idx,n_idx);
        }
    }

    inline int get(const char *s) {
        if (equalsLogin(s,my_logins[l_idx])) {
            return n_idx;
        }

        if (!next)
            return -1;
        else
            return next->get(s);
    }

    CacheNode* next = nullptr;
    int l_idx;
    int n_idx;
    //int size = 1;
};

struct sub_name_info {
    //char str[8];
    int name_idx;
    int offset;
};

static sub_name_info sub_names[32768 * 9];
static sub_name_info sub_names_buffer[32768 * 9];

void sortSubnamesBySubname(int start, int end) {
    if (start == end)
        return;

    int begin = start;
    int len = end - start + 1;
    int mid1 = (end + start)/2;
    int mid2 = mid1 + 1;

    sortSubnamesBySubname(start,mid1);
    sortSubnamesBySubname(mid2,end);

    int current = 0;

    while(begin <= mid1 && mid2 <= end) {
        if (isLoginLesser(my_names[sub_names[begin].name_idx] + sub_names[begin].offset, my_names[sub_names[mid2].name_idx] + sub_names[mid2].offset)) {
            sub_names_buffer[current++] = sub_names[begin++];
        } else {
            sub_names_buffer[current++] = sub_names[mid2++];
        }
    }

    while (begin <= mid1) {
        sub_names_buffer[current++] = sub_names[begin++];
    }

    while(mid2 <= end) {
        sub_names_buffer[current++] = sub_names[mid2++];
    }

    for (int i = 0; i < len; ++i) {
        sub_names[start + i] = sub_names_buffer[i];
    }
}

void sortSubnamesByName(int start, int end) {
    if (start == end)
        return;

    int begin = start;
    int len = end - start + 1;
    int mid1 = (end + start)/2;
    int mid2 = mid1 + 1;

    sortSubnamesBySubname(start,mid1);
    sortSubnamesBySubname(mid2,end);
    int current = 0;

    while(begin <= mid1 && mid2 <= end) {
        if (isNameLesser(my_names[sub_names[begin].name_idx], my_names[sub_names[mid2].name_idx])) {
            sub_names_buffer[current++] = sub_names[begin++];
        } else {
            sub_names_buffer[current++] = sub_names[mid2++];
        }
    }


    while (begin <= mid1) {
        sub_names_buffer[current++] = sub_names[begin++];
    }

    while(mid2 <= end) {
        sub_names_buffer[current++] = sub_names[mid2++];
    }


    for (int i = 0; i < len; ++i) {
        sub_names[start + i] = sub_names_buffer[i];
    }
}

inline void shiftSubnames(int begin, int end) {
    for (;begin < end;++begin) {
        sub_names[begin] = sub_names[begin + 1];
    }
}

inline int removeDuplicateSubnames(int count) {
    for (int i = 0; i < count;) {
        if (equalsLogin(my_names[sub_names[i].name_idx] + sub_names[i].offset,my_names[sub_names[i+1].name_idx] + sub_names[i+1].offset)) {
            if (isNameLesser(my_names[sub_names[i].name_idx], my_names[sub_names[i+1].name_idx])) {
                shiftSubnames(i,count);
            } else {
                shiftSubnames(i+1,count);
            }
            --count;
        } else {
            ++i;
        }
    }
    return count;
}

inline bool tryToMatch2(const char* login, const char* name) {
        bool matched = true;
        for (int i = 0; i < 8; ++i) {
            if (login[i] != name[i] && nextCh[login[i] - 'a'] != name[i] && prevCh[login[i] - 'a'] != name[i]) {
                matched = false;
                break;
            }
        }
        return matched;
}

static CacheNode* solved3[cache_size];

inline bool findInSubnames(const char* str,int begin, int end, sub_name_info& dest) {

//    if (equalsLogin(my_names[sub_names[begin].name_idx] + sub_names[begin].offset, str)) {
//        dest = sub_names[begin];
//        return true;
//    }

//    if (equalsLogin(my_names[sub_names[end].name_idx] + sub_names[end].offset, str)) {
//        dest = sub_names[end];
//        return true;
//    }

    int mid = (begin + end)/2;

    if (equalsLogin(my_names[sub_names[mid].name_idx] + sub_names[mid].offset, str)) {
        dest = sub_names[mid];
        return true;
    }

//    if (end - begin < 2) {
//        return false;
//    }

    if (isLoginLesser(str,my_names[sub_names[mid].name_idx] + sub_names[mid].offset)) {
        return mid!=begin && findInSubnames(str,begin,mid-1,dest);
    } else {
        return mid!=end && findInSubnames(str,mid+1,end,dest);
    }
}

void solution4() {
    // initialize typo helpers
    init();

//    clock_t begin = clock();

    // make a copy of names to avoid copy on Judge::getCitizenName
    for (int i = 0; i < Judge::getPopulation(); ++i) {
        Judge::getCitizenName(i,my_names[i]);
        for (int j = 0; j < 9; ++j) {
            sub_names[i*9+j].name_idx = i;
            sub_names[i*9+j].offset = j;
        }
    }

//    clock_t end = clock();

//    std::cout << double(end - begin) / CLOCKS_PER_SEC << " "  << std::endl;

//    begin = clock();

    sortSubnamesBySubname(0,Judge::getPopulation()*9 -1);

//    end = clock();

//    std::cout << double(end - begin) / CLOCKS_PER_SEC << " "  << std::endl;

//    begin = clock();

    int newCount = removeDuplicateSubnames(Judge::getPopulation()*9);
//    std::cout << newCount * 1.0 / Judge::getPopulation() /9 << " ";
//    std::cout << newCount << " ";
//    std::cout << Judge::getPopulation() * 9 << std::endl;

//    end = clock();

//    std::cout << double(end - begin) / CLOCKS_PER_SEC << " "  << std::endl;

//    auto begin2 = clock();

    double diff = 0;

    for (int i = 0; i < Judge::getQueryCount(); ++i) {

        // get current querry
        Judge::getCitizenLogin(my_logins[i]);

        // lowercase login
        toLower(my_logins[i]);

        auto hash = getHash16(my_logins[i]);

        // check if any solution for given hash exists
        if (solved3[hash]) {
            // check if solution for given login exists
            int answer = solved3[hash]->get(my_logins[i]);
            if (answer >= 0) {
                Judge::replyCitizenName(my_names[answer]);
                continue;
            }
        }

        // login not solved before


        resCnt = 0;

        char variant[8];
        sub_name_info info;
        for (int k = 0; k < 3*3*3*3*3*3*3*3;++k) {
            if (getSubstVariant(k,my_logins[i],variant)) {
//                begin = clock();
                if (findInSubnames(variant,0,newCount-1,info)) {
                    resIdx[resCnt++] = info.name_idx;
                }
//                end = clock();
//                diff += double(end - begin) / CLOCKS_PER_SEC;
            }
        }

        int answer = findFirstName();

        if (solved3[hash]) {
            solved3[hash]->add(i,answer);
        } else {
            solved3[hash] = new CacheNode(i,answer);
        }
        Judge::replyCitizenName(my_names[answer]);
    }

//    auto end2 = clock();

//    std::cout << diff << " ++++"  << std::endl;

//    std::cout << double(end2 - begin2) / CLOCKS_PER_SEC << " ---"  << std::endl;
}

