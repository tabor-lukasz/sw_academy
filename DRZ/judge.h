const int MAX_INFO_LEN = 256;

class IDRZ {
public:
	virtual int addCitizenInfo(char info[MAX_INFO_LEN]) = 0;
	virtual int delCitizenInfo(char info[MAX_INFO_LEN]) = 0;
	virtual void modifyCitizen(char info[MAX_INFO_LEN], char newInfo[MAX_INFO_LEN]) = 0;
	virtual int familyMemberCount(char info[MAX_INFO_LEN]) = 0;
};

class Judge
{
public:
	static void run(IDRZ *solution);
};

