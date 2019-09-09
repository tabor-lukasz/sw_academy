#include "judge.h"

//#define VERBOSE

#ifdef VERBOSE
#include <iostream>
using namespace std;
#endif

bool poss[9][9][9];
int (*tab)[9];


#ifdef VERBOSE
void print(int tbl[][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0;j<9;++j) {
            if (tbl[i][j])
                cout << tbl[i][j] << "";
            else {
                cout << " ";
            }
            if (j % 3 == 2)
                cout << "|";
        }
        cout << endl;
        if (i % 3 == 2)
            cout << "------------"<<endl;
    }
}

void printPoss() {
    for (int i = 0; i < 9*3; ++i) {
        for (int j = 0; j < 9*3 ; ++j) {
            if (poss[i/3][j/3][i%3*3 + j%3])
                cout << i%3*3 + j%3 + 1 << "";
            else {
                cout << " ";
            }
            if (j % 9 == 8)
                cout << " # ";
            else if (j % 3 == 2)
                cout << "|";

        }
        cout << endl;
        if (i % 9 == 8)
            cout << "#########################################"<<endl;
        else if (i % 3 == 2) {
            cout << "-----------------------------------------"<<endl;
        }
    }
}
#endif


void excludeLine(int y, int x, int num) {
    for (int i = 0; i < 9; ++i) {
        poss[i][x][num-1] = poss[y][i][num-1] = poss[y][x][i] = false;
    }
}

void excludeSquare(int y, int x, int num) {
    const int xBegin = x/3*3;
    const int yBegin = y/3*3;

    const int xEnd = xBegin + 3;
    const int yEnd = yBegin + 3;

    for (int i = xBegin; i < xEnd; ++i) {
        for (int j = yBegin; j < yEnd; ++j) {
            poss[j][i][num-1] = false;
        }
    }
}

int checkField(int y, int x) {
    int rval = 0;

    for (int i = 0; i < 9; ++i) {
        if (poss[y][x][i]) {
            if (rval)
                return 0;
            else {
                rval = i+1;
            }
        }
    }

    return rval;
}

int checkLineInSquare(int y, int x, bool vertical, int num) {
    const int xBegin = x/3*3;
    const int yBegin = y/3*3;

    const int xEnd = xBegin + 3;
    const int yEnd = yBegin + 3;

    int line = -1;
    for (int i = yBegin; i <yEnd; ++i) {
        for (int j = xBegin; j <xEnd; ++j) {
            if (poss[i][j][num]) {
                if (line == -1) {
                    if (vertical)
                        line = j;
                    else {
                        line = i;
                    }
                } else {
                    if (vertical && line != j)
                        line = -2;

                    if (!vertical && line != i)
                        line = -2;
                }
            }
            if (line == -2)
                break;
        }
        if (line == -2)
            break;
    }

    return line;
}

bool excludeLineOuter(int line, bool vertical, int rootSqare, int num) {
    bool updated = false;
    for (int i = 0; i < 9; ++i) {
        if (i/3 != rootSqare) {
            if (vertical) {
                if (poss[i][line][num-1]) {
                    poss[i][line][num-1] = false;
                    updated = true;
                }
            }else {
                if (poss[line][i][num-1]) {
                    poss[line][i][num-1] = false;
                    updated = true;
                }

            }
        }
    }
    return updated;
}

int checkSquare(int& y, int& x) {
    const int xBegin = x/3*3;
    const int yBegin = y/3*3;

    const int xEnd = xBegin + 3;
    const int yEnd = yBegin + 3;

    for (int k =0; k < 9; ++k) {
        int cnt = 0;
        for (int i = xBegin; i < xEnd; ++i) {
            for (int j = yBegin; j < yEnd; ++j) {
                if (poss[i][j][k]) {
                    y = i;
                    x = j;
                    ++cnt;
                } else if (cnt > 1)
                    break;
            }
            if (cnt > 1)
                break;
        }
        if (cnt == 1) {
            return k+1;
        }
    }
    return 0;
}

