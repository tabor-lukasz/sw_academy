#include "judge.h"

//#include <set>
//#include <iostream>
//#include <iomanip>
//using namespace std;

struct Planet;

enum COLOR { RED, BLACK };

class Node {
public:
    Planet* val;
    COLOR color;
    Node *left, *right, *parent;

    Node(Planet* val) : val(val) {
        parent = left = right = nullptr;
        color = RED;
    }

    inline Node *uncle();

    inline bool isOnLeft();

    inline Node *sibling();

    inline void moveDown(Node *nParent);

    inline bool hasRedChild();
};

Node *Node::uncle() {
    if (!parent || !parent->parent)
        return nullptr;

    if (parent->isOnLeft()) {
        return parent->parent->right;
    } else {
        return parent->parent->left;
    }
}

bool Node::isOnLeft() { return this == parent->left; }

Node *Node::sibling() {
    if (parent == nullptr)
        return nullptr;

    if (isOnLeft())
        return parent->right;

    return parent->left;
}

void Node::moveDown(Node *nParent) {
    if (parent != nullptr) {
        if (isOnLeft()) {
            parent->left = nParent;
        } else {
            parent->right = nParent;
        }
    }
    nParent->parent = parent;
    parent = nParent;
}

bool Node::hasRedChild() {
    return (left && left->color == RED) || (right && right->color == RED);
}

class RBTree {
    Node *root;

