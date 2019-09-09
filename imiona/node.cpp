#include "node.h"
//#include <iostream>

node::node(int lv) : level(lv), names(nullptr), names_cnt(0)
{
    for (int i = 0; i < 26; ++i) {
        children[i] = nullptr;
    }
}

node::~node()
{
    if (names) {
        delete [] names;
    }
    for (int i = 0; i < 26; ++i) {
        if (children[i])
            delete children[i];
    }
}

void node::add(const char* login, const char* word) {
    if (level == 8) {
        if (names_cnt > 0) {
            int aaa = 0;
            aaa++;
        }

        if (!isUnique(word))
            return;

        const char** tmp = new const char*[++names_cnt];
        for (int i = 0; i < names_cnt - 1; ++i) {
            tmp[i] = names[i];
        }

        tmp[names_cnt-1] = word;

//        std::cout << word << std::endl;
        delete [] names;
        names = tmp;
        int www = 2;
        www++;
    } else  {
        if (children[login[level] - 'a'] == nullptr) {
            children[login[level] - 'a'] = new node(level + 1);
        }
//        std::cout << login[level] << " ";
        children[login[level] - 'a']->add(login,word);
    }
}

void node::check(const char* word,const char ** &dest, int &count) const {
    if (level == 8) {
        dest = names;
        count = names_cnt;
      return;
    }
    children[word[level] - 'a']->check(word,dest,count);
}

bool node::isUnique(const char* word) {
    for (int i = 0; i < names_cnt; ++i) {
        bool same = true;
        for (int j = 0; j < 16; ++j) {
            if (word[j] != names[i][j] ) {
                same = false;
                break;
            }
        }
        if (same)
            return false;
    }
    return true;
}
