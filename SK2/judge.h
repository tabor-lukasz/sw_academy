
class ISK2 {
public:
	virtual void database(int db[100][100][100]) = 0;
	virtual int query(int sample[8][8]) = 0;
};

class Judge
{
public:
	static void run(ISK2 *solution);
};

