#include "judge.h"

//#include <iostream>
//using namespace std;

const int MAX_NODE_ID = 1000000;

struct Connection {
    int toId;
    int linkThroughput;
};

struct LinkInfo {
    LinkInfo() {};
    LinkInfo(int _from, int _to, int _link) : from(_from), to(_to), linkThroughput(_link) {}
    int from  = -1;
    int to = -1;
    int linkThroughput = 1000000005;
};

template <typename T>
class List {

    template<typename K>
    class ListNode {
    public :

        ListNode() {}
        ListNode(const K& other) {
            value = other;
        }

        K value;
        ListNode* next = nullptr;
        ListNode* prev = nullptr;
    };

public:

    ~List() {
        while(!empty()) {
            pop_front();
        }
    }

    bool empty() const {
        return root == nullptr;
    }

    void push_back(const T& element) {
        if (!root) {
            last = root = new ListNode<T>(element);
        } else {
            last->next = new ListNode<T>(element);
            last->next->prev = last;
            last = last->next;
        }
        ++_size;
    }

    T front() {
        return root->value;
    }

    void pop_front() {
        if (root) {
            auto tmp = root;
            if (root->next) {
                root->next->prev = nullptr;
            }
            root = root->next;

            --_size;
            if (_size == 0) {
                last = nullptr;
            }

            delete tmp;
        }
    }

    int size() const {return _size;}

    ListNode<T>* begin() const {
        return root;
    }

    void erase(ListNode<T>* element) {
        if (element == root) {
            pop_front();
            return;
        }

        if (element == last) {
            last->prev->next = nullptr;
            last = last->prev;
            delete element;
            --_size;
            return;
        }

        element->next->prev = element->prev;
        element->prev->next = element->next;
        delete element;
        --_size;
    }

private:
    ListNode<T>* root = nullptr;
    ListNode<T>* last = nullptr;
    int _size = 0;
};


class Node {
public:
    int visitId = -1;
    List<Connection> links;
};


class SIE : public iSIE {
public:

    SIE() {
        nodes = new Node[MAX_NODE_ID+1];
    }

    ~SIE() {delete [] nodes;}

    virtual void addServer(int idNew, int idExisting, int linkThroughput)
    {
        nodes[idNew].links.push_back({idExisting,linkThroughput});
        nodes[idExisting].links.push_back({idNew,linkThroughput});
    }

    virtual int directLinks(int id)
    {
        return nodes[id].links.size();
    }

    virtual int connectionThroughput(int id1, int id2)
    {
        LinkInfo minInit;
        return findMinLink(id1,id2,minInit,searchId++).linkThroughput;
    }
    virtual void improveThroughput(int id1, int id2, int newThroughput)
    {
        LinkInfo minInit;
        auto link = findMinLink(id1,id2,minInit,searchId++);
        if (link.linkThroughput < newThroughput) {
            for (auto itr = nodes[link.to].links.begin();itr;itr = itr->next){
                if (itr->value.toId == link.from) {
                    nodes[link.to].links.erase(itr);
                    break;
                }
            }

            for (auto itr = nodes[link.from].links.begin();itr;itr = itr->next){
                if (itr->value.toId == link.to) {
                    nodes[link.from].links.erase(itr);
                    break;
                }
            }

            nodes[id1].links.push_back({id2,newThroughput});
            nodes[id2].links.push_back({id1,newThroughput});
        }
    }

    int getMin(int a, int b) {
        return a < b ? a : b;
    }

    int getMax(int a, int b) {
        return a > b ? a : b;
    }


    LinkInfo findMinLink(int from, int to, LinkInfo currentMin , int searchId) {

        struct SearchTarget {
            int to;
            LinkInfo currentMin;
        };

        List<SearchTarget> targets;
        nodes[from].visitId = searchId;
        for (auto link = nodes[from].links.begin();link; link = link->next) {

            if (link->value.toId == to) {
                return LinkInfo(from,link->value.toId,link->value.linkThroughput);
            }

            SearchTarget target;
            target.to = link->value.toId;
            target.currentMin = LinkInfo(from, link->value.toId, link->value.linkThroughput);

            targets.push_back(target);
        }


        while (!targets.empty()) {
            auto target = targets.front();
            targets.pop_front();

            nodes[target.to].visitId = searchId;

            for (auto link = nodes[target.to].links.begin();link; link = link->next) {
                if (nodes[link->value.toId].visitId != searchId) {

                    bool updateLink = false;
                    if (link->value.linkThroughput < target.currentMin.linkThroughput) {
                        updateLink = true;
                    } else if(link->value.linkThroughput == target.currentMin.linkThroughput) {
                        auto newLinkMin = getMin(target.to,link->value.toId);
                        auto oldLinkMin = getMin(target.currentMin.from,target.currentMin.to);
                        if (newLinkMin < oldLinkMin) {
                            updateLink = true;
                        } else if (newLinkMin == oldLinkMin) {
                            if (getMax(target.to,link->value.toId) > getMax(target.currentMin.from,target.currentMin.to)) {
                                updateLink = true;
                            }
                        }
                    }

                    SearchTarget target2;
                    target2.to = link->value.toId;
                    if (updateLink) {
                        target2.currentMin.to = link->value.toId;
                        target2.currentMin.linkThroughput = link->value.linkThroughput;
                        target2.currentMin.from = target.to;
                    } else {
                        target2.currentMin = target.currentMin;
                    }

                    if (target2.to == to) {
                        return target2.currentMin;
                    } else {
                        targets.push_back(target2);
                    }
                }
            }
        }

        currentMin.to = -1;
        return  currentMin;
    }

    int searchId = 0;

    Node* nodes;
};

SIE s;
int main() {
    judge::run(&s);
    return 0;
}

