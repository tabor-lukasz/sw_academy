class IBFC {
public:
	virtual double minFiberCableLength(int n, int *x, int *y, int minDist, int rangeDist) = 0;
};

class Judge
{
public:
	static void run(IBFC *solution);
};

