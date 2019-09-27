//class IWYB {
//public:
//  virtual int improveNetwork(int N, int *v1, int *v2, int *d) = 0;
//};

//class Judge {
//public:
//  static void run(IWYB *solution);
//};

class IPLE {
public:
  virtual int improveNetwork(int N, int *v1, int *v2, int *d) = 0;
};

class Judge {
public:
  static void run(IPLE *solution);
};
