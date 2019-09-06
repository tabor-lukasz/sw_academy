#include "judge.h"

class NON : public INON {
public:
	INON *createLine(int n, int k, int *data) { return 0; }
	int getColor(int) { return INON::COLOR_UNKNOWN; }
	void setColor(int, int) {  }
};

NON factory;
int main() {
	Judge::run(&factory);
	return 0;
}

