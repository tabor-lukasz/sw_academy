//#include "judge.h"

//static char all[] = "qwertyuiopasdfghjklzxcvbnm";
//static char nextCh[26];
//static char prevCh[26];

//static char my_names[32768][16];
//static char my_names_buffer[32768][16];
//static char my_logins[65536][8];

//inline bool equals(const char* s1, const char* s2) {
//    const long long* i1 = reinterpret_cast<const long long*>(s1);
//    const long long* i2 = reinterpret_cast<const long long*>(s2);

//    return *i1 == *i2;
//}

//struct node {

//    node(int _l_idx,int _n_idx) : l_idx(_l_idx), n_idx(_n_idx) { }

//    inline void add(int l_idx,int n_idx) {
//        if (!next) {
//            next = new node(l_idx,n_idx);
//        } else {
//            next->add(l_idx,n_idx);
//        }
//    }

//    inline int get(const char *s) {
//        if (equals(s,my_logins[l_idx])) {
//            return n_idx;
//        }

//        if (!next)
//            return -1;
//        else
//            return next->get(s);
//    }

//    node* next = nullptr;
//    int l_idx;
//    int n_idx;
//};

//static const unsigned cache_size = 256*256;
//static const unsigned cache_mask = cache_size - 1;
//static node* solved[cache_size];

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
//        *(destI + i) = *(srcI + i);
//    }
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
//        cpyName(my_names_buffer[i],my_names[start + i]);
//    }
//}

//int main()
//{
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
//        int answer = 0;
//        for (int j = 0; j < Judge::getPopulation(); ++j) {

//            // name matched, store index
//            if (tryToMatch(my_logins[i],my_names[j])) {
//                answer = j;
//                break;
//            }
//        }

//        if (solved[hash]) {
//            solved[hash]->add(i,answer);
//        } else {
//            solved[hash] = new node(i,answer);
//        }

//        Judge::replyCitizenName(my_names[answer]);

//    }
//    return 0;
//}
