//#include "judge.h"

//static const int MAX_SHOPS = 5;
//static const int MAX_ID = 20000000;
//static const int SWT_LEVELS = 5;
//static const int MAX_PARTICIPANTS = 100000;

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
//    char current;
//    char prefs[MAX_SHOPS];
//};

//static User* usersRegister[MAX_ID+1];

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
//    void leftRotate(Node *x);
//    void rightRotate(Node *x);
//    void swapColors(Node *x1, Node *x2);
//    void swapValues(Node *u, Node *v);
//    void fixRedRed(Node *x);
//    Node *successor(Node *x);
//    Node *BSTreplace(Node *x);
//    void deleteNode(Node *v);
//    void fixDoubleBlack(Node *x);

//public:
//    RBTree() { root = nullptr; }
//    Node *getRoot() { return root; }
//    inline Node *search(int n);
//    void insert(int n);
//    void deleteByVal(int n);
//    int getMin();
//    int getMax();
//};

//void RBTree::leftRotate(Node *x) {
//    Node *nParent = x->right;

//    if (x == root)
//        root = nParent;

//    x->moveDown(nParent);

//    x->right = nParent->left;

//    if (nParent->left)
//        nParent->left->parent = x;

//    nParent->left = x;
//}

//void RBTree::rightRotate(Node *x) {
//    Node *nParent = x->left;

//    if (x == root)
//        root = nParent;

//    x->moveDown(nParent);

//    x->left = nParent->right;

//    if (nParent->right != nullptr)
//        nParent->right->parent = x;

//    nParent->right = x;
//}

//void RBTree::swapColors(Node *x1, Node *x2) {
//    COLOR temp;
//    temp = x1->color;
//    x1->color = x2->color;
//    x2->color = temp;
//}

//void RBTree::swapValues(Node *u, Node *v) {
//    int temp;
//    temp = u->val;
//    u->val = v->val;
//    v->val = temp;
//}

//void RBTree::fixRedRed(Node *x) {
//    if (x == root) {
//        x->color = BLACK;
//        return;
//    }

//    Node *parent = x->parent, *grandparent = parent->parent,
//            *uncle = x->uncle();

//    if (parent->color != BLACK) {
//        if (uncle && uncle->color == RED) {
//            parent->color = BLACK;
//            uncle->color = BLACK;
//            grandparent->color = RED;
//            fixRedRed(grandparent);
//        } else {
//            // Perform LR, LL, RL, RR
//            if (parent->isOnLeft()) {
//                if (x->isOnLeft()) {
//                    // for left right
//                    swapColors(parent, grandparent);
//                } else {
//                    leftRotate(parent);
//                    swapColors(x, grandparent);
//                }
//                // for left left and left right
//                rightRotate(grandparent);
//            } else {
//                if (x->isOnLeft()) {
//                    // for right left
//                    rightRotate(parent);
//                    swapColors(x, grandparent);
//                } else {
//                    swapColors(parent, grandparent);
//                }
//                // for right right and right left
//                leftRotate(grandparent);
//            }
//        }
//    }
//}

//Node *RBTree::successor(Node *x) {
//    Node *temp = x;

//    while (temp->left != nullptr)
//        temp = temp->left;

//    return temp;
//}

//// find node that replaces a deleted node in BST
//Node *RBTree::BSTreplace(Node *x) {
//    // when node have 2 children
//    if (x->left && x->right)
//        return successor(x->right);

//    // when leaf
//    if (!x->left && !x->right)
//        return nullptr;

//    // when single child
//    if (x->left)
//        return x->left;
//    else
//        return x->right;
//}

//// deletes the given node
//void RBTree::deleteNode(Node *v) {
//    Node *u = BSTreplace(v);

//    // True when u and v are both black
//    bool uvBlack = ((u == nullptr or u->color == BLACK) and (v->color == BLACK));
//    Node *parent = v->parent;

//    if (!u) {
//        // u is nullptr therefore v is leaf
//        if (v == root) {
//            // v is root, making root nullptr
//            root = nullptr;
//        } else {
//            if (uvBlack) {
//                // u and v both black
//                // v is leaf, fix double black at v
//                fixDoubleBlack(v);
//            } else {
//                // u or v is red
//                if (v->sibling() != nullptr)
//                    // sibling is not nullptr, make it red"
//                    v->sibling()->color = RED;
//            }

