class INON {
public:
	static const int COLOR_UNKNOWN = 0;
	static const int COLOR_WHITE = 1;
	static const int COLOR_BLACK = 2;

	virtual INON *createLine(int n, int k, int *data) = 0;
	virtual int getColor(int pos) = 0;
	virtual void setColor(int pos, int color) = 0;
};



class Judge
{
public:
	static void run(INON *solution);
};

