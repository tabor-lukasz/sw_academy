//#include "judge.h"

//#include <iostream>
//#include <initializer_list>
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
//    User(int id, const char * level, int prefs[]) : current(-1) {
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
//    int rank;
//    int current;
//    char prefs[MAX_SHOPS];
//};


//static User* usersRegister[MAX_ID+1];

//void printUser(int rank) {
//    int id = MAX_ID - (rank % (MAX_ID));
//    auto user = usersRegister[id];
//    cout << id << " \t" << user->rank << "\t";
//    for (int i = 0; i < shops_ctn;++i) {
//        cout << (int)user->prefs[i] << " ";
//    }
//    cout << endl;
//}

//enum COLOR { RED, BLACK };

//class Node {
//public:
//    int val;
//    COLOR color;
//    Node *left, *right, *parent;

//    Node(int val) : val(val) {
//        parent = left = right = nullptr;
//        color = RED;
//    }

//    Node *uncle();

//    bool isOnLeft();

//    Node *sibling();

//    void moveDown(Node *nParent);

//    bool hasRedChild();
//};

//Node *Node::uncle() {
//    if (!parent || !parent->parent)
//        return nullptr;

//    if (parent->isOnLeft()) {
//        return parent->parent->right;
//    } else {
//        return parent->parent->left;
//    }
//}

//bool Node::isOnLeft() { return this == parent->left; }

//Node *Node::sibling() {
//    if (parent == nullptr)
//        return nullptr;

//    if (isOnLeft())
//        return parent->right;

//    return parent->left;
//}

//void Node::moveDown(Node *nParent) {
//    if (parent != nullptr) {
//        if (isOnLeft()) {
//            parent->left = nParent;
//        } else {
//            parent->right = nParent;
//        }
//    }
//    nParent->parent = parent;
//    parent = nParent;
//}

//bool Node::hasRedChild() {
//    return (left && left->color == RED) || (right && right->color == RED);
//}

//class RBTree {
//    Node *root;

//    void leftRotate(Node *x) {
//        Node *nParent = x->right;

//        if (x == root)
//            root = nParent;

//        x->moveDown(nParent);

//        x->right = nParent->left;

//        if (nParent->left)
//            nParent->left->parent = x;

//        nParent->left = x;
//    }

//    void rightRotate(Node *x) {
//        Node *nParent = x->left;

//        if (x == root)
//            root = nParent;

//        x->moveDown(nParent);

//        x->left = nParent->right;

//        if (nParent->right != nullptr)
//            nParent->right->parent = x;

//        nParent->right = x;
//    }

//    void swapColors(Node *x1, Node *x2) {
//        COLOR temp;
//        temp = x1->color;
//        x1->color = x2->color;
//        x2->color = temp;
//    }

//    void swapValues(Node *u, Node *v) {
//        int temp;
//        temp = u->val;
//        u->val = v->val;
//        v->val = temp;
//    }

//    void fixRedRed(Node *x) {
//        if (x == root) {
//            x->color = BLACK;
//            return;
//        }

//        Node *parent = x->parent, *grandparent = parent->parent,
//                *uncle = x->uncle();

//        if (parent->color != BLACK) {
//            if (uncle && uncle->color == RED) {
//                parent->color = BLACK;
//                uncle->color = BLACK;
//                grandparent->color = RED;
//                fixRedRed(grandparent);
//            } else {
//                // Perform LR, LL, RL, RR
//                if (parent->isOnLeft()) {
//                    if (x->isOnLeft()) {
//                        // for left right
//                        swapColors(parent, grandparent);
//                    } else {
//                        leftRotate(parent);
//                        swapColors(x, grandparent);
//                    }
//                    // for left left and left right
//                    rightRotate(grandparent);
//                } else {
//                    if (x->isOnLeft()) {
//                        // for right left
//                        rightRotate(parent);
//                        swapColors(x, grandparent);
//                    } else {
//                        swapColors(parent, grandparent);
//                    }
//                    // for right right and right left
//                    leftRotate(grandparent);
//                }
//            }
//        }
//    }

//    Node *successor(Node *x) {
//        Node *temp = x;

//        while (temp->left != nullptr)
//            temp = temp->left;

//        return temp;
//    }

//    // find node that replaces a deleted node in BST
//    Node *BSTreplace(Node *x) {
//        // when node have 2 children
//        if (x->left && x->right)
//            return successor(x->right);

