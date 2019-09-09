class INAD {
public:
	virtual long long getMinimumCost(int n, int k, long long cost[15][8]) = 0;
};

class Judge
{
public:
	static void run(INAD *solution);
};

