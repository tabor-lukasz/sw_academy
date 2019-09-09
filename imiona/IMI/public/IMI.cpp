#include "judge.h"

int main() {
	int population = Judge::getPopulation();
	int n = Judge::getQueryCount();

	for (int ___=0; ___<n; ++___) {
		char login[8];
		Judge::getCitizenLogin(login);
		char name[16];
		int id = ___ % population;
		Judge::getCitizenName(id, name);
		Judge::replyCitizenName(name);
	}
	return 0;
}

