#include "judge.h"
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_WORKSHOPS = 5;

const string TestPrefix = "WAR0";
string TestName = "c";
string TestSuffixIn = ".in";
string TestSuffixOut = ".out";


void judge::run(iWAR *w)
{
  ifstream ins(TestPrefix + TestName + TestSuffixIn);
  ifstream outs(TestPrefix + TestName + TestSuffixOut);

  int typ;
  ins >> typ;

  int workshopsNum, maxParticipants, callsNum;
  ins >> workshopsNum >> maxParticipants >> callsNum;
  w->init(workshopsNum, maxParticipants);
  for (int i = 0; i < callsNum; ++i) {
    int result;
    int answer;
    outs >> answer;
    int op;
    ins >> op;
    if (op == 0) {
      int byteid;
      char level[15];
      int preferences[MAX_WORKSHOPS];
      ins >> byteid >> level;
      for (int j = 0; j < workshopsNum; ++j)
        ins >> preferences[j];
      result = w->registration(byteid, level, preferences);
    } else {
      int byteid;
      ins >> byteid;
      result = w->unregistration(byteid);
    }

    if (result != answer) {
        cout << i << ": " << answer << "\t" << result << endl;
    } else {
        cout << i << " OK" << endl;
    }
  }
}
