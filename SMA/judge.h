const int MAX_N = 500;
const int MAX_MOVES = 15 * MAX_N;

class ISMA {
public:
	virtual int sortPancakes(int n, int *pancakes, int *moves) = 0;
};

class Judge
{
public:
	static void run(ISMA *solution);
};

