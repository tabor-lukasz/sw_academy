//#include "judge.h"

//#include <iostream>

//using namespace std;

//static const int MAX_SHOPS = 5;
//static const int MAX_ID = 20000000;
//static const int SWT_LEVELS = 5;
//static const int MAX_PARTICIPANTS = 100000;

//static const int BUCKET_SIZE = 50;
//static const int BUCKET_COUNT = MAX_ID*SWT_LEVELS/BUCKET_SIZE;

//static int shops_ctn =0;
//static int shops_capacity =0;

//struct User {
//    User() = default;
//    User(int id, const char * level, int prefs[]) {
//        switch (level[0]) {
//        case 'e': {
//            rank = 4*MAX_ID + (MAX_ID-id);
//            break;
//        }
//        case 'p': {
//            rank = 3*MAX_ID + (MAX_ID-id);
//            break;
//        }
//        case 'a': {
//            rank = 2*MAX_ID + (MAX_ID-id);
//            break;
//        }
//        case 'i': {
//            rank = 1*MAX_ID + (MAX_ID-id);
//            break;
//        }
//        case 'n': {
//            rank = (MAX_ID-id);
//            break;
//        }
//        }
//        for (int i = 0; i < shops_ctn; ++i) {
//            this->prefs[i] = static_cast<char>(prefs[i]);
//        }
//    }
//    User* next = nullptr;
//    User* prev = nullptr;
//    int rank;
//    int current;
//    char prefs[MAX_SHOPS];
//};

//static User* usersRegister[MAX_ID+1];
//static User* firstUser;
//static User* lastUser;

//struct Bucket {
//    User* first = nullptr;
//    User* last = nullptr;
//    int id;

//    void add(User* user) {
//        if (!first) {
//            first = last = user;
//            user->next = user->prev = nullptr;
//            return;
//        }

//        if (first->rank < user->rank) {
//            user->next = first;
//            user->prev = first->prev;
//            if (first->prev) {
//                first->prev->next = user;
//            }
//            first->prev = user;
//            first = user;
//            return;
//        }

//        auto current = first;
//        while (current->next && current->next->rank > user->rank) {
//            current = current->next;
//        }

//        if (!current->next) {
//            current->next = user;
//            user->prev = current;
//        } else {
//            user->next = current->next;
//            user->prev = current;
//            current->next->prev = user;
//            current->next = user;
//        }

//        if (last->rank > user->rank) {
//            last = user;
//        }
//    }

//    void remove(User* user) {

//        if (user->prev) {
//            user->prev->next = user->next;

//        }

//        if (user->next) {
//            user->next->prev = user->prev;
//        }

//        if (user == first) {
//            if (user->next && BUCKET_COUNT - (user->next->rank / BUCKET_SIZE) - 1 == id) {
//                first = user->next;
//            } else {
//                first = nullptr;
//            }
//        }

//        if (user == last) {
//            if (user->prev && BUCKET_COUNT - (user->prev->rank / BUCKET_SIZE) - 1 == id) {
//                last = user->prev;
//            } else {
//                last = nullptr;
//            }
//        }
//    }
//};

//static Bucket buckets[BUCKET_COUNT];

//void addToBuckets(User* user) {
//    int bucket_id = BUCKET_COUNT - (user->rank / BUCKET_SIZE) - 1;
//    buckets[bucket_id].add(user);

//    if (!firstUser || firstUser->rank < user->rank) {
//        firstUser = user;
//    } else {
//        if (buckets[bucket_id].first->prev == nullptr) {
//            for (int i = bucket_id - 1; i >= 0; --i) {
//                if (buckets[i].last) {
//                    buckets[bucket_id].first->prev = buckets[i].last;
//                    buckets[i].last->next = buckets[bucket_id].first;
//                    break;
//                }
//            }
//        }
//    }

