#include "judge.h"
#include <iostream>
using namespace std;


int Judge::tcc;
int Judge::seeed;

namespace {
	long long seed;
	int pseudo_rand() {
		seed = seed * 13477581 + 1;
		return (seed & 0x7FFFFFFF) % 1000000007;
	}

	void randomShuffle(char buf[36], int cnt, int limit) {
		for (int i=0; i<cnt; ++i) {
			int pos = pseudo_rand() % limit;
			char tmp = buf[i];
			buf[i] = buf[pos];
			buf[pos] = tmp;
		}
	}

	void error(int tc, const char *msg) {
		cout << "ERROR occured in test case: " << (tc+1) << "\n";
		cout << "ERROR MSG: " << msg << "\n";
		exit(0);
	}

} // namespace



void Judge::run(ISkleroza *solution) {
    int tc;
//    cin >> tc;
//	cin >> seed;

    tc = tcc;
    seed = seeed;

	// there will be 100 test cases
	// tc value will be from set: {54,58,63,68,73,79,85,91,98,105,113,121,130,140,150,161,173,186,200,215,231,248,266,285,305,327,350,375,402,431,462,495,530,568,608,651,697,746,799,855,915,980,1049,1123,1202,1287,1378,1475,1579,1690,1809,1936,2072,2218,2374,2541,2719,2910,3114,3332,3566,3816,4084,4370,4676,5004,5355,5730,6132,6562,7022,7514,8040,8603,9206,9851,10541,11279,12069,12914,13819,14787,15823,16931,18117,19386,20744,22197,23751,25414,27193,29097,31134,33314,35647,38143,40814,43671,46728,49999}

	char board[6][6];
	char pattern[4][4];
	char orgBoard[6][6];
	char orgPattern[4][4];
	char result[MOVE_LIMIT];

	const char *letters = "AAAAABBBBBCCCCCDDDDDEEEEEFFFFFGGGGG.";

	for (int nr=0; nr<tc; ++nr) {        
		int x = 5;
		int y = 5;
		char buf[36];
		for (int i=0; i<36; ++i)
			buf[i] = letters[i];

		randomShuffle(buf, 16, 35);
		int next = -1;
		for (int i=0; i<4; ++i)
			for (int j=0; j<4; ++j)
				orgPattern[i][j] = pattern[i][j] = buf[++next];

		randomShuffle(buf, 35, 35);
		next = -1;
		for (int i=0; i<6; ++i)
			for (int j=0; j<6; ++j)
				orgBoard[i][j] = board[i][j] = buf[++next];

        if (nr == 65 && tc ==85) {
            int rr = 3;
            rr++;
        }

		int cnt = solution->solve(board, pattern, result);

		if (cnt < 0 || cnt > MOVE_LIMIT)
			error(nr, "count of moves incorrect!");

		for (int j=0; j<cnt; ++j) {
			int xx=x, yy=y;
			if (result[j] == 'U') { xx = x + 0; yy = y + 1; }
			if (result[j] == 'D') { xx = x + 0; yy = y - 1; }
			if (result[j] == 'L') { xx = x + 1; yy = y + 0; }
			if (result[j] == 'R') { xx = x - 1; yy = y + 0; }
			if (xx < 0 || xx >= 6 || yy < 0 || yy >= 6)
                error(tc*100000 + nr, "move outside the board!");
			orgBoard[y][x] = orgBoard[yy][xx];
			orgBoard[yy][xx] = '.';
			x = xx; y = yy;
		}

		for (int i=0; i<4; ++i) for (int j=0; j<4; ++j)
			if (orgBoard[1+i][1+j] != orgPattern[i][j])
				error(nr, "pattern doesn't match!");
	}
    cout << "SOLUTION CORRECT! MAGIC: " << pseudo_rand() << '\n';
}