//            // delete v from the tree
//            if (v->isOnLeft()) {
//                parent->left = nullptr;
//            } else {
//                parent->right = nullptr;
//            }
//        }
//        delete v;
//        return;
//    }

//    if (v->left == nullptr or v->right == nullptr) {
//        // v has 1 child
//        if (v == root) {
//            // v is root, assign the value of u to v, and delete u
//            v->val = u->val;
//            v->left = v->right = nullptr;
//            delete u;
//        } else {
//            // Detach v from tree and move u up
//            if (v->isOnLeft()) {
//                parent->left = u;
//            } else {
//                parent->right = u;
//            }
//            delete v;
//            u->parent = parent;
//            if (uvBlack) {
//                // u and v both black, fix double black at u
//                fixDoubleBlack(u);
//            } else {
//                // u or v red, color u black
//                u->color = BLACK;
//            }
//        }
//        return;
//    }

//    // v has 2 children, swap values with successor and recurse
//    swapValues(u, v);
//    deleteNode(u);
//}

//void RBTree::fixDoubleBlack(Node *x) {
//    if (x == root)
//        // Reached root
//        return;

//    Node *sibling = x->sibling(), *parent = x->parent;
//    if (sibling == nullptr) {
//        // No sibiling, double black pushed up
//        fixDoubleBlack(parent);
//    } else {
//        if (sibling->color == RED) {
//            // Sibling red
//            parent->color = RED;
//            sibling->color = BLACK;
//            if (sibling->isOnLeft()) {
//                // left case
//                rightRotate(parent);
//            } else {
//                // right case
//                leftRotate(parent);
//            }
//            fixDoubleBlack(x);
//        } else {
//            // Sibling black
//            if (sibling->hasRedChild()) {
//                // at least 1 red children
//                if (sibling->left != nullptr and sibling->left->color == RED) {
//                    if (sibling->isOnLeft()) {
//                        // left left
//                        sibling->left->color = sibling->color;
//                        sibling->color = parent->color;
//                        rightRotate(parent);
//                    } else {
//                        // right left
//                        sibling->left->color = parent->color;
//                        rightRotate(sibling);
//                        leftRotate(parent);
//                    }
//                } else {
//                    if (sibling->isOnLeft()) {
//                        // left right
//                        sibling->right->color = parent->color;
//                        leftRotate(sibling);
//                        rightRotate(parent);
//                    } else {
//                        // right right
//                        sibling->right->color = sibling->color;
//                        sibling->color = parent->color;
//                        leftRotate(parent);
//                    }
//                }
//                parent->color = BLACK;
//            } else {
//                // 2 black children
//                sibling->color = RED;
//                if (parent->color == BLACK)
//                    fixDoubleBlack(parent);
//                else
//                    parent->color = BLACK;
//            }
//        }
//    }
//}

//inline Node *RBTree::search(int n) {
//    Node *temp = root;
//    while (temp != nullptr) {
//        if (n < temp->val) {
//            if (temp->left == nullptr)
//                break;
//            else
//                temp = temp->left;
//        } else if (n == temp->val) {
//            break;
//        } else {
//            if (temp->right == nullptr)
//                break;
//            else
//                temp = temp->right;
//        }
//    }

//    return temp;
//}

//// inserts the given value to tree
//inline void RBTree::insert(int n) {
//    if (root == nullptr) {
//        Node *newNode = new Node(n);
//        // when root is nullptr
//        // simply insert value at root
//        newNode->color = BLACK;
//        root = newNode;
//    } else {
//        Node *temp = search(n);

//        if (temp->val == n) {
//            // return if value already exists
//            return;
//        }

//        Node *newNode = new Node(n);

//        // if value is not found, search returns the node
//        // where the value is to be inserted

//        // connect new node to correct node
//        newNode->parent = temp;

//        if (n < temp->val)
//            temp->left = newNode;
//        else
//            temp->right = newNode;

//        // fix red red voilaton if exists
//        fixRedRed(newNode);
//    }
//}

//// utility function that deletes the node with given value
//void RBTree::deleteByVal(int n) {
//    if (root == nullptr)
//        // Tree is empty
//        return;