//        // when leaf
//        if (!x->left && !x->right)
//            return nullptr;

//        // when single child
//        if (x->left)
//            return x->left;
//        else
//            return x->right;
//    }

//    // deletes the given node
//    void deleteNode(Node *v) {
//        Node *u = BSTreplace(v);

//        // True when u and v are both black
//        bool uvBlack = ((u == nullptr or u->color == BLACK) and (v->color == BLACK));
//        Node *parent = v->parent;

//        if (!u) {
//            // u is nullptr therefore v is leaf
//            if (v == root) {
//                // v is root, making root nullptr
//                root = nullptr;
//            } else {
//                if (uvBlack) {
//                    // u and v both black
//                    // v is leaf, fix double black at v
//                    fixDoubleBlack(v);
//                } else {
//                    // u or v is red
//                    if (v->sibling() != nullptr)
//                        // sibling is not nullptr, make it red"
//                        v->sibling()->color = RED;
//                }

//                // delete v from the tree
//                if (v->isOnLeft()) {
//                    parent->left = nullptr;
//                } else {
//                    parent->right = nullptr;
//                }
//            }
//            delete v;
//            return;
//        }

//        if (v->left == nullptr or v->right == nullptr) {
//            // v has 1 child
//            if (v == root) {
//                // v is root, assign the value of u to v, and delete u
//                v->val = u->val;
//                v->left = v->right = nullptr;
//                delete u;
//            } else {
//                // Detach v from tree and move u up
//                if (v->isOnLeft()) {
//                    parent->left = u;
//                } else {
//                    parent->right = u;
//                }
//                delete v;
//                u->parent = parent;
//                if (uvBlack) {
//                    // u and v both black, fix double black at u
//                    fixDoubleBlack(u);
//                } else {
//                    // u or v red, color u black
//                    u->color = BLACK;
//                }
//            }
//            return;
//        }

//        // v has 2 children, swap values with successor and recurse
//        swapValues(u, v);
//        deleteNode(u);
//    }

//    void fixDoubleBlack(Node *x) {
//        if (x == root)
//            // Reached root
//            return;

//        Node *sibling = x->sibling(), *parent = x->parent;
//        if (sibling == nullptr) {
//            // No sibiling, double black pushed up
//            fixDoubleBlack(parent);
//        } else {
//            if (sibling->color == RED) {
//                // Sibling red
//                parent->color = RED;
//                sibling->color = BLACK;
//                if (sibling->isOnLeft()) {
//                    // left case
//                    rightRotate(parent);
//                } else {
//                    // right case
//                    leftRotate(parent);
//                }
//                fixDoubleBlack(x);
//            } else {
//                // Sibling black
//                if (sibling->hasRedChild()) {
//                    // at least 1 red children
//                    if (sibling->left != nullptr and sibling->left->color == RED) {
//                        if (sibling->isOnLeft()) {
//                            // left left
//                            sibling->left->color = sibling->color;
//                            sibling->color = parent->color;
//                            rightRotate(parent);
//                        } else {
//                            // right left
//                            sibling->left->color = parent->color;
//                            rightRotate(sibling);
//                            leftRotate(parent);
//                        }
//                    } else {
//                        if (sibling->isOnLeft()) {
//                            // left right
//                            sibling->right->color = parent->color;
//                            leftRotate(sibling);
//                            rightRotate(parent);
//                        } else {
//                            // right right
//                            sibling->right->color = sibling->color;
//                            sibling->color = parent->color;
//                            leftRotate(parent);
//                        }
//                    }
//                    parent->color = BLACK;
//                } else {
//                    // 2 black children
//                    sibling->color = RED;
//                    if (parent->color == BLACK)
//                        fixDoubleBlack(parent);
//                    else
//                        parent->color = BLACK;
//                }
//            }
//        }
//    }

//    void inorder(Node *x) {
//        if (x == nullptr)
//            return;
//        inorder(x->left);
//        printUser(x->val);
//        inorder(x->right);
//    }

//public:
//    // constructor
//    // initialize root
//    RBTree() { root = nullptr; }

//    Node *getRoot() { return root; }

//    // searches for given value
//    // if found returns the node (used for delete)
//    // else returns the last node while traversing (used in insert)
//    Node *search(int n) {
//        Node *temp = root;
//        while (temp != nullptr) {
//            if (n < temp->val) {
//                if (temp->left == nullptr)
//                    break;
//                else
//                    temp = temp->left;
//            } else if (n == temp->val) {
//                break;
//            } else {
//                if (temp->right == nullptr)
//                    break;
//                else
//                    temp = temp->right;
//            }
//        }

