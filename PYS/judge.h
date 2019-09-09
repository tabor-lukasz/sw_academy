const int MAX_N = 5000;
const int MAX_MOVES = 15 * MAX_N;

class IPYS {
public:
	virtual int sortPancakes(int n, int *pancakes, int *moves) = 0;
};

class Judge
{
public:
	static void run(IPYS *solution);
};

