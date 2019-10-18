class iKAL
{
  public:
  virtual void insert(char data[], int pos, int len, char buffer[]) = 0;
  virtual void remove(int pos, int len, char buffer[]) = 0;
};

class judge
{
  public:
	static void run(iKAL* solution);
};