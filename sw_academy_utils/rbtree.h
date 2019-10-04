#ifndef RBTREE_H
#define RBTREE_H

enum COLOR { RED, BLACK };

template<typename T>
class Node {
public:
    T val;
    COLOR color;
    Node *left, *right, *parent;

    Node(T val) : val(val) {
        parent = left = right = nullptr;
        color = RED;
    }

    inline Node<T> *uncle() {
        if (!parent || !parent->parent)
            return nullptr;

        if (parent->isOnLeft()) {
            return parent->parent->right;
        } else {
            return parent->parent->left;
        }
    }

    inline bool isOnLeft() { return this == parent->left; }

    inline Node *sibling() {
        if (parent == nullptr)
            return nullptr;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    inline void moveDown(Node *nParent) {
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

    inline bool hasRedChild() {
        return (left && left->color == RED) || (right && right->color == RED);
    }
};

template<typename T>
class RBTree {
    Node<T> *root;

    void leftRotate(Node<T> *x) {
        auto nParent = x->right;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;

        if (nParent->left)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void rightRotate(Node<T> *x) {
        auto nParent = x->left;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;

        if (nParent->right != nullptr)
            nParent->right->parent = x;

        nParent->right = x;
    }

    void swapColors(Node<T> *x1, Node<T> *x2) {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node<T> *u, Node<T> *v) {
        auto temp = u->val;
        u->val = v->val;
        v->val = temp;
    }

    void fixRedRed(Node<T> *x) {
        if (x == root) {
            x->color = BLACK;
            return;
        }

        Node<T> *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();

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

    Node<T> *successor(Node<T> *x) {
        auto temp = x;

        while (temp->left != nullptr)
            temp = temp->left;

        return temp;
    }

    // find node that replaces a deleted node in BST
    Node<T> *BSTreplace(Node<T> *x) {
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
    void deleteNode(Node<T> *v) {
        Node<T> *u = BSTreplace(v);

        // True when u and v are both black
        bool uvBlack = ((u == nullptr or u->color == BLACK) and (v->color == BLACK));
        Node<T> *parent = v->parent;

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

    void fixDoubleBlack(Node<T> *x) {
        if (x == root)
            // Reached root
            return;

        Node<T> *sibling = x->sibling(), *parent = x->parent;
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

    Node<T> *getRoot() { return root; }

    Node<T> *getMin() {
        if (!root) {
            return nullptr;
        }
        auto node = root;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node<T> *getMax() {
        if (!root) {
            return nullptr;
        }
        auto node = root;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    // searches for given value
    // if found returns the node (used for delete)
    // else returns the last node while traversing (used in insert)
    Node<T> *search(const T& n) {
        auto temp = root;
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
    void insert(const T& n) {
        if (root == nullptr) {
            auto newNode = new Node<T>(n);
            // when root is nullptr
            // simply insert value at root
            newNode->color = BLACK;
            root = newNode;
        } else {
            auto temp = search(n);

            if (temp->val == n) {
                // return if value already exists
                return;
            }

            auto newNode = new Node<T>(n);

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
    void deleteByVal(const T& n) {
        if (root == nullptr)
            // Tree is empty
            return;

        auto v = search(n);//, *u;

        if (v->val != n) {
            return;
        }

        deleteNode(v);
    }
    void removeRoot() {
        if (root == nullptr)
            // Tree is empty
            return;

        deleteNode(root);
    }
};

#endif // RBTREE_H
