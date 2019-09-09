//#include "judge.h"

//enum Operation {
//    PROD,
//    TRADE,
//    PROC,
//    ATT,
//    TAX
//};

//struct Point {
//    int x;
//    int y;
//};

//class galaxy;

//struct Planet {
//    //    Planet() {}

//    void update(long long production) {type = PROD; value = production;}
//    void update(Operation _type, Point _p1, Point _p2) {type = _type; p1 = _p1; p2 = _p2;}

//    long long int getValue(unsigned calcID);

//    static const int GALAXY_SIZE = 100;

//    static Planet universe[GALAXY_SIZE][GALAXY_SIZE];

//private:

//    unsigned lastCalculationID = 0;

//    Operation type = PROD;
//    long long value = 0;
//    Point p1;
//    Point p2;

//    long long int calcTrade();
//    long long int calcProc();
//    long long int calcAtt();
//    long long int calcTax();
//};

//long long int Planet::getValue(unsigned calcId) {
//    if (type == PROD || lastCalculationID == calcId) {
//        return value;
//    }

//    lastCalculationID = calcId;
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

//    return value;
//}

//Planet Planet::universe[GALAXY_SIZE][GALAXY_SIZE];

//long long int Planet::calcTrade() {
//    return universe[p1.x][p1.y].getValue(lastCalculationID) + universe[p2.x][p2.y].getValue(lastCalculationID);
//}

//long long int Planet::calcProc() {
//    return 2*calcTrade();
//}

//long long int Planet::calcAtt() {
//    long long min;
//    if (&universe[p1.x][p1.y] != this) {
//        min = universe[p1.x][p1.y].getValue(lastCalculationID);
//    } else if (&universe[p2.x][p2.y] != this) {
//        min = universe[p2.x][p2.y].getValue(lastCalculationID);
//    } else {
//        return 0;
//    }

//    for (int i = p1.x; i <= p2.x; ++i) {
//        for (int j = p1.y; j <= p2.y; ++j) {
//            if (&universe[i][j] != this) {
//                if (min > universe[i][j].getValue(lastCalculationID)) {
//                    min = universe[i][j].getValue(lastCalculationID);
//                }
//            }
//        }
//    }

//    return min;
//}

//long long int Planet::calcTax() {
//    long long max;
//    if (&universe[p1.x][p1.y] != this) {
//        max = universe[p1.x][p1.y].getValue(lastCalculationID);
//    } else if (&universe[p2.x][p2.y] != this) {
//        max = universe[p2.x][p2.y].getValue(lastCalculationID);
//    } else {
//        return 0;
//    }

//    for (int i = p1.x; i <= p2.x; ++i) {
//        for (int j = p1.y; j <= p2.y; ++j) {
//            if (&universe[i][j] != this) {
//                if (max < universe[i][j].getValue(lastCalculationID)) {
//                    max = universe[i][j].getValue(lastCalculationID);
//                }
//            }
//        }
//    }
//    return max;
//}

//class galaxy : public igalaxy {
//public:
//    void report(char* text);
//    void summary(long long int output[100][100]);
////    void reset();
//private:
//    Planet universe[100][100];
//    unsigned calcId = 0;
//    bool recalc = false;

//    char* parseNumber(char* ss, long long &number);
//    char* parseNumber(char* ss, int &number);
//};

//char* galaxy::parseNumber(char* ss, long long &number){
//    number = 0;
//    while (*ss >= '0' && *ss <= '9') {
//        number *= 10;
//        number += *ss - '0';
//        ++ss;
//    }
//    return ss;
//}

//char* galaxy::parseNumber(char* ss, int &number){
//    number = 0;
//    while (*ss >= '0' && *ss <= '9') {
//        number *= 10;
//        number += *ss - '0';
//        ++ss;
//    }
//    return ss;
//}

////void galaxy::reset() {
////    for (int i = 0; i < Planet::GALAXY_SIZE; ++i) {
////        for (int j = 0; j < Planet::GALAXY_SIZE; ++j) {
////            Planet::universe[i][j].update(0);
////        }
////    }
////}

//void galaxy::report(char* text) {
//    recalc = true;
//    int x, y;
//    text = parseNumber(text+1,x);
//    text = parseNumber(text+1,y);

//    int p1x, p1y, p2x, p2y;
//    int offset;
//    Operation oper;

//    switch (*(text+4)) {
//    case 'o': {
//        long long value;
//        parseNumber(text+12,value);
//        Planet::universe[x][y].update(value);
//        return;
//    }
//    case 'n': {
//        oper = TRADE;
//        offset = 10;
//        break;
//    }
//    case 'z': {
//        oper = PROC;
//        offset = 17;
//        break;
//    }
//    case 'a': {
//        oper = ATT;
//        offset = 9;
//        break;
//    }
//    case 'd': {
//        oper = TAX;
//        offset = 11;
//        break;
//    }
//    }

//    text = parseNumber(text+offset,p1x);
//    text = parseNumber(text+1,p1y);
//    text = parseNumber(text+3,p2x);
//    text = parseNumber(text+1,p2y);
//    Planet::universe[x][y].update(oper,{p1x,p1y},{p2x,p2y});
//}

//void galaxy::summary(long long int output[100][100]) {
//    if (recalc)
//        ++calcId;

//    for (int i = 0; i < Planet::GALAXY_SIZE; ++i) {
//        for (int j = 0; j < Planet::GALAXY_SIZE; ++j) {
//            output[i][j] = Planet::universe[i][j].getValue(calcId);
//        }
//    }
//}

//galaxy solution;
//int main() {
//    judge::run(&solution);
//    return 0;
//}
