class igalaxy
{
public:
	virtual void report(char* text) = 0;
	virtual void summary(long long int output[100][100]) = 0;
};

class judge
{
 public:
	static void run(igalaxy* solution);
};
