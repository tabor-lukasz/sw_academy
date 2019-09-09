class iSIE {
public:
  virtual void addServer(int idNew, int idExisting, int linkThroughput) = 0;
  virtual int directLinks(int id) = 0;
  virtual int connectionThroughput(int id1, int id2) = 0;
  virtual void improveThroughput(int id1, int id2, int newTroughtput) = 0;
};

class judge {
public:
  static void run(iSIE *);
};