//        return temp;
//    }

//    Node *myFind(int n) {
//        auto temp = search(n);
//        if (temp && temp->val == n)
//            return temp;
//        else {
//            return nullptr;
//        }
//    }

//    // inserts the given value to tree
//    void insert(int n) {
//        if (root == nullptr) {
//            Node *newNode = new Node(n);
//            // when root is nullptr
//            // simply insert value at root
//            newNode->color = BLACK;
//            root = newNode;
//        } else {
//            Node *temp = search(n);

//            if (temp->val == n) {
//                // return if value already exists
//                return;
//            }

//            Node *newNode = new Node(n);

//            // if value is not found, search returns the node
//            // where the value is to be inserted

//            // connect new node to correct node
//            newNode->parent = temp;

//            if (n < temp->val)
//                temp->left = newNode;
//            else
//                temp->right = newNode;

//            // fix red red voilaton if exists
//            fixRedRed(newNode);
//        }
//    }

//    // utility function that deletes the node with given value
//    void deleteByVal(int n) {
//        if (root == nullptr)
//            // Tree is empty
//            return;

//        Node *v = search(n);//, *u;

//        if (v->val != n) {
//            return;
//        }

//        deleteNode(v);
//    }

//    int getMin() {
//        int rval = root->val;
//        auto curr = root;
//        while (curr->left) {
//            curr = curr->left;
//        }
//        return curr->val;
//    }
//    int getMax() {
//        int rval = root->val;
//        auto curr = root;
//        while (curr->right) {
//            curr = curr->right;
//        }
//        return curr->val;
//    }

//    void printAsc() {
//        inorder(root);
//        cout << endl;
//    }
//};




//struct workshop {

//    RBTree users;

//    //    int last = -1;
//    int cnt = 0;
//    //    char id;
//};

//static workshop shops[MAX_SHOPS];
//static RBTree reserves[MAX_SHOPS];

//class WAR : public iWAR {
//public:
//    virtual void init(int workshopsNum, int maxParticipants);
//    virtual int registration(int byteid, char level[], int preferences[]);
//    virtual int unregistration(int byteid);
//private:
//};

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

//extern void setTestCase(int);

////int main() {
////    WAR w;
////    judge::run(&w);
////}

//int main() {

////    cout << sizeof (User) << endl;
////    cout << sizeof(usersRegister)/1024.0/1024.0 << endl;
////    cout << sizeof(Bucket) << endl;
////    cout << sizeof(buckets)/1024.0/1024.0 << endl;
////    cout << sizeof(workshop) << endl;
////    cout << sizeof(shops)/1024.0/1024.0 << endl;

////    cout << sizeof(usersRegister)/1024.0/1024.0  + sizeof(buckets)/1024.0/1024.0 << endl;

//    WAR w;

//    long sum = 0;
////    auto testsCases = {0,1,2,10,11,12,13,20,30};
//    auto testsCases = {2};
//    auto nrOfPasses = 1;
//    long max = 0;

//    for (int i = 0; i < nrOfPasses; ++i) {

//        for (auto t : testsCases) {
//            setTestCase(t);
//            long time = judge::run(&w);
//            cout << time << endl;
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
//    for (int i = 0; i < MAX_SHOPS; i++) {
//        while (shops[i].users.getRoot()) {
//            shops[i].users.deleteByVal(shops[i].users.getRoot()->val);
//        }
//        shops[i].cnt = 0;
//        while (reserves[i].getRoot()) {
//            reserves[i].deleteByVal(reserves[i].getRoot()->val);
//        }
//    }

//    for (int i = 0; i <= MAX_ID; ++i) {
//        if (usersRegister[i]) {
//            delete usersRegister[i];
//            usersRegister[i] = nullptr;
//        }
//    }

//    shops_ctn = workshopsNum;
//    shops_capacity = maxParticipants;
//    check();
//}

//int WAR::registration(int byteid, char level[], int preferences[]) {
////    if (usersRegister[byteid]) {
////        int aasa= 0;
////    }
//    auto user = new User(byteid,level,preferences);

//    usersRegister[byteid] = user;

////    if (byteid == 19700001) {
////        check();
////        printUserState(byteid);
////    }

