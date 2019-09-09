#include "judge.h"
#include <iostream>
using namespace std;

namespace {
	const int N = 7;
	int a[N];
	int b[N];
	int c[N];
}

void Judge::run(IKLO *solution) {
	int tc; cin >> tc;
	for (int t=0; t<tc; ++t) {
		int n; cin >> n;
		for (int i=0; i<n; ++i) {
			cin >> a[i];
			cin >> b[i];
			cin >> c[i];
		}
		int res = solution->maxTowerHeight(n, a, b, c);
		cout << "#" << t << ": " << res << "\n";
	}
}

