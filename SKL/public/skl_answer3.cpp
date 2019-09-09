#include "judge.h"

static bool forbidden[6][6];
static char board[6][6];
static char pattern[4][4];

inline bool isForbidden(int y, int x) {
    return y < 0 || x < 0 || y > 5 || x > 5 || forbidden[y][x];
}

struct moves {
    char* res;
    int current = 0;
};

static moves answer;

struct Point {
    Point(int yy, int xx) : x(xx), y(yy) {}

    int x;
    int y;

    inline bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    inline bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    inline bool borders(const Point& other) const {
        return  (x == other.x && (y - other.y == 1 || y - other.y == -1)) ||
                (y == other.y && (x - other.x == 1 || x - other.x == -1));
    }
};

inline int distance(const Point p1, const Point p2) {
    return ((p1.x - p2.x) > 0 ? (p1.x - p2.x) : (p2.x - p1.x)) + ((p1.y - p2.y) > 0 ? (p1.y - p2.y) : (p2.y - p1.y));
}

Point findNearest(const Point& from, char cc) {
    Point nearest{20,20};
    int min = 100;
    for (int i =5; i >= 0; --i) {
        for (int j = 5; j >= 0; --j) {
            if (board[i][j] == cc && !forbidden[i][j] && distance(from,Point(i,j)) < min ) {
                nearest = Point(i,j);
                min = distance(nearest,from);
            }
        }
    }
    return nearest;
}

inline void slideDot(Point& src, Point& dest) {
    if (src.x > dest.x) {
        answer.res[answer.current++] = 'R';
    } else if (src.x < dest.x) {
        answer.res[answer.current++] = 'L';
    } else if (src.y < dest.y) {
        answer.res[answer.current++] = 'U';
    } else {
        answer.res[answer.current++] = 'D';
    }

    const char tmp = board[src.y][src.x];
    board[src.y][src.x] = board[dest.y][dest.x];
    board[dest.y][dest.x] = tmp;

    const auto tmp2 = src;
    src = dest;
    dest = tmp2;
}

inline void slideDot(Point& src,Point&& dest) {
    Point tmp = dest;
    slideDot(src,tmp);
}

void moveDot(Point& src,const Point& dest) {
    while (src != dest) {
        const int xDir = src.x < dest.x ? 1 : -1;
        const int yDir = src.y < dest.y ? 1 : -1;

        if (src.x != dest.x && !isForbidden(src.y,src.x + xDir)) {
            slideDot(src,Point(src.y,src.x + xDir));
            continue;
        }
        if (src.y != dest.y && !isForbidden(src.y + yDir,src.x)) {
            slideDot(src,Point(src.y + yDir,src.x));
            continue;
        }
        const int sides[2] = {1,-1};
        bool moved = false;
        if (src.x != dest.x) {
            for ( auto side : sides)
                if (!isForbidden(src.y + side,src.x) &&
                        !isForbidden(src.y + side,src.x + xDir) &&
                        !isForbidden(src.y + side,src.x +2*xDir) &&
                        !isForbidden(src.y,src.x + 2*xDir))
                {
                    slideDot(src,Point(src.y + side,src.x));
                    slideDot(src,Point(src.y,src.x + xDir));
                    slideDot(src,Point(src.y,src.x + xDir));
                    slideDot(src,Point(src.y - side,src.x));
                    moved = true;
                    break;
                }
        }
        if (moved)
            continue;

        if (src.y != dest.y) {
            for ( auto side : sides)
            if (    !isForbidden(src.y,src.x + side) &&
                    !isForbidden(src.y + yDir,src.x + side) &&
                    !isForbidden(src.y + 2*yDir,src.x + side) &&
                    !isForbidden(src.y + 2*yDir,src.x))
            {
                slideDot(src,Point(src.y,src.x + side));
                slideDot(src,Point(src.y + yDir,src.x));
                slideDot(src,Point(src.y + yDir,src.x));
                slideDot(src,Point(src.y,src.x - side));
                moved = true;
                break;
            }
        }
    }
}

bool moveToProximity(Point& dot, Point piece, Point destination) {
    Point dest(0,0);
    bool reorder = false;

    if (piece.y < destination.y) {
        if (!isForbidden(piece.y + 1,piece.x)) {
            dest.x = piece.x;
            dest.y = piece.y + 1;
        }
        reorder = true;
    } else {
        if (piece.x == destination.x) {
            dest.x = piece.x;
            dest.y = piece.y-1;
        } else if (piece.x > destination.x) {
            dest.x = piece.x-1;
            dest.y = piece.y;
        } else {
            if (!isForbidden(piece.y, piece.x+1)) {
                dest.x = piece.x+1;
                dest.y = piece.y;
            } else {
                dest.x = piece.x;
                dest.y = piece.y-1;
            }
        }
    }
    moveDot(dot,dest);
    return reorder;
}

