#include "judge.h"
#include <iostream>
using namespace std;

const int MAX_WORKSHOPS = 5;

void judge::run(iWAR *w)
{
  int typ;
  cin >> typ;
  int workshopsNum, maxParticipants, callsNum;
  cin >> workshopsNum >> maxParticipants >> callsNum;
  w->init(workshopsNum, maxParticipants);
  for (int i = 0; i < callsNum; ++i) {
    int op;
    cin >> op;
    if (op == 0) {
      int byteid;
      char level[15];
      int preferences[MAX_WORKSHOPS];
      cin >> byteid >> level;
      for (int j = 0; j < workshopsNum; ++j)
        cin >> preferences[j];
      cout << w->registration(byteid, level, preferences) << "\n";
    } else {
      int byteid;
      cin >> byteid;
      cout << w->unregistration(byteid) << "\n";
    }
  }
}
