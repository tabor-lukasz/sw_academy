#ifndef UTILS_H
#define UTILS_H

//#include "globals.h"

static char all[] = "qwertyuiopasdfghjklzxcvbnm";
static char nextCh[26];
static char prevCh[26];

static const unsigned solved_cache_size = 256*256;
static const unsigned solved_cache_mask = solved_cache_size - 1;

static const unsigned solved_substr_cache_size = 256*256;
static const unsigned solved_substr_cache_mask = solved_substr_cache_size - 1;

// initialize allowed typo errors
void init() {
    for (char c = 'a'; c <= 'z'; ++c) {
        int index = -1;
        for (int i = 0; i < 26; ++i) {
            if (all[i] == c) {
                index = i;
                break;
            }
        }
        if (index == 0 || index == 10 || index == 19) {
            prevCh[c-'a'] = 0;
        } else {
            prevCh[c-'a'] = all[index-1];
        }

        if (index == 9 || index == 18 || index == 25) {
            nextCh[c-'a'] = 0;
        } else {
            nextCh[c-'a'] = all[index+1];
        }
    }
}

inline bool getSubstVariant(int nr, const char* src, char* dest) {
    for (int i = 0; i < 8; ++i,nr/=3) {
        int remainder = nr %3;
        switch (remainder) {
        case 0: {
            dest[i] = src[i];
            break;
        }
        case 1: {
            dest[i] = prevCh[src[i] - 'a'];
            break;
        }
        case 2: {
            dest[i] = nextCh[src[i] - 'a'];
            break;
        }
        }
        if (dest[i] == 0)
            return false;
    }
    return true;
}

inline bool getSubstVariantAsc(int nr, const char* src, char* dest) {
    for (int i = 7; i >= 0; --i,nr/=3) {
        int remainder = nr %3;

        char c1 = src[i];
        char c2 = prevCh[c1-'a'];
        char c3 = nextCh[c1-'a'];

        if (c1 > c2) {
            char tmp = c1;
            c1 = c2;
            c2 = tmp;
        }

        if (c1 > c3) {
            char tmp = c1;
            c1 = c3;
            c3 = tmp;
        }

        if (c2 > c3) {
            char tmp = c2;
            c2 = c3;
            c3 = tmp;
        }

        switch (remainder) {
        case 0: {
            dest[i] = c1;
            break;
        }
        case 1: {
            dest[i] = c2;
            break;
        }
        case 2: {
            dest[i] = c3;
            break;
        }
        }
        if (dest[i] == 0)
            return false;
    }
    return true;
}

inline bool equalsLogin(const char* s1, const char* s2) {
    const long long i1 = *reinterpret_cast<const long long*>(s1);
    const long long i2 = *reinterpret_cast<const long long*>(s2);

    return i1 == i2;
}

inline bool equalsName(const char* s1, const char* s2) {
    const long long i11 = *reinterpret_cast<const long long*>(s1);
    const long long i21 = *reinterpret_cast<const long long*>(s2);
    const long long i12 = *reinterpret_cast<const long long*>(s1+8);
    const long long i22 = *reinterpret_cast<const long long*>(s2+8);

    return i11 == i21 && i12 == i22;
}

inline bool isLoginLesser(const char* s1, const char* s2) {
    for (int i = 0; i < 8; ++i) {
        if (s1[i] > s2[i])
            return false;
        else if (s1[i] < s2[i])
            return true;
    }
    return false;
}

inline bool isNameLesser(const char* s1, const char* s2) {
    for (int i = 0; i < 16; ++i) {
        if (s1[i] > s2[i])
            return false;
        else if (s1[i] < s2[i])
            return true;
    }
    return false;
}

inline void cpyLogin(const char* src, char* dest) {
    for (int i = 0; i < 8; ++i) {
        dest[i] = src[i];
    }
}

inline void toLower(char* login) {
    for (int i = 0; i < 8; ++i) {
        if (login[i] < 'a') {
            login[i] = login[i] - 'A' + 'a';
        }
    }
}

inline bool tryToMatch(const char* login, const char* name) {
    for (int j = 0; j < 9; ++j) {
        bool matched = true;
        for (int i = 0; i < 8; ++i) {
            if (login[i] != name[i + j] && nextCh[login[i] - 'a'] != name[i + j] && prevCh[login[i] - 'a'] != name[i + j]) {
                matched = false;
                break;
            }
        }
        if (matched)
            return true;
    }
    return false;
}

inline unsigned int getSolvedHash16(const char *login) {
    unsigned int h = 0;
    for (int i = 0; i < 8; ++i, ++login)
        h = h*23131 + (unsigned char)*login;
    return (h & solved_cache_mask);
}

inline unsigned int getSolvedSubstrHash16(const char *login) {
    unsigned int h = 0;
    for (int i = 0; i < 8; ++i, ++login)
        h = h*23131 + (unsigned char)*login;
    return (h & solved_substr_cache_mask);
}

#endif // UTILS_H
