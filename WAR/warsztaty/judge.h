class iWAR {
public:
  virtual void init(int workshopsNum, int maxParticipants) = 0;
  virtual int registration(int byteid, char level[], int preferences[]) = 0;
  virtual int unregistration(int byteid) = 0;
};

class judge {
public:
  static long run(iWAR *);
};
