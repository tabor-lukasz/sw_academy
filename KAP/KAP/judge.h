#pragma warning(disable : 4996)

class IKAP {
 public:
  virtual int maxScore(int n, int data[][5]) = 0;
};

class judge {
 public:
  static void run(IKAP *solution);
};