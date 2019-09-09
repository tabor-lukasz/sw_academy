#ifndef LISTLINKED_H
#define LISTLINKED_H

long long compute_hash(const char* str) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (;*str;++str) {
        hash_value = (hash_value + (*str - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

template <typename T>
class List {

public:

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

    void push_front(const T& element) {
        if (!root) {
            last = root = new ListNode<T>(element);
        } else {
            root->prev = new ListNode<T>(element);
            root->prev->next = root;
            root = root->prev;
        }
        ++_size;
    }

    T front() {
        return root->value;
    }

    T back() {
        return last->value;
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

    void pop_back() {
        if (last) {
            auto tmp = last;
            if (last->prev) {
                last->prev->next = nullptr;
            }
            last = last->prev;

            --_size;
            if (_size == 0) {
                root = nullptr;
            }

            delete tmp;
        }
    }

    unsigned size() const {return _size;}

    ListNode<T>* begin() const {
        return root;
    }

    void erase(ListNode<T>* element) {
        if (element == root) {
            pop_front();
            return;
        }

        if (element == last) {
           pop_back();
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
    unsigned _size = 0;
};


#endif // LISTLINKED_H
