#include "judge.h"

class WAR : public iWAR {
public:
  virtual void init(int workshopsNum, int maxParticipants) {}
  virtual int registration(int byteid, char level[], int preferences[]) { return 0; }
  virtual int unregistration(int byteid) { return 0; }
};

int main() {
  WAR w;
  judge::run(&w);
}
