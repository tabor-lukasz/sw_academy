#include "judge.h"
#include <iostream>
#include <vector>
using namespace std;

namespace {


string TestPrefix = "res/SMA0";
string TestCases= "abcdefgh";
//string TestCases= "b";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";

long long seed;
int pseudoRand() {
	seed = seed * 13477581 + 1;
	return (seed & 0x7fffffff) % 1000000007;
}

int pancakes[MAX_N];
int pancakesOrg[MAX_N];
int moves[MAX_MOVES];

void randomShuffle(int n) {
	for (; n>1; --n) {
		int pos = pseudoRand() % n;
		int tt = pancakes[pos];
		pancakes[pos] = pancakes[n-1];
		pancakes[n-1] = tt;
	}
}

bool verify(int n, int cnt) {
	for (int i=0; i<cnt; ++i) {
		int a = moves[i];
		int b = n-1;
		if (a < 0 || a >= n) {
			cout << "Error. Move not in range [0, n-1].\n";
			a = n-1;
		}
		while (a < b) {
			int tt = pancakesOrg[a];
			pancakesOrg[a] = pancakesOrg[b];
			pancakesOrg[b] = tt;
			++a;
			--b;
		}
	}
	for (int i=0; i<n; ++i) {
		if (i + pancakesOrg[i] != n) {
			cout << "Error. Pancakes are not sorted!\n";
			return false;
		}
	}
	return true;
}

void changeSeed() {
	// THE FINAL JUDGE WILL BE THE SAME AS THIS ONE...
	// EXCEPT THE BODY OF THIS FUNCTION
}

} // namespace

void Judge::run(ISMA *solution) {
	int mode; cin >> mode;
	int TC; cin >> TC;
	int n; cin >> n;
	cin >> seed;
	changeSeed();

	vector<int> needVerify(TC, 1);

	long long hhash = 0;
	for (int tc=0; tc<TC; ++tc) {
		for (int i=0; i<n; ++i)
			pancakes[i] = i+1;
		randomShuffle(n);
		for (int i=0; i<n; ++i)
			pancakesOrg[i] = pancakes[i];
		int cnt = solution->sortPancakes(n, pancakes, moves);
		if (cnt < 0 || cnt > MAX_MOVES) {
			cout << "Error. Number of moves negative or exceeds the limit.\n";
			needVerify[tc] = 0;
		}
		if (needVerify[tc] != 0)
			hhash = (hhash * 10007 + (verify(n, cnt) ? (tc+1) : 0)) % 1000000007;
	}
	cout << "Final hash: " << hhash << "\n";
}

