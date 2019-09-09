class ISUD {
public:
	virtual void solve(int board[9][9]) = 0;
};

class Judge
{
public:
	static void run(ISUD *solution);
};

