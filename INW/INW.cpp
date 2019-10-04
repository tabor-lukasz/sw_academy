#include "judge.h"
#include<iostream>
#include<iomanip>


#include "../sw_academy_utils/rbtree.h"

using namespace std;

int stash[1000*1000];
int stash_size;

int hh,ww;
int tt[1000+1][1000+1];
int parent[1000+1][1000+1];

void printStash();

void printTT() {
    for (int i = 0; i < hh; i++) {
        for (int j = 0; j < ww; j++) {
            cout << setw(3) << tt[i][j] << " ";
        }
        cout << endl;
    }
}

void printParents() {
    for (int i = 0; i < hh; i++) {
        for (int j = 0; j < ww; j++) {
            cout<< setw(3) << parent[i][j] << " ";
        }
        cout << endl;
    }
}

struct Connection {

    Connection(int to, int power) : power(power), to(to) {
        if (power > 0)
            rank = power*1000000 + to;
        else {
            rank = power*1000000 - to;
        }
    }
    int rank;

    inline int getTo() const {
        return to;
    }

    inline int getPower() const {
        return power;
    }


    inline bool operator<(const Connection& other) const {
        return rank < other.rank;
    }

    inline bool operator==(const Connection& other) const {
        return rank == other.rank;
    }

    inline bool operator!=(const Connection& other) const {
        return !(*this == other);
    }
    int power;
    int to;
};

class State {
public:

    static State states[1000*1000];

    State() {}
    void grow(int x,int y) {
        if (x > hh || x < 0 || y < 0 || y > ww )
            return;

        if (tt[x][y] != power){
            if (parent[x][y] != -1){
                //                cout << "(" <<id <<"," << power << ")->(" <<states[parent[x][y]].id <<"," << states[parent[x][y]].power << ")" << endl;
                states[parent[x][y]].neighbours.insert({id,power});
                neighbours.insert({parent[x][y], states[parent[x][y]].power});
            }
            return;
        }

        if (parent[x][y] == id) {
            return;
        }

        parent[x][y] = id;
        area++;
        grow(x+1,y);
        grow(x-1,y);
        grow(x,y+1);
        grow(x,y-1);
    }

    bool consumeOne() {
        return consumeGreater() || consumeLesser();
    }

    bool consumeGreater() {
        auto min = neighbours_greater.getMin();
        if (!min) {
            return false;
        }
        if (min->val.getPower() > (power_max+1)) {
            return false;
        }
        auto id = min->val.getTo();
        //        cout << "consuming: " << id <<endl;
        neighbours_greater.deleteByVal(min->val);
        area += states[id].area;
        if (power_max_upd < states[id].power) {
            power_max_upd = states[id].power;
        }
        consumed.insert(id);
        auto neigh = states[id].neighbours.getRoot();
        while (neigh) {
            if (consumed.search(neigh->val.getTo())->val != neigh->val.getTo()) {
                stash[stash_size] = neigh->val.getTo();
                stash_size++;
                printStash();
            }
            states[id].neighbours.deleteByVal(neigh->val);
            neigh = states[id].neighbours.getRoot();
        }
        return true;
    }

    bool consumeLesser() {
        auto max = neighbours_lesser.getMax();
        if (!max) {
            return false;
        }
        if (max->val.getPower() < (power_min-1)) {
            return false;
        }
        auto id = max->val.getTo();
        //        cout << "consuming: " << id <<endl;
        neighbours_lesser.deleteByVal(max->val);
        area += states[id].area;
        if (power_min_upd > states[id].power) {
            power_min_upd = states[id].power;
        }
        consumed.insert(id);
        auto neigh = states[id].neighbours.getRoot();
        while (neigh) {
            if (consumed.search(neigh->val.getTo())->val != neigh->val.getTo()) {
                stash[stash_size] = neigh->val.getTo();
                stash_size++;
                printStash();
            }
            states[id].neighbours.deleteByVal(neigh->val);
            neigh = states[id].neighbours.getRoot();
        }
        return true;
    }