//    if (!lastUser || lastUser->rank > user->rank) {
//        lastUser = user;
//    } else {
//        if (buckets[bucket_id].last->next == nullptr) {
//            for (int i = bucket_id + 1; i < BUCKET_COUNT; ++i) {
//                if (buckets[i].first) {
//                    buckets[bucket_id].last->next = buckets[i].first;
//                    buckets[i].first->prev = buckets[bucket_id].last;
//                    break;
//                }
//            }
//        }
//    }
//}

//void removeFromBuckets(User* user) {
//    int bucket_id = BUCKET_COUNT - (user->rank / BUCKET_SIZE) - 1;
//    buckets[bucket_id].remove(user);

//    if (user == firstUser) {
//        firstUser = firstUser->next;
//    }
//    if (user == lastUser) {
//        lastUser = lastUser->prev;
//    }
//}

////void printUser(User* user) {
////        if (!user) {
////            return;
////        }
////        cout << 20000000 - (user->rank % MAX_ID) << "\t" <<  user->rank << "\t" << (int)user->current << "\t";
////        for (int j = 0 ; j < shops_ctn; j++) {
////            cout << (int)user->prefs[j] << " ";
////        }
////        cout << endl;
////}

////void printUsers() {
////        auto curr = firstUser;
////        while(curr) {
////            printUser(curr);
////            curr = curr->next;
////        }
////}

//struct workshop {
//    User* last = nullptr;
//    int cnt = 0;
//    char id;

//    User* updateAfterAdd(User* user) {
//        cnt++;
//        if(!last || user->rank < last->rank) {
//            last = user;
//        }
//        if (cnt > shops_capacity) {
//            auto current = last;
//            auto tmp = last;
//            while (current->prev->current != id) {
//                current = current->prev;
//            }
//            last = current->prev;
//            cnt--;
//            tmp->current = -1;
//            return tmp;
//        }
//        return nullptr;
//    }

//    void prepareBeforeRemove(User* user) {
//        if (user == last) {
//            auto current = last;
//            while (current->prev && current->prev->current != id) {
//                current = current->prev;
//            }
//            last = current->prev;
//        }
//        cnt--;
//    }
//};

//static workshop shops[MAX_SHOPS];

////void check() {
////    int sum = 0;
////    for (int i = 0; i < shops_ctn; ++i) {
////        sum += shops[i].cnt;
////    }

////    int counter = 0;
////    auto current = firstUser;
////    while (current) {
////        ++counter;
////        if (counter > sum + 1) {
////            int ccc = 0;
////            (void)ccc;
////            break;
////        }
////        current = current->next;
////    }
////}

////void printShops() {
////        for (int i = 0; i < shops_ctn; i++) {
////            cout << "Shop: " << (int)shops[i].id << " cnt: " << shops[i].cnt << endl;
////            auto current = firstUser;
////    //        auto current = shops[i].first;
////            while (current) {
////                if (current->current == shops[i].id)
////                    printUser(current);
////                if (current == shops[i].last) {
////                    break;
////                }
////                current = current->next;
////            }
////        }
////        cout << endl;
////}

////void printBuckets() {
////    for (int i = 0; i < BUCKET_COUNT; ++i) {
////        auto curr = buckets[i].first;

////        if (curr) {
////            cout << "Bucket: " << i << endl;
////        }

////        while (curr && (BUCKET_COUNT - (curr->rank / BUCKET_SIZE) - 1) == i) {
////            printUser(curr);
////            curr = curr->next;
////        }
////    }
////}


//class WAR : public iWAR {
//public:
//    virtual void init(int workshopsNum, int maxParticipants);
//    virtual int registration(int byteid, char level[], int preferences[]);
//    virtual int unregistration(int byteid);
//private:
//};

//extern void setTestCase(int);

//int main() {