//    Node *v = search(n);//, *u;

//    if (v->val != n) {
//        return;
//    }

//    deleteNode(v);
//}

//int RBTree::getMin() {
//    int rval = root->val;
//    auto curr = root;
//    while (curr->left) {
//        curr = curr->left;
//    }
//    return curr->val;
//}
//int RBTree::getMax() {
//    int rval = root->val;
//    auto curr = root;
//    while (curr->right) {
//        curr = curr->right;
//    }
//    return curr->val;
//}

//struct workshop {

//    RBTree users;
//    int cnt = 0;
//};

//static workshop shops[MAX_SHOPS];
//static RBTree reserves[MAX_SHOPS];

//class WAR : public iWAR {
//public:
//    virtual void init(int workshopsNum, int maxParticipants);
//    virtual int registration(int byteid, char level[], int preferences[]);
//    virtual int unregistration(int byteid);
//};

//int main() {
//    WAR w;
//    judge::run(&w);
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
//}

//int WAR::registration(int byteid, char level[], int preferences[]) {

//    usersRegister[byteid] = new User(byteid,level,preferences);

//    auto& user = *usersRegister[byteid];

//    for (auto pref : user.prefs) {
//        if (shops[static_cast<int>(pref)].cnt < shops_capacity) {
//            shops[static_cast<int>(pref)].cnt++;
//            shops[static_cast<int>(pref)].users.insert(user.rank);
//            user.current = pref;
//            break;
//        }

//        int to_move = 0;
//        if (shops[static_cast<int>(pref)].users.getMin() < user.rank) {
//            to_move = shops[static_cast<int>(pref)].users.getMin();
//            shops[static_cast<int>(pref)].users.deleteByVal(to_move);
//            shops[static_cast<int>(pref)].users.insert(user.rank);
//            user.current = pref;
//        }

//        while(to_move) {
//            auto id =  MAX_ID - (to_move % (MAX_ID));
//            auto& user2 = *usersRegister[id];
//            for (auto pref2 : user2.prefs) {
//                if (shops[static_cast<int>(pref2)].cnt < shops_capacity) {
//                    shops[static_cast<int>(pref2)].cnt++;
//                    shops[static_cast<int>(pref2)].users.insert(user2.rank);
//                    user2.current = pref2;
//                    to_move = 0;
//                    break;
//                }

//                if (shops[static_cast<int>(pref2)].users.getMin() < user2.rank) {
//                    int to_move2 = shops[static_cast<int>(pref2)].users.getMin();
//                    shops[static_cast<int>(pref2)].users.deleteByVal(to_move2);
//                    shops[static_cast<int>(pref2)].users.insert(user2.rank);
//                    user2.current = pref2;
//                    to_move = to_move2;
//                    break;
//                }

//                reserves[static_cast<int>(pref2)].insert(to_move);
//            }
//        }

//        if (user.current < 0)
//            reserves[static_cast<int>(pref)].insert(user.rank);
//        else
//            break;
//    }
//    return user.current;
//}

//int WAR::unregistration(int byteid) {
//    auto& user = *usersRegister[byteid];

//    for (auto pref : user.prefs) {
//        if (pref == user.current) {
//            shops[static_cast<int>(pref)].users.deleteByVal(user.rank);
//            --shops[static_cast<int>(pref)].cnt;

//            while (reserves[static_cast<int>(pref)].getRoot()) {
//                int to_move = reserves[static_cast<int>(pref)].getMax();
//                auto id =  MAX_ID - (to_move % (MAX_ID));
//                auto& user_to_move = *usersRegister[id];

//                bool start_removing = false;
//                for (auto pref2 : user_to_move.prefs) {
//                    if (pref2 == pref) {
//                        start_removing = true;
//                        shops[static_cast<int>(pref2)].users.insert(to_move);
//                        ++shops[static_cast<int>(pref2)].cnt;
//                    }

//                    if (pref2 == user_to_move.current) {
//                        shops[static_cast<int>(pref2)].users.deleteByVal(to_move);
//                        --shops[static_cast<int>(pref2)].cnt;
//                        user_to_move.current = pref;
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
//            reserves[pref].deleteByVal(user.rank);
//        }
//    }
//    return user.current;
//}