    void finalize() {
        for (int i = 0; i < stash_size; ++i) {
            if (consumed.search(stash[i])->val != stash[i]) {
                //                cout << "adding " << stash[i] << endl;
                if (states[stash[i]].power < 0)
                    neighbours_lesser.insert({stash[i],states[stash[i]].power});
                else
                    neighbours_greater.insert({stash[i],states[stash[i]].power});
            }
        }
        if (power_max_upd - power_max > 1)
            throw 4;
        if (power_min - power_min_upd > 1)
            throw 6;
        power_max = power_max_upd;
        power_min = power_min_upd;
        stash_size = 0;
        //        cout  << "fin " << area << " " << power_min << " " << power_max << endl;
    }

    static RBTree<Connection> neighbours_greater;
    static RBTree<Connection> neighbours_lesser;
    RBTree<Connection> neighbours;
    RBTree<int> consumed;
    int area = -1;
    int power_max = 0;
    int power_max_upd = 0;
    int power_min = 0;
    int power_min_upd = 0;
    int power;
    int id = -1;

    static int states_count;
};

State State::states[1000*1000];
int State::states_count;
RBTree<Connection> State::neighbours_greater;
RBTree<Connection> State::neighbours_lesser;

void printStash() {
    //    cout << "stash: ";
    //    for (int i = 0; i < stash_size; i++) {
    //        cout<< stash[i] <<" " ;
    //    }
    //    cout << endl;
}

void printStates() {
    for (int i = 0; i < State::states_count; i++) {
        cout << State::states[i].id << " " << State::states[i].power << " " << State::states[i].area << endl;
    }
}

void printAll() {
    //    printTT();
    //    cout << endl;
    //    printParents();
    //    cout << endl;
    //    printStates();
    //    cout << endl;
}

class INW : public IINW {
public:
    void init(int h, int w, int t[1000][1000]) {

        hh = h;
        ww = w;
        moves = 0;
        //simId++;
        stash_size = 0;
        State::states_count = 1;
        while(State::neighbours_greater.getRoot()) {
            State::neighbours_greater.removeRoot();
        }
        while(State::neighbours_lesser.getRoot()) {
            State::neighbours_lesser.removeRoot();
        }

        for(int i = 0; i <= h; i++) {
            for(int j = 0; j <=  w; ++j) {
                tt[i][j] = t[i][j];
                parent[i][j] = -1;
            }
        }

        for(int i = 0; i < 1000*1000; i++) {
            State::states[i] = State();
        }

        printAll();

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (parent[i][j] == -1) {
                    printAll();
                    if (tt[i][j] == 0) {
                        parent[i][j]  = State::states[0].id = 0;
                    } else {
                        parent[i][j]  = State::states[State::states_count].id = State::states_count;
                        State::states_count++;
                    }
                    State::states[parent[i][j]].area = 1;
                    State::states[parent[i][j]].power = tt[i][j];
                    State::states[parent[i][j]].grow(i+1,j);
                    State::states[parent[i][j]].grow(i-1,j);
                    State::states[parent[i][j]].grow(i,j+1);
                    State::states[parent[i][j]].grow(i,j-1);
                    printAll();
                }
            }
        }
        State::states[0].consumed.insert(0);
        while (State::states[0].neighbours.getRoot()) {
            auto connection = State::states[0].neighbours.getRoot()->val;
            if (connection.getPower() > 0) {
                State::neighbours_greater.insert(connection);
            } else {
                State::neighbours_lesser.insert(connection);
            }
            State::states[0].neighbours.removeRoot();
        }
        bool change = true;
        while (change) {
            change = false;
            while(State::states[0].consumeOne()) {
                change = true;
            }
            if (change) {
                State::states[0].finalize();
                moves++;
            }
        }
    }
    int getInvasionDuration() {
        return moves;
    }
    int getFinalArea() {
        return State::states[0].area;
    }

    int simId = 0;
    int moves;
    //    int area;
};

