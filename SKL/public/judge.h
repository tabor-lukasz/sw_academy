#pragma warning(disable : 4996)

const int MOVE_LIMIT = 2000;

class ISkleroza {
public:
	virtual int solve(char board[6][6], char pattern[4][4], char moves[MOVE_LIMIT]) = 0;
};


class Judge
{
public:
	static void run(ISkleroza *solution);    

    static int tcc;
    static int seeed;

};