//    for (auto pref : user->prefs) {
//        if (shops[static_cast<int>(pref)].cnt < shops_capacity) {
//            shops[static_cast<int>(pref)].cnt++;
//            shops[static_cast<int>(pref)].users.insert(user->rank);
//            user->current = pref;
//            break;
//        }

//        int to_move = 0;
//        if (shops[static_cast<int>(pref)].users.getMin() < user->rank) {
//            to_move = shops[static_cast<int>(pref)].users.getMin();
//            shops[static_cast<int>(pref)].users.deleteByVal(to_move);
//            shops[static_cast<int>(pref)].users.insert(user->rank);
//            user->current = pref;
//        }

//        while(to_move) {
//            auto id =  MAX_ID - (to_move % (MAX_ID));
//            auto user2 = usersRegister[id];
//            for (auto pref2 : user2->prefs) {
//                if (shops[static_cast<int>(pref2)].cnt < shops_capacity) {
//                    shops[static_cast<int>(pref2)].cnt++;
//                    shops[static_cast<int>(pref2)].users.insert(user2->rank);
//                    //                    if (shops[static_cast<int>(pref2)].users.getMin() > user2->rank) {
//                    //                         shops[static_cast<int>(pref2)].users.getMin() = user2->rank;
//                    //                    }
//                    user2->current = pref2;
//                    to_move = 0;
//                    break;
//                }

//                if (shops[static_cast<int>(pref2)].users.getMin() < user2->rank) {
//                    int to_move2 = shops[static_cast<int>(pref2)].users.getMin();
//                    shops[static_cast<int>(pref2)].users.deleteByVal(to_move2);
//                    shops[static_cast<int>(pref2)].users.insert(user2->rank);
//                    user2->current = pref2;
//                    to_move = to_move2;
//                    break;
//                }

//                reserves[static_cast<int>(pref2)].insert(to_move);
//            }
//        }

//        if (user->current < 0)
//            reserves[static_cast<int>(pref)].insert(user->rank);
//        else
//            break;
//    }

////    if (byteid == 19700001) {
////        check();
////        printUserState(byteid);
////    }

////        cout << "Adding ";
////        printUser(user->rank);
////        printShops();
//    //    cout << "res " << user->current << endl << endl;

//    return user->current;
//}

//int WAR::unregistration(int byteid) {

////    if (byteid == 32) {
////        check();
////        printUserState(byteid);
////        printShops();
////    }

////    if (!usersRegister[byteid]) {
////        int aasa= 0;
////    }

//    auto user = usersRegister[byteid];

////    check();

////    cout << "Removing ";
////    printUser(user->rank);

////    if (19118168 == byteid) {
////        printShops();
////    }
////    if (19496599 == byteid) {
////        printUserState(byteid);
//////        printShops();
////    }

//    for (auto pref : user->prefs) {
//        if (pref == user->current) {
//            shops[static_cast<int>(pref)].users.deleteByVal(user->rank);
//            --shops[static_cast<int>(pref)].cnt;

//            while (reserves[static_cast<int>(pref)].getRoot()) {
//                int to_move = reserves[static_cast<int>(pref)].getMax();
//                auto id =  MAX_ID - (to_move % (MAX_ID));
//                auto user_to_move = usersRegister[id];

//                bool start_removing = false;
//                for (auto pref2 : user_to_move->prefs) {
//                    if (pref2 == pref) {
//                        start_removing = true;
//                        shops[static_cast<int>(pref2)].users.insert(to_move);
//                        ++shops[static_cast<int>(pref2)].cnt;
//                    }

//                    if (pref2 == user_to_move->current) {
//                        shops[static_cast<int>(pref2)].users.deleteByVal(to_move);
//                        --shops[static_cast<int>(pref2)].cnt;
//                        user_to_move->current = pref;
//                        pref = pref2;
//                        break;
//                    }

//                    if (start_removing) {
//                        reserves[static_cast<int>(pref2)].deleteByVal(to_move);
//                    }
//                }
//            }
//            break;
//        } else {
//            reserves[pref].deleteByVal(user->rank);
//        }
////        if (19750002 == byteid) {
////            printUserState(byteid);
////            printShops();
////        }
//    }

////        cout << "Removing ";
////        printUser(user->rank);
////        printShops();
////        cout << "res " << user->current << endl << endl;
//        int rval = user->current;
//        delete user;
//        usersRegister[byteid] = nullptr;

////    if (19750002 == byteid) {
//////        printUserState(byteid);
////        check();
//////        printShops();
////    }
//    return rval;
//}