bool about_to_change[1000][1000];
int (*ttt)[1000];

class Brute : public IINW {
public:
    void init(int h, int w, int t[1000][1000]) {
        max = 0;
        min = 0;
        area = 0;
        moves = 0;
        ttt = t;
        this->ww = w;
        this->hh = h;

        for (int i = 0; i < hh; i++) {
            for (int j = 0; j < ww; j++) {
                about_to_change[i][j] = false;
            }
        }

        for (int i = 0; i < hh; i++) {
            for (int j = 0; j < ww; j++) {
                if( t[i][j] == 0) {
                    area++;
                }
            }
        }

        print();

        bool any_change = true;
        while (any_change) {
            any_change = markToChange();
            bool has_grown = true;
            while (has_grown) {
                has_grown = extendMarks();
                any_change |= has_grown;
            }

            if (any_change) {
                for (int i = 0; i < hh; i++) {
                    for (int j = 0; j < ww; j++) {
                        if(about_to_change[i][j]) {
                            if (t[i][j] > max) {
//                                if (t[i][j] - max > 1) {
//                                    throw 4;
//                                }
                                max = t[i][j];
                            } else if (t[i][j] < min) {
//                                if (min - t[i][j] > 1) {
//                                    throw 5;
//                                }
                                min = t[i][j];
                            }
                            t[i][j] = 0;
                            area++;
                            about_to_change[i][j] = false;
                        }
                    }
                }
                print();
            }

            if (any_change || has_grown) {
                moves++;
            }
        }
        print();
    }

    int getInvasionDuration() {
        return moves;
    }
    int getFinalArea() {
        return area;
    }

    bool extendMarks() {
        bool marked = false;
        for (int i = 0; i < hh; i++) {
            for (int j = 0; j < ww; j++) {
                if (about_to_change[i][j] == true && ttt[i][j]) {
                    marked |= tryToExtend(i-1,j,ttt[i][j]);
                    marked |= tryToExtend(i+1,j,ttt[i][j]);
                    marked |= tryToExtend(i,j-1,ttt[i][j]);
                    marked |= tryToExtend(i,j+1,ttt[i][j]);
                }
            }
        }
        return marked;
    }

    bool tryToExtend(int x, int y,int source_power) {
        if (x >= 0 && x < hh && y >= 0 && y < ww && ttt[x][y] == source_power && !about_to_change[x][y]) {
            about_to_change[x][y] = true;
            print();
            return true;
        }
        return false;
    }

    bool markToChange() {
        bool marked = false;
        for (int i = 0; i < hh; i++) {
            for (int j = 0; j < ww; j++) {
                if (ttt[i][j] == 0) {
                    marked |= tryToMark(i-1,j);
                    marked |= tryToMark(i+1,j);
                    marked |= tryToMark(i,j-1);
                    marked |= tryToMark(i,j+1);
                }
            }
        }
        return marked;
    }

    bool tryToMark(int x, int y) {
        if (x >= 0 && x < hh && y >= 0 && y < ww && ttt[x][y] && !about_to_change[x][y] && ttt[x][y] <= (max +1) && ttt[x][y] >= (min - 1) ) {
            about_to_change[x][y] = true;
            print();
            return true;
        }
        return false;
    }

    void print() {
        //        for (int i = 0; i < h; i++) {
        //            for (int j = 0; j < w; j++) {
        //                cout << setw(3) << ttt[i][j] << " ";
        //            }
        //            cout << endl;
        //        }
        //        cout << endl;
        //        for (int i = 0; i < h; i++) {
        //            for (int j = 0; j < w; j++) {
        //                cout << setw(3) << about_to_change[i][j] << " ";
        //            }
        //            cout << endl;
        //        }
        //        cout << area << " " << min << " " << max << endl;
    }
    int moves;
    int area;
    int ww;
    int hh;
    int min;
    int max;
};

INW solution;
int main() {
    Judge::run(&solution);
    return 0;
}

