#include "judge.h"
#include <iostream>
using namespace std;

namespace {

int mode;

int population;
int queryCount;
int nextQuery;
char names[32768][16];
char logins[65536][8];
char buf[32];

void init() {
	static bool doInit = true;
	if (doInit == false) return;
	doInit = false;
	cin >> mode;
	cin >> population >> queryCount;
	for (int i=0; i<population; ++i) {
		cin >> buf;
		for (int j=0; j<16; ++j) names[i][j] = buf[j];
	}
	for (int i=0; i<queryCount; ++i) {
		cin >> buf;
		for (int j=0; j<8; ++j) logins[i][j] = buf[j];
	}
} // init()

} // namespace

int Judge::getPopulation() {
	init();
	return population;
}

void Judge::getCitizenName(int id, char *name) {
	init();
	for (int i=0; i<16; ++i)
		name[i] = names[id][i];
}

int Judge::getQueryCount() {
	init();
	return queryCount;
}

void Judge::getCitizenLogin(char *login) {
	init();
	for (int j=0; j<8; ++j)
		login[j] = logins[nextQuery][j];
	++nextQuery;
}

void Judge::replyCitizenName(char *name) {
	init();
	for (int j=0; j<16; ++j)
		buf[j] = name[j];
	buf[16] = 0;
	cout << buf << "\n";
}

