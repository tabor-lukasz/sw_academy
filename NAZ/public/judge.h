#pragma warning(disable : 4996)

class INaz {
public:
	virtual void init(int maxSize) = 0;
	virtual void addCitizen(char *name, char *surname, char *pesel) = 0;
	virtual void delCitizen(char *pesel) = 0;
	virtual void getNameByPesel(char *pesel, /*OUT*/ char *name) = 0;
	virtual void getSurnameByPesel(char *pesel, /*OUT*/ char *surname) = 0;
	virtual void getPeselByName(char *name, /*OUT*/ char *pesel) = 0;
	virtual void getPeselBySurname(char *surname, /*OUT*/ char *pesel) = 0;
};

class Judge
{
public:
	static int memorySize();
	static void memoryRead(int offset, int size, char *buf);
	static void memoryWrite(int offset, int size, char *buf);
	static void run(INaz *solution);
};

