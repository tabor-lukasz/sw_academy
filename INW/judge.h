class IINW {
public:
    virtual void init(int h, int w, int map[1000][1000]) = 0;
    virtual int getInvasionDuration() = 0;
    virtual int getFinalArea() = 0;
};

class Judge
{
public:
    static void run(IINW *solution);
};

