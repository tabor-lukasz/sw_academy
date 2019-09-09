#include "judge.h"

#include <iostream>
using namespace std;

const int MAX_SHOPS = 5;
const int MAX_ID = 20000000;
const int SWT_LEVELS = 5;
const int MAX_PARTICIPANTS = 100000;

int heaps[MAX_SHOPS][MAX_PARTICIPANTS];

int shops_ctn =0;
int shops_capacity =0;

//template<class T> struct ListNode {
//    ListNode<T>* next = nullptr;
//    ListNode<T>* prev = nullptr;
//    T* data;
//};

struct User {
    User() = default;
    User(int id, const char * level, int prefs[]) {
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
            this->prefs[i] = prefs[i];
        }
    }
    User* next;
    User* prev;
    int rank;
    char prefs[MAX_SHOPS];
    int current;
};

User* usersRegister[MAX_ID+1];
User* firstUser;

struct workshop {
    User* first = nullptr;
    User* last = nullptr;
    int cnt = 0;
    char id;

    User* updateAfterAdd(User* user) {
        cnt++;
        if(!first || user->rank > first->rank) {
            first = user;
        }

        if(!last || user->rank < last->rank) {
            last = user;
        }
        if (cnt > shops_capacity) {
            auto current = last;
            auto tmp = last;
            while (current->prev->current != id) {
                current = current->prev;
            }
            last = current->prev;
            cnt--;
            tmp->current = -1;
            return tmp;
        }
        return nullptr;
    }

    void prepareBeforeRemove(User* user) {
        if (user == first) {
            auto current = first;
            while (current->next && current->next->current != id) {
                current = current->next;
            }
            first = current->next;
        }

        if (user == last) {
            auto current = last;
            while (current->prev && current->prev->current != id) {
                current = current->prev;
            }
            last = current->prev;
        }
        cnt--;
    }
};

workshop shops[MAX_SHOPS];

class WAR : public iWAR {
public:
    virtual void init(int workshopsNum, int maxParticipants);
    virtual int registration(int byteid, char level[], int preferences[]);
    virtual int unregistration(int byteid);
private:
};

int main() {
    WAR w;
    judge::run(&w);
}


void WAR::init(int workshopsNum, int maxParticipants){

    for (int i = 0; i < MAX_PARTICIPANTS; ++i) {
        if (usersRegister[i]) {
            delete usersRegister[i];
            usersRegister[i] = nullptr;
        }
    }
    firstUser = nullptr;
    shops_ctn = workshopsNum;
    shops_capacity = maxParticipants;

    for (int i = 0; i < shops_ctn; ++i) {
        shops[i].cnt = 0;
        shops[i].last = nullptr;
        shops[i].first = nullptr;
        shops[i].id = static_cast<char>(i);
    }
}

void printUser(User* user) {
    if (!user) {
        return;
    }
    cout << 20000000 - (user->rank % MAX_ID) << "\t" <<  user->rank << "\t" << (int)user->current << "\t";
    for (int j = 0 ; j < shops_ctn; j++) {
        cout << (int)user->prefs[j] << " ";
    }
    cout << endl;
}

void printUsers() {
    auto curr = firstUser;
    while(curr) {
        printUser(curr);
        curr = curr->next;
    }
}

void printShops() {
    for (int i = 0; i < shops_ctn; i++) {
        cout << "Shop: " << (int)shops[i].id << " cnt: " << shops[i].cnt << endl;
        auto current = shops[i].first;
        while (current) {
            if (current->current == shops[i].id)
                printUser(current);
            if (current == shops[i].last) {
                break;
            }
            current = current->next;
        }
    }
    cout << endl;
}

void addToList(User* user) {
    if (!firstUser) {
        firstUser = user;
        return;
    }

    if (firstUser->rank < user->rank) {
        user->next = firstUser;
        firstUser->prev = user;
        firstUser = user;
        return;
    }

    auto current = firstUser;
    while (current->next && current->next->rank > user->rank) {
        current = current->next;
    }

    while (current->next && current->next->rank > user->rank) {
        current = current->next;
    }
    if (!current->next) {
        current->next = user;
        user->prev = current;
    } else {
        current->next = user;
        current->next->prev = user;
        user->next = current->next;
        user->prev = current;
    }
}

void removeFromList(User* user) {
    if (user->next) {
        user->next->prev = user->prev;
    }

    if (user->prev) {
        user->prev->next = user->next;
    }

    if (user == firstUser) {
        firstUser = firstUser->next;
        if (firstUser)
            firstUser->prev = nullptr;
     }
}


int WAR::registration(int byteid, char level[], int preferences[]) {
    auto user = new User(byteid,level,preferences);
    usersRegister[byteid] = user;
//    if (byteid == 23) {
//        printShops();
//    }

    addToList(user);

//    if (byteid == 23) {
//        printShops();
//    }


//    cout << "Adding:";
//    printUser(user);

//    if (byteid == 23) {
//        int rrr =0;
//        printUsers();
//    }

    User* user2 = nullptr;
    for (auto pref : user->prefs) {
        auto& workshop = shops[pref];
        if (workshop.cnt < shops_capacity || user->rank > workshop.last->rank) {
            user->current = pref;
            user2 = workshop.updateAfterAdd(user);
            break;
        }
    }

    while(user2) {
        for (auto pref : user2->prefs) {
            auto& workshop = shops[pref];
            if (workshop.cnt < shops_capacity || user2->rank > workshop.last->rank) {
                user2->current = pref;
                user2 = workshop.updateAfterAdd(user2);
                break;
            }
        }
    }

//    printShops();
    return user->current;
}

User* lookForCandidate(User* user, int shop_id) {
    if (!user)
        return nullptr;

    while (user->next) {
        user = user->next;
        for (auto pref : user->prefs) {
            if (pref == user->current)
                break;

            if (pref == shop_id)
                return user;
        }
    }
    return nullptr;
}

int WAR::unregistration(int byteid) {
    auto user = usersRegister[byteid];

//    cout << "Removing: ";
//    printUser(user);

    auto shop_id = user->current;

    auto new_space = user->current;
    shops[new_space].prepareBeforeRemove(user);

    auto candidate = lookForCandidate(shops[new_space].last,new_space);
    while (candidate) {
        auto candidate_shop = candidate->current;
        shops[candidate_shop].prepareBeforeRemove(candidate);
//        printShops();
        candidate->current = new_space;
        shops[new_space].updateAfterAdd(candidate);
//        printShops();
        new_space = candidate_shop;
        candidate = lookForCandidate(shops[new_space].last,new_space);
    }

    removeFromList(user);
    delete user;
    usersRegister[byteid] = nullptr;
//    printShops();
//    printUsers();

    return shop_id;
}