void tansportPiece(Point& dot, Point& piece, Point dest, bool reorder) {
    if (!reorder) {
        if (piece.x != dest.x) {
            while (piece.x != dest.x) {
                int dir = piece.x < dest.x ? 1 : -1;
                if ((dot.x < piece.x && dir == -1) || (dot.x > piece.x && dir == 1)) {
                    slideDot(dot,piece);
                } else {
                    int pass_side = dot.y < 5 ? 1 : -1;
                    slideDot(dot,Point(dot.y + pass_side,dot.x));
                    slideDot(dot,Point(dot.y,dot.x + dir));
                    slideDot(dot,Point(dot.y,dot.x + dir));
                    slideDot(dot,Point(dot.y - pass_side,dot.x));
                }
            }
            if (piece == dest) {
                return;
            }
            if (!isForbidden(dot.y - 1, dot.x)) {
                slideDot(dot,Point(dot.y - 1,dot.x));
                slideDot(dot,Point(dot.y,piece.x));
            } else {
                int dir = piece.x > dot.x ? 1 : -1;
                slideDot(dot,Point(dot.y + 1,dot.x));
                slideDot(dot,Point(dot.y,dot.x + dir));
                slideDot(dot,Point(dot.y,dot.x + dir));
                slideDot(dot,Point(dot.y - 1,dot.x));
                slideDot(dot,Point(dot.y - 1,dot.x));
                slideDot(dot,Point(dot.y,dot.x - dir));
            }
        }
        while (piece.y != dest.y) {
            if (dot.y < piece.y ) {
                slideDot(dot,piece);
            } else {
                int pass_side = dot.x < 5 ? 1 : -1;
                slideDot(dot,Point(dot.y,dot.x + pass_side));
                slideDot(dot,Point(dot.y - 1,dot.x));
                slideDot(dot,Point(dot.y - 1,dot.x));
                slideDot(dot,Point(dot.y,dot.x - pass_side));
            }
        }
    } else {
        while (piece.y != dest.y) {
            if (dot.y > piece.y ) {
                slideDot(dot,piece);
            } else {
                int pass_side = dot.x < 5 ? 1 : -1;
                slideDot(dot,Point(dot.y,dot.x + pass_side));
                slideDot(dot,Point(dot.y + 1,dot.x));
                slideDot(dot,Point(dot.y + 1,dot.x));
                slideDot(dot,Point(dot.y,dot.x - pass_side));
            }
        }
        if (piece == dest) {
            return;
        }
        if (!isForbidden(dot.y, dot.x - 1)) {
            slideDot(dot,Point(dot.y,dot.x - 1));
            slideDot(dot,Point(piece.y,dot.x));
        } else {
            slideDot(dot,Point(dot.y,dot.x + 1));
            slideDot(dot,Point(dot.y + 1,dot.x));
            slideDot(dot,Point(dot.y + 1,dot.x));
            slideDot(dot,Point(dot.y,dot.x - 1));
            slideDot(dot,Point(dot.y,dot.x - 1));
            slideDot(dot,Point(dot.y - 1,dot.x));
        }
        while (piece.x != dest.x) {
            if (dot.x < piece.x ) {
                slideDot(dot,piece);
            } else {
                int pass_side = dot.y < 5 ? 1 : -1;
                slideDot(dot,Point(dot.y + pass_side,dot.x));
                slideDot(dot,Point(dot.y,dot.x - 1));
                slideDot(dot,Point(dot.y,dot.x - 1));
                slideDot(dot,Point(dot.y - pass_side,dot.x));
            }
        }
    }
}


class Skleroza : public ISkleroza {
public:
    int solve(char b[6][6], char p[4][4], char res[MOVE_LIMIT]) {

        answer.res = res;
        answer.current = 0;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                pattern[i][j] = p[i][j];
            }
        }

        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                board[i][j] = b[i][j];
                forbidden[i][j] = false;
            }
        }

        Point dot(5,5);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++ j) {
                if (board[i][j] != pattern[i][j]) {
                    const Point destination(i,j);
                    auto target = findNearest(destination,pattern[i][j]);
                    forbidden[target.y][target.x] = true;
                    auto reorder = moveToProximity(dot,target,destination);
                    forbidden[target.y][target.x] = false;
                    tansportPiece(dot,target,destination,reorder);
                }
                forbidden[i][j] = true;
            }
        }

        moveDot(dot,Point(4,4));

        constexpr int ending_size = 95;
        const char* const ending = "RDLURRDLURRDLURRDLURDLLLLRDLURRDLURRDLURRDLURDLLLLRDLURRDLURRDLURRDLURDLLLLRDLURRDLURRDLURRDLUR";

        for (int i = 0; i < ending_size; ++i) {
            answer.res[answer.current + i] = ending[i];
        }
        answer.current += ending_size;
        return answer.current;
    }
};


Skleroza solution;
int main() {
    // You can initialize Your data structures here

    // But the last instructions should not been modified

    Judge::run(&solution);

    return 0;
}