bool isAvalible(int y, int x, int num) {
    const int xBegin = x/3*3;
    const int yBegin = y/3*3;
    for (int i = 0; i < 9; ++i) {
        if (tab[y][i] == num || tab[i][x] == num || tab[yBegin + i%3][xBegin + i/3] == num)
            return false;
    }
    return true;
}


int solveBrute(int y, int x) {
    if (y == 9) {
        return true;
    }

    if (!tab[y][x]) {
        for (int i = 0; i < 9; ++i) {
            if (poss[y][x][i] && isAvalible(y,x,i+1)) {
                tab[y][x] = i+1;
#ifdef VERBOSE
                print(tab);
#endif
                if(solveBrute( y + x/8 , (x + 1) % 9 )) {
                    return true;
                }
            }
        }
        tab[y][x] = 0;
        return false;
    } else {
        return solveBrute( y + x/8 , (x + 1) % 9 );
    }
}

class SUD : public ISUD {
public:
    void solve(int t[9][9]) {

        tab = t;
        int cnt = 0;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (t[i][j] == 0) {
                    ++cnt;
                }
            }
        }

        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                for (int k = 0; k < 9; ++k) {
                    poss[i][j][k] = true;
                }

        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j) {
                if (t[i][j]) {
                    excludeLine(i,j,t[i][j]);
                    excludeSquare(i,j,t[i][j]);
                }
            }
#ifdef VERBOSE
        print(t);
        printPoss();
#endif

        while (cnt) {
            bool updated = false;
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    int newNumber = checkField(i,j);
                    if (newNumber) {
                        updated = true;
                        t[i][j] = newNumber;
                        --cnt;
                        excludeLine(i,j,newNumber);
                        excludeSquare(i,j,newNumber);
#ifdef VERBOSE
                        //                        cout << i << " " << j << " " << newNumber << endl;
                        print(t);
                        printPoss();
#endif
                        continue;
                    }
                }
            }

            if (updated)
                continue;

            for (int i = 0; i < 9; i+=3) {
                for (int j = 0; j < 9; j+=3) {
                    int y = i;
                    int x = j;
                    int newNumber = checkSquare(y,x);
                    if (newNumber) {
                        updated = true;
                        t[y][x] = newNumber;
                        --cnt;
                        excludeLine(y,x,newNumber);
                        //                        cout << y << " " << x << " " << newNumber << endl;
#ifdef VERBOSE
                        print(t);
                        printPoss();
#endif
                    }
                }
            }


            if (updated)
                continue;

            for (int i = 0; i < 9; i+=3) {
                for (int j = 0; j < 9; j+=3) {
                    for (int num = 0; num < 9;++num) {
                        int line = checkLineInSquare(i,j,false,num);
                        if (line > 0) {
                            updated = excludeLineOuter(line,false,j/3,num+1);
                            if (updated) {
#ifdef VERBOSE
                                print(t);
                                printPoss();
#endif
                                break;
                            }
                        }
                    }
                    if (updated)
                        break;
                }
                if (updated)
                    break;
            }

            if (updated)
                continue;

            for (int i = 0; i < 9; i+=3) {
                for (int j = 0; j < 9; j+=3) {
                    for (int num = 0; num < 9;++num) {
                        int line = checkLineInSquare(i,j,true,num);
                        if (line > 0) {
                            updated = excludeLineOuter(line,true,i/3,num+1);
                            if (updated) {
#ifdef VERBOSE
                                print(t);
                                printPoss();
#endif
                                break;
                            }
                        }
                    }
                    if (updated)
                        break;
                }
                if (updated)
                    break;
            }

            if (!updated)
                break;
        }

        solveBrute(0,0);

#ifdef VERBOSE
        cout << cnt << endl;
#endif

    }
};

SUD solution;
int main() {
    Judge::run(&solution);
    return 0;
}