    void leftRotate(Node *x) {
        Node *nParent = x->right;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;

        if (nParent->left)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void rightRotate(Node *x) {
        Node *nParent = x->left;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;

        if (nParent->right != nullptr)
            nParent->right->parent = x;

        nParent->right = x;
    }

    void swapColors(Node *x1, Node *x2) {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node *u, Node *v) {
        Planet* temp;
        temp = u->val;
        u->val = v->val;
        v->val = temp;
    }

    void fixRedRed(Node *x) {
        if (x == root) {
            x->color = BLACK;
            return;
        }

        Node *parent = x->parent, *grandparent = parent->parent,
                *uncle = x->uncle();

        if (parent->color != BLACK) {
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed(grandparent);
            } else {
                // Perform LR, LL, RL, RR
                if (parent->isOnLeft()) {
                    if (x->isOnLeft()) {
                        // for left right
                        swapColors(parent, grandparent);
                    } else {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    // for left left and left right
                    rightRotate(grandparent);
                } else {
                    if (x->isOnLeft()) {
                        // for right left
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    } else {
                        swapColors(parent, grandparent);
                    }
                    // for right right and right left
                    leftRotate(grandparent);
                }
            }
        }
    }

    Node *successor(Node *x) {
        Node *temp = x;

        while (temp->left != nullptr)
            temp = temp->left;

        return temp;
    }

    // find node that replaces a deleted node in BST
    Node *BSTreplace(Node *x) {
        // when node have 2 children
        if (x->left && x->right)
            return successor(x->right);

        // when leaf
        if (!x->left && !x->right)
            return nullptr;

        // when single child
        if (x->left)
            return x->left;
        else
            return x->right;
    }

    // deletes the given node
    void deleteNode(Node *v) {
        Node *u = BSTreplace(v);

        // True when u and v are both black
        bool uvBlack = ((u == nullptr or u->color == BLACK) and (v->color == BLACK));
        Node *parent = v->parent;

        if (!u) {
            // u is nullptr therefore v is leaf
            if (v == root) {
                // v is root, making root nullptr
                root = nullptr;
            } else {
                if (uvBlack) {
                    // u and v both black
                    // v is leaf, fix double black at v
                    fixDoubleBlack(v);
                } else {
                    // u or v is red
                    if (v->sibling() != nullptr)
                        // sibling is not nullptr, make it red"
                        v->sibling()->color = RED;
                }

                // delete v from the tree
                if (v->isOnLeft()) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }
            delete v;
            return;
        }

        if (v->left == nullptr or v->right == nullptr) {
            // v has 1 child
            if (v == root) {
                // v is root, assign the value of u to v, and delete u
                v->val = u->val;
                v->left = v->right = nullptr;
                delete u;
            } else {
                // Detach v from tree and move u up
                if (v->isOnLeft()) {
                    parent->left = u;
                } else {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack) {
                    // u and v both black, fix double black at u
                    fixDoubleBlack(u);
                } else {
                    // u or v red, color u black
                    u->color = BLACK;
                }
            }
            return;
        }

        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node *x) {
        if (x == root)
            // Reached root
            return;

        Node *sibling = x->sibling(), *parent = x->parent;
        if (sibling == nullptr) {
            // No sibiling, double black pushed up
            fixDoubleBlack(parent);
        } else {
            if (sibling->color == RED) {
                // Sibling red
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft()) {
                    // left case
                    rightRotate(parent);
                } else {
                    // right case
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            } else {
                // Sibling black
                if (sibling->hasRedChild()) {
                    // at least 1 red children
                    if (sibling->left != nullptr and sibling->left->color == RED) {
                        if (sibling->isOnLeft()) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    } else {
                        if (sibling->isOnLeft()) {
                            // left right
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                } else {
                    // 2 black children
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }

public:
    // constructor
    // initialize root
    RBTree() { root = nullptr; }

    Node *getRoot() { return root; }

    // searches for given value
    // if found returns the node (used for delete)
    // else returns the last node while traversing (used in insert)
    Node *search(Planet* n) {
        Node *temp = root;
        while (temp != nullptr) {
            if (n < temp->val) {
                if (temp->left == nullptr)
                    break;
                else
                    temp = temp->left;
            } else if (n == temp->val) {
                break;
            } else {
                if (temp->right == nullptr)
                    break;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    // inserts the given value to tree
    void insert(Planet* n) {
        if (root == nullptr) {
            Node *newNode = new Node(n);
            // when root is nullptr
            // simply insert value at root
            newNode->color = BLACK;
            root = newNode;
        } else {
            Node *temp = search(n);

            if (temp->val == n) {
                // return if value already exists
                return;
            }

            Node *newNode = new Node(n);

            // if value is not found, search returns the node
            // where the value is to be inserted

            // connect new node to correct node
            newNode->parent = temp;

            if (n < temp->val)
                temp->left = newNode;
            else
                temp->right = newNode;

            // fix red red voilaton if exists
            fixRedRed(newNode);
        }
    }

    // utility function that deletes the node with given value
    void deleteByVal(Planet* n) {
        if (root == nullptr)
            // Tree is empty
            return;

        Node *v = search(n);//, *u;

        if (v->val != n) {
            return;
        }

        deleteNode(v);
    }
};

enum Operation {
    PROD,
    TRADE,
    PROC,
    ATT,
    TAX
};

struct Point {
    int x;
    int y;
};

class galaxy;

struct Planet {

    static const int GALAXY_SIZE = 100;
    static Planet universe[GALAXY_SIZE][GALAXY_SIZE];

    void update(long long production);
    void update(Operation _type, Point _p1, Point _p2);

    long long int getValue() {return value;}

    void subscribe(Planet* planet) {subscribers.insert(planet);}
    void unsubscribe(Planet* planet) {subscribers.deleteByVal(planet);}

    void onValueChanged(Planet* planet, long long value);

private:

    void notifyChange();
    void notifyOne(Node* node);

    bool updateValue(Planet* planet, long long notifyValue);

    RBTree subscribers;

    Operation type = PROD;
    long long value = 0;
    Point p1;
    Point p2;
    Planet* currentTarget;

    long long int calcTrade();
    long long int calcProc();
    long long int calcAtt();
    long long int calcTax();
};

void Planet::update(long long production) {
    switch (type) {
    case TRADE:
    case PROC: {
        universe[p1.x][p1.y].unsubscribe(this);
        universe[p2.x][p2.y].unsubscribe(this);
        break;
    }
    case TAX:
    case ATT: {
        for (int i = p1.x; i <= p2.x; ++i) {
            for (int j = p1.y; j <= p2.y; ++j) {
                if (&universe[i][j] != this) {
                    universe[i][j].unsubscribe(this);
                }
            }
        }
        break;
    }
    }

    auto old_val = value;

    type = PROD;
    value = production;

    if (value != old_val){
        notifyChange();
    }
}

void Planet::update(Operation _type, Point _p1, Point _p2) {

    switch (type) {
    case TRADE:
    case PROC: {
        universe[p1.x][p1.y].unsubscribe(this);
        universe[p2.x][p2.y].unsubscribe(this);
        break;
    }
    case TAX:
    case ATT: {
        for (int i = p1.x; i <= p2.x; ++i) {
            for (int j = p1.y; j <= p2.y; ++j) {
                if (&universe[i][j] != this) {
                    universe[i][j].unsubscribe(this);
                }
            }
        }
        break;
    }
    }


    type = _type;
    p1 = _p1;
    p2 = _p2;

    switch (type) {
    case TRADE:
    case PROC: {
        universe[p1.x][p1.y].subscribe(this);
        universe[p2.x][p2.y].subscribe(this);
        break;
    }
    case TAX:
    case ATT: {
        for (int i = p1.x; i <= p2.x; ++i) {
            for (int j = p1.y; j <= p2.y; ++j) {
                if (&universe[i][j] != this) {
                    universe[i][j].subscribe(this);
                }
            }
        }
        break;
    }
    }

    auto old_val = value;

    switch (type) {
    case TRADE: {
        value = calcTrade();
        break;
    }
    case PROC: {
        value = calcProc();
        break;
    }
    case ATT: {
        value = calcAtt();
        break;
    }
    case TAX: {
        value = calcTax();
        break;
    }
    }

    if (value != old_val) {
        notifyChange();
    }
}

void Planet::notifyChange() {    
    notifyOne(subscribers.getRoot());

//    for (auto planet : subscribers) {
//        planet->onValueChanged(this,value);
//    }
}

void Planet::notifyOne(Node *node) {
    if (!node)
        return;

    notifyOne(node->left);
    node->val->onValueChanged(this,value);
    notifyOne(node->right);
}

void Planet::onValueChanged(Planet* planet, long long notifyValue) {
    auto old_val = value;
    updateValue(planet,notifyValue);
    if (old_val != value) {
        notifyChange();
    }
}

bool Planet::updateValue(Planet* planet, long long notifyValue) {
    switch (type) {
    case PROC:
        value = calcProc();
        break;
    case TRADE:
        value = calcTrade();
        break;
    case TAX:
        if (planet == currentTarget) {
            value = calcTax();
        } else {
            if (value < notifyValue) {
                value = notifyValue;
                currentTarget = planet;
            }
        }
        break;
    case ATT:
        if (planet == currentTarget) {
            value = calcAtt();
        } else {
            if (value > notifyValue) {
                value = notifyValue;
                currentTarget = planet;
            }
        }
        break;
    }
}

Planet Planet::universe[GALAXY_SIZE][GALAXY_SIZE];

long long int Planet::calcTrade() {
    return universe[p1.x][p1.y].getValue() + universe[p2.x][p2.y].getValue();
}

long long int Planet::calcProc() {
    return 2*calcTrade();
}

long long int Planet::calcAtt() {
    long long min;
    if (&universe[p1.x][p1.y] != this) {
        min = universe[p1.x][p1.y].getValue();
        currentTarget = &universe[p1.x][p1.y];
    } else if (&universe[p2.x][p2.y] != this) {
        min = universe[p2.x][p2.y].getValue();
        currentTarget = &universe[p2.x][p2.y];
    } else {
        throw "calcAtt";
    }

    for (int i = p1.x; i <= p2.x; ++i) {
        for (int j = p1.y; j <= p2.y; ++j) {
            if (&universe[i][j] != this) {
                if (min > universe[i][j].getValue()) {
                    min = universe[i][j].getValue();
                    currentTarget = &universe[i][j];
                }
            }
        }
    }

    return min;
}

long long int Planet::calcTax() {
    long long max;
    if (&universe[p1.x][p1.y] != this) {
        max = universe[p1.x][p1.y].getValue();
        currentTarget = &universe[p1.x][p1.y];
    } else if (&universe[p2.x][p2.y] != this) {
        max = universe[p2.x][p2.y].getValue();
        currentTarget = &universe[p2.x][p2.y];
    } else {
        throw "calcTax";
    }

    for (int i = p1.x; i <= p2.x; ++i) {
        for (int j = p1.y; j <= p2.y; ++j) {
            if (&universe[i][j] != this) {
                if (max < universe[i][j].getValue()) {
                    max = universe[i][j].getValue();
                    currentTarget = &universe[i][j];
                }
            }
        }
    }
    return max;
}

class galaxy : public igalaxy {
public:
    void report(char* text);
    void summary(long long int output[100][100]);
private:

    char* parseNumber(char* ss, long long &number);
    char* parseNumber(char* ss, int &number);
};

char* galaxy::parseNumber(char* ss, long long &number){
    number = 0;
    while (*ss >= '0' && *ss <= '9') {
        number *= 10;
        number += *ss - '0';
        ++ss;
    }
    return ss;
}

char* galaxy::parseNumber(char* ss, int &number){
    number = 0;
    while (*ss >= '0' && *ss <= '9') {
        number *= 10;
        number += *ss - '0';
        ++ss;
    }
    return ss;
}

void galaxy::report(char* text) {
    int x, y;
    text = parseNumber(text+1,x);
    text = parseNumber(text+1,y);

    int p1x, p1y, p2x, p2y;
    int offset;
    Operation oper;

    switch (*(text+4)) {
    case 'o': {
        long long value;
        parseNumber(text+12,value);
        Planet::universe[x][y].update(value);
        return;
    }
    case 'n': {
        oper = TRADE;
        offset = 10;
        break;
    }
    case 'z': {
        oper = PROC;
        offset = 17;
        break;
    }
    case 'a': {
        oper = ATT;
        offset = 9;
        break;
    }
    case 'd': {
        oper = TAX;
        offset = 11;
        break;
    }
    }

    text = parseNumber(text+offset,p1x);
    text = parseNumber(text+1,p1y);
    text = parseNumber(text+3,p2x);
    text = parseNumber(text+1,p2y);
    Planet::universe[x][y].update(oper,{p1x,p1y},{p2x,p2y});
}

void galaxy::summary(long long int output[100][100]) {
    for (int i = 0; i < Planet::GALAXY_SIZE; ++i) {
        for (int j = 0; j < Planet::GALAXY_SIZE; ++j) {
            output[i][j] = Planet::universe[i][j].getValue();
        }
    }
}

galaxy solution;
int main() {
    judge::run(&solution);
    return 0;
}
