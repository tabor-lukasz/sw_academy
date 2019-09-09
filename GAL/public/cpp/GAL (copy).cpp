#include "judge.h"

#include <set>
#include <iostream>
#include <iomanip>
using namespace std;

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

    bool operator<(const Point& other) const {
        bool rval = false;
        if (x < other.x)
            rval = true;
        else if (x == other.x && y < other.y)
                    rval = true;

        return rval;
    }

    bool operator==(const Point& other) {
        return x == other.x && y == other.y;
    }
};

class galaxy;

struct Planet {
    //    Planet() {}

    void update(long long production);
    void update(Operation _type, Point _p1, Point _p2);

    long long int getValue();

    static const int GALAXY_SIZE = 100;

    static Planet universe[GALAXY_SIZE][GALAXY_SIZE];

    void subscribe(Point planet) {subscribers.insert(planet);
//                                    if (_x == 0 && _y == 3) {
//                                        cout << "subscribe " << _x << " " << _y << subscribers.size() <<  endl;
//                                        for (auto p : subscribers) {
//                                            cout << p.x << p.y << " ";
//                                        }
//                                                    cout << endl;
//                                    }
                                 }
    void unsubscribe(Point planet) {subscribers.erase(planet);
//                                    if (_x == 0 && _y == 3) {
//                                        cout << "unsubscribe " << _x << " " << _y << subscribers.size() <<  endl;
//                                        for (auto p : subscribers) {
//                                            cout << p.x << p.y << " ";
//                                        }
//                                        cout << endl;
//                                    }
                                   }

    void onValueChanged(Point planet, long long value);

    void check() {
        if (value != 0) {
            cout << "val ";
        }
        if (!subscribers.empty()) {
            throw "subs ";
        }
        if (type != PROD) {
            cout << "subs ";
        }
    }


    int _x;
    int _y;

private:

    void notifyChange();

    bool updateValue(Point planet, long long notifyValue);

    set<Point> subscribers;

    Operation type = PROD;
    long long value = 0;
    Point p1;
    Point p2;
    Point currentTarget;

    long long int calcTrade();
    long long int calcProc();
    long long int calcAtt();
    long long int calcTax();
};

void Planet::update(long long production) {
    switch (type) {
    case TRADE:
    case PROC: {
        universe[p1.x][p1.y].unsubscribe({_x,_y});
        universe[p2.x][p2.y].unsubscribe({_x,_y});
        break;
    }
    case TAX:
    case ATT: {
        for (int i = p1.x; i <= p2.x; ++i) {
            for (int j = p1.y; j <= p2.y; ++j) {
                if (&universe[i][j] != this) {
                    universe[i][j].unsubscribe({_x,_y});
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

//    if (_x == 0 && _y == 3)
//        cout << "subscribe " << _x << " " << _y << subscribers.size() <<  endl;
}

void Planet::update(Operation _type, Point _p1, Point _p2) {

    switch (type) {
    case TRADE:
    case PROC: {
        universe[p1.x][p1.y].unsubscribe({_x,_y});
        universe[p2.x][p2.y].unsubscribe({_x,_y});
        break;
    }
    case TAX:
    case ATT: {
        for (int i = p1.x; i <= p2.x; ++i) {
            for (int j = p1.y; j <= p2.y; ++j) {
                if (&universe[i][j] != this) {
                    universe[i][j].unsubscribe({_x,_y});
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
        universe[p1.x][p1.y].subscribe({_x,_y});
        universe[p2.x][p2.y].subscribe({_x,_y});
        break;
    }
    case TAX:
    case ATT: {
        for (int i = p1.x; i <= p2.x; ++i) {
            for (int j = p1.y; j <= p2.y; ++j) {
                if (&universe[i][j] != this) {
                    universe[i][j].subscribe({_x,_y});
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

//    if (_x == 0 && _y == 3)
//        cout << "subscribe " << _x << " " << _y << subscribers.size() <<  endl;
}

long long int Planet::getValue() {
//    if (type == PROD) {
//        return value;
//    }

//    switch (type) {
//    case TRADE: {
//        value = calcTrade();
//        break;
//    }
//    case PROC: {
//        value = calcProc();
//        break;
//    }
//    case ATT: {
//        value = calcAtt();
//        break;
//    }
//    case TAX: {
//        value = calcTax();
//        break;
//    }
//    }

    return value;
}

void Planet::notifyChange() {
    for (auto planet : subscribers) {
        //if (planet->_x == 6 && planet->_y == 7 || _x == 0 && _y == 3)
          //  cout << "notifyChange()" << planet->_x << " " << planet->_y << endl;
        Planet::universe[planet.x][planet.y].onValueChanged({_x,_y},value);
    }

//    if (_x == 0 && _y == 3)
//        cout << "subscribe " << _x << " " << _y << subscribers.size() <<  endl;
}

void Planet::onValueChanged(Point planet, long long notifyValue) {
    auto old_val = value;
    updateValue(planet,notifyValue);
    if (old_val != value) {
        notifyChange();
    }

//    if (_x == 0 && _y == 3)
//        cout << "subscribe " << _x << " " << _y << subscribers.size() <<  endl;
}

bool Planet::updateValue(Point planet, long long notifyValue) {
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

//    if (_x == 0 && _y == 3)
//        cout << "subscribe " << _x << " " << _y << subscribers.size() <<  endl;
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
        currentTarget = p1;
    } else if (&universe[p2.x][p2.y] != this) {
        min = universe[p2.x][p2.y].getValue();
        currentTarget = p2;
    } else {
        throw "calcAtt";
    }

    for (int i = p1.x; i <= p2.x; ++i) {
        for (int j = p1.y; j <= p2.y; ++j) {
            if (&universe[i][j] != this) {
                if (min > universe[i][j].getValue()) {
                    min = universe[i][j].getValue();
                    currentTarget = Point{i,j};
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
        currentTarget = p1;
    } else if (&universe[p2.x][p2.y] != this) {
        max = universe[p2.x][p2.y].getValue();
        currentTarget = p2;
    } else {
        throw "calcTax";
    }

    for (int i = p1.x; i <= p2.x; ++i) {
        for (int j = p1.y; j <= p2.y; ++j) {
            if (&universe[i][j] != this) {
                if (max < universe[i][j].getValue()) {
                    max = universe[i][j].getValue();
                    currentTarget =Point{i,j};
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
    //    void reset();
    void check() {
        for (int i = 0; i < 100 ; ++i) {
            for (int j = 0; j < 100; ++j) {
                Planet::universe[i][j].check();
            }
        }
    }
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

    if (Planet::universe[1][1]._x != 1) {
        for (int i = 0; i < Planet::GALAXY_SIZE; ++i) {
            for (int j = 0; j < Planet::GALAXY_SIZE; ++j) {
                Planet::universe[i][j]._x = i;
                Planet::universe[i][j]._y = j;
            }
        }
    }

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
//        for (int i = 0; i < 10; ++i) {
//            for (int j = 0; j < 10; ++j) {
//                cout <<setw(3) << Planet::universe[i][j].getValue() % 1000 << " ";
//            }
//            cout << endl;
//        }
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

//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            cout <<setw(3) << Planet::universe[i][j].getValue() % 1000 << " ";
//        }
//        cout << endl;
//    }
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
