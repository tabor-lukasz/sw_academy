#include "judge.h"

//#define DBG

#ifdef DBG

using namespace std;

//#include <map>
#include <iostream>
#include <iomanip>

#endif

long long compute_hash(const char* str) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (;*str && *str != '>';++str) {
        hash_value = (hash_value + (*str - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

bool strEq(const char* s1, const char* s2) {
    while (*s1 && *s2 && *s2 != '>' && *s1 != '>') {
        if (*s1 != *s2) {
            return false;
        }
        ++s1;
        ++s2;
    }

    if (*s1 == *s2 || (*s2 == '>' && *s1 == 0) || (*s1 == '>' && *s2 == 0)) {
        return true;
    }

    return false;
}

void strcpy(const char* src, char* dest, int len) {
    for (int i = 0; i < len;++i) {
        dest[i] = src[i];
    }
    dest[len] = 0;
}

struct user {
    user(const char* _name = 0, int len = 0, user* p = nullptr) : parent(p) {
        if (parent)
            parent->addChild(this);

        for (int i = 0; i < 20; ++i) {
            children[i] = nullptr;
        }
        int i = 0;
        for (i = 0; i < len; ++i) {
            name[i] = _name[i];
        }
        name[i] = 0;
    }

    ~user() {
        for (int i = 0; i < 20; ++i) {
            delete children[i];
        }
    }

    void modFamilyCt(int cnt) {
        familyCnt +=cnt;
        if (parent)
            parent->modFamilyCt(cnt);
    }

    int getFamilyCnt() const {
        return familyCnt;
    }

    char name[9];


    void addChild(user* child) {
        child->parent = this;
        auto idx = compute_hash(child->name) % 20;

        while (children[idx]) {
            ++idx;
            if (idx > 19)
                idx = 0;
        }

        children[idx] = child;
        modFamilyCt(child->familyCnt);
        ++childCnt;
    }

    void removeChild(const user* child) {
        auto idx = compute_hash(child->name) % 20;

        while (true) {
            if (children[idx] && strEq(child->name,children[idx]->name)) {
                modFamilyCt(-child->familyCnt);
                children[idx] = nullptr;
                --childCnt;
                return;
            } else {
                ++idx;
                if (idx > 19)
                    idx = 0;
            }
        }
    }

    user* getChild(const char* childName) {

        if (childCnt == 0) {
            return nullptr;
        }

        auto idx = compute_hash(childName) % 20;
        const int idx_cpy = idx;

        while (true) {
            if (children[idx] && strEq(childName,children[idx]->name)) {
                return children[idx];
            } else {
                ++idx;
                if (idx > 19)
                    idx = 0;

                if (idx == idx_cpy){
                    return nullptr;
                }
            }
        }
    }

    user* children[20];
    user* parent = nullptr;

private:
    int familyCnt = 1;
    int childCnt = 0;

};

user usersRoot;
char* g_info;
char* g_newInfo;
user* lastTraversed = nullptr;

#ifdef DBG
void printUser(const user* u) {
    static int intend = -1;
    intend++;
    static bool newLine = true;
    if (newLine) {
        cout << endl;
        for (int i = 0; i < intend; ++i) {
            cout << string("            ");
        }
        newLine = false;
    }
    cout << string(u->name,8) << " " << setw(2) << u->getFamilyCnt() << " ";
    for (int i = 0; i < 20; ++i) {
        if (u->children[i]) {
            printUser(u->children[i]);
        }
    }
    newLine = true;
    intend--;
}


void printAll(const string& header) {
    if (!header.empty())
        cout << header << endl;

    for (int i = 0; i < 20; ++i) {
        if (usersRoot.children[i]) {
            printUser(usersRoot.children[i]);
        }
    }
    cout << endl;
}

#endif

int getNextLen(int begin) {
    auto pos = g_info + begin;
    int cnt = 0;
    while (*pos != '>' && *pos != 0) {
        ++cnt;
        ++pos;
    }
    return cnt;
}


class DRZ : public IDRZ {
public:
    int addCitizenInfo(char info[MAX_INFO_LEN]) {

        g_info = info;

        auto len = getNextLen(0);
        if (len == 0) {
            return 0;
        }

        auto res = addToTree(0,&usersRoot);
#ifdef DBG
        printAll("\n\naddCitizenInfo " + string(info));
#endif
        return res;
    }

    int delCitizenInfo(char info[MAX_INFO_LEN]) {
        g_info = info;

        auto user = findUser(&usersRoot,0);

        user->parent->removeChild(user);
        auto cnt = user->getFamilyCnt();

        delete user;
#ifdef DBG
        printAll("\n\ndelCitizenInfo " + string(info));
#endif
        return cnt;
    }

    void modifyCitizen(char info[MAX_INFO_LEN], char newInfo[MAX_INFO_LEN]) {
        g_info = info;
        g_newInfo = newInfo;

#ifdef DBG
        printAll("\n\nmodifyCitizen " + string(info) + " -> " + string(newInfo));
#endif

        auto user = findUser(&usersRoot,0);

        user->parent->removeChild(user);

        g_info = g_newInfo;

        int lastSeparator = 0;
        int idx = 0;
        while (g_info[idx]) {
            if (g_info[idx] == '>') {
                lastSeparator = idx;
            }
            ++idx;
        }

        if (lastSeparator > 0) {
            idx = lastSeparator +1;
        } else {
            idx = 0;
        }
        {
            int i = 0;
            while (g_info[idx]) {
                user->name[i] = g_info[idx];
                ++idx;
                ++i;
            }
            user->name[i] = 0;
        }

        g_info[lastSeparator] = 0;

        addToTree(0,&usersRoot);

        lastTraversed->addChild(user);
        user->parent = lastTraversed;
#ifdef DBG
        printAll("-->");
        (void)g_info;
#endif
    }

    int familyMemberCount(char info[MAX_INFO_LEN]) {

        g_info = info;

        auto user = findUser(&usersRoot,0);
        if (user != &usersRoot) {
            return user->getFamilyCnt();
        } else {
            return 0;
        }
    }

    int addToTree(int begin, user* dest) {

        lastTraversed = dest;
        auto len = getNextLen(begin);

        if (len == 0) {
            return 0;
        }

        auto usr = dest->getChild(g_info+begin);

        if (usr) {
            lastTraversed = usr;
            if (*(g_info + begin + len) == 0)
                return 0;
            auto added = addToTree(begin + len + 1, usr);
            return added;
        } else {
            user* u = new user(g_info+begin,len,dest);

            lastTraversed = u;

            int added = 1;
            if (*(g_info + begin + len)) {
                added += addToTree(begin + len + 1, u);
            }
            return added;
        }
    }

    user* findUser(user* parent,int begin) {
        auto len = getNextLen(begin);

        if (!len) {
            return parent;
        }

        auto usr = parent->getChild(g_info+begin);

        if (!usr) {
            return parent;
        }

        if (*(g_info + begin + len)) {
            return  findUser(usr,begin + len + 1);
        } else {
            return usr;
        }
    }
};

DRZ solution;
int main() {
    Judge::run(&solution);
    return 0;
}

