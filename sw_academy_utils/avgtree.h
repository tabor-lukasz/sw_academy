#ifndef AVGTREE_H
#define AVGTREE_H

enum COLOR { RED, BLACK };

template <typename K, typename V>
class Node {
public:
    Node *left, *right, *parent;
    V value;
    K key;
    COLOR color;

    Node(K key, V val) : value(val), key(key) {
        parent = left = right = nullptr;
        color = RED;
    }

    ~Node() = default;

    inline Node *uncle() {
        if (!parent || !parent->parent)
            return nullptr;

        if (parent->isOnLeft()) {
            return parent->parent->right;
        } else {
            return parent->parent->left;
        }
    }

    inline bool isOnLeft() {return this == parent->left;}

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

    Node* getMin() {
        if (left)
            return left->getMin();
        else {
            return this;
        }
    }


    Node* getNext(Node*prev=nullptr) {
        if (right && prev != right)
            return right->getMin();

        if (!parent)
            return nullptr;

        if (parent->right == this)
            return parent->getNext(this);

        return parent;
    }
};

template <typename K, typename V>
class RBTree {
    Node<K,V> *root = nullptr;

    void leftRotate(Node<K,V> *x) {
        Node<K,V> *nParent = x->right;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;

        if (nParent->left)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void rightRotate(Node<K,V> *x) {
        Node<K,V> *nParent = x->left;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;

        if (nParent->right != nullptr)
            nParent->right->parent = x;

        nParent->right = x;
    }

    void swapColors(Node<K,V> *x1, Node<K,V> *x2) {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node<K,V> *u, Node<K,V> *v) {
        K tempK;
        V tempV;
        tempK = u->key;
        u->key = v->key;
        v->key = tempK;
        tempV = u->value;
        u->value = v->value;
        v->value = tempV;
    }

    void fixRedRed(Node<K,V> *x) {
        if (x == root) {
            x->color = BLACK;
            return;
        }

        Node<K,V> *parent = x->parent, *grandparent = parent->parent,
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

    Node<K,V> *successor(Node<K,V> *x) {
        Node<K,V> *temp = x;

        while (temp->left != nullptr)
            temp = temp->left;

        return temp;
    }

    // find node that replaces a deleted node in BST
    Node<K,V> *BSTreplace(Node<K,V> *x) {
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
    void deleteNode(Node<K,V> *v) {
        Node<K,V> *u = BSTreplace(v);

        // True when u and v are both black
        bool uvBlack = ((u == nullptr or u->color == BLACK) and (v->color == BLACK));
        Node<K,V> *parent = v->parent;

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
                // v is root, assign the keyue of u to v, and delete u
                v->key = u->key;
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

        // v has 2 children, swap keyues with successor and recurse
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node<K,V> *x) {
        if (x == root)
            // Reached root
            return;

        Node<K,V> *sibling = x->sibling(), *parent = x->parent;
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
    ~RBTree() {clear();}

    void clear(){
        while(root) {
            deleteNode(root);
        }
    }

    Node<K,V> *getRoot() { return root; }

    // searches for given keyue
    // if found returns the node (used for delete)
    // else returns the last node while traversing (used in insert)
    Node<K,V> *search(K n) {
        Node<K,V> *temp = root;
        while (temp != nullptr) {
            if (n < temp->key) {
                if (temp->left == nullptr)
                    break;
                else
                    temp = temp->left;
            } else if (n == temp->key) {
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

    Node<K,V> *searchPrecise(K n) {
        Node<K,V> *temp = root;
        while (temp != nullptr) {
            if (n < temp->key) {
                if (temp->left == nullptr)
                    break;
                else
                    temp = temp->left;
            } else if (n == temp->key) {
                return temp;
            } else {
                if (temp->right == nullptr)
                    break;
                else
                    temp = temp->right;
            }
        }

        return nullptr;
    }

    // inserts the given keyue to tree
    void insert(K n, V v) {
        if (root == nullptr) {
            Node<K,V> *newNode = new Node<K,V>(n,v);
            // when root is nullptr
            // simply insert keyue at root
            newNode->color = BLACK;
            root = newNode;
        } else {
            Node<K,V> *temp = search(n);

            if (temp->key == n) {
                // return if keyue already exists
                return;
            }

            Node<K,V> *newNode = new Node<K,V>(n,v);

            // if keyue is not found, search returns the node
            // where the keyue is to be inserted

            // connect new node to correct node
            newNode->parent = temp;

            if (n < temp->key)
                temp->left = newNode;
            else
                temp->right = newNode;

            // fix red red voilaton if exists
            fixRedRed(newNode);
        }
    }

    // utility function that deletes the node with given keyue
    void deleteByKey(K n) {
        if (root == nullptr)
            // Tree is empty
            return;

        Node<K,V> *v = search(n);//, *u;

        if (v->key != n) {
            return;
        }
        deleteNode(v);
    }
};

#endif // AVGTREE_H
