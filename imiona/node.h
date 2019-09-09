#ifndef NODE_H
#define NODE_H


class node
{
public:
    node(int lv);
    ~node();
    void add(const char* login, const char* word);

    void check(const char* word,const char ** &dest, int &count) const;

private:

    bool isUnique(const char* word);

    int level;
    node* children[26];
    const char** names;
    int names_cnt;
};

#endif // NODE_H