////    cout << sizeof (User) << endl;
////    cout << sizeof(usersRegister)/1024.0/1024.0 << endl;
////    cout << sizeof(Bucket) << endl;
////    cout << sizeof(buckets)/1024.0/1024.0 << endl;
////    cout << sizeof(workshop) << endl;
////    cout << sizeof(shops)/1024.0/1024.0 << endl;

//    cout << sizeof(usersRegister)/1024.0/1024.0  + sizeof(buckets)/1024.0/1024.0 << endl;

//    WAR w;

//    long sum = 0;
//    auto testsCases = {0,1,2,10,11,12,13,20,30};
//    auto nrOfPasses = 1;
//    long max = 0;

//    for (int i = 0; i < nrOfPasses; ++i) {

//        for (auto t : testsCases) {
//            setTestCase(t);
//            long time = judge::run(&w);
//            cout << judge::run(&w) << " ";
//            if (time > max) {
//                max = time;
//            }
//            if (t >= 2) {
//                sum += time;
//            }
//        }
//    }
//    cout << endl << "Avg: " <<  sum / 6 / nrOfPasses << " MAX: " << max << endl;
//}

//void WAR::init(int workshopsNum, int maxParticipants){
//    for (int i = 0; i <= MAX_ID; ++i) {
//        if (usersRegister[i]) {
//            delete usersRegister[i];
//            usersRegister[i] = nullptr;
//        }
//    }

//    for (int i = 0; i < BUCKET_COUNT; i++) {
//        buckets[i].id = i;
//        buckets[i].first = nullptr;
//        buckets[i].last = nullptr;
//    }

//    lastUser = firstUser = nullptr;
//    shops_ctn = workshopsNum;
//    shops_capacity = maxParticipants;

//    for (int i = 0; i < shops_ctn; ++i) {
//        shops[i].cnt = 0;
//        shops[i].last = nullptr;
//        shops[i].id = static_cast<char>(i);
//    }
//}

//int WAR::registration(int byteid, char level[], int preferences[]) {

////    cout << "Adding: " << byteid << endl;

//    auto user = new User(byteid,level,preferences);

//    usersRegister[byteid] = user;

//    addToBuckets(user);

//    User* user2 = nullptr;
//    for (auto pref : user->prefs) {
//        auto& workshop = shops[static_cast<int>(pref)];
//        if (workshop.cnt < shops_capacity || user->rank > workshop.last->rank) {
//            user->current = pref;
//            user2 = workshop.updateAfterAdd(user);
//            break;
//        }
//    }

//    while(user2) {
//        for (auto pref : user2->prefs) {
//            auto& workshop = shops[static_cast<int>(pref)];
//            if (workshop.cnt < shops_capacity || user2->rank > workshop.last->rank) {
//                user2->current = pref;
//                user2 = workshop.updateAfterAdd(user2);
//                break;
//            }
//        }
//    }

//    return user->current;
//}

//User* lookForCandidate(User* user, int shop_id) {
//    if (!user)
//        return nullptr;

//    while (user->next) {
//        user = user->next;
//        for (auto pref : user->prefs) {
//            if (pref == user->current)
//                break;

//            if (pref == shop_id)
//                return user;
//        }
//    }
//    return nullptr;
//}

//int WAR::unregistration(int byteid) {
//    auto user = usersRegister[byteid];

////    cout << "Removing: " << byteid << endl;
//    auto shop_id = user->current;

//    auto new_space = user->current;
//    shops[new_space].prepareBeforeRemove(user);

//    auto candidate = lookForCandidate(shops[new_space].last,new_space);

//    while (candidate) {
//        auto candidate_shop = candidate->current;
//        shops[candidate_shop].prepareBeforeRemove(candidate);
//        candidate->current = new_space;
//        shops[new_space].updateAfterAdd(candidate);
//        new_space = candidate_shop;
//        candidate = lookForCandidate(shops[new_space].last,new_space);
//    }

//    removeFromBuckets(user);

//    delete user;
//    usersRegister[byteid] = nullptr;

//    return shop_id;
//}
