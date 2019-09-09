#include "judge.h"
#include <iostream>
#include <set>
#include <utility>
#include <cassert>
using namespace std;

#define REP(I,N) for(int I=0;I<(N);I++)
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SIZE(x) ((int)(x).size())
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
typedef pair<int,int> PII;


const int MAX_WORKSHOPS = 5;
const int MAX_KNOX_ID = 20 * 1000 * 1000;
const int MAX_CALLS = 500 * 1000;

inline int levelInt(char levelStr[])
{
  if (levelStr[0] == 'n') return 0;
  else if (levelStr[0] == 'i') return 1;
  else if (levelStr[0] == 'a') return 2;
  else if (levelStr[0] == 'p') return 3;
  else return 4;
}

int currentEmployee;
int allKnoxes[MAX_CALLS];
char allLevels[MAX_CALLS];
char allPreferences[MAX_CALLS][MAX_WORKSHOPS];
int byteToId[MAX_KNOX_ID + 1];

class Registrations
{
private:
  set<PII> participants[MAX_WORKSHOPS], waiters[MAX_WORKSHOPS];

  inline PII encode(int id)
  {
    return MP((int)allLevels[id] * MAX_KNOX_ID - allKnoxes[id], id);
  }

  int remove(int id)
  {
    int wid = -1;
    PII e = encode(id);
    REP(i, workshopsNum)
    {
      if (participants[i].find(e) != participants[i].end())
      {
        participants[i].erase(e);
        wid = i;
      }
      waiters[i].erase(e);
    }
    return wid;
  }

  void correct(int id)
  {
    PII e = encode(id);
    remove(id);
    REP(i, workshopsNum)
    {
      int wid = allPreferences[id][i];
      if (SIZE(participants[wid]) < maxParticipants || participants[wid].begin()->FI < e.FI)
      {
        participants[wid].insert(e);
        break;
      } else
      {
        waiters[wid].insert(e);
      }
    }
    REP(i, workshopsNum)
    {
      if (SIZE(participants[i]) < maxParticipants && !waiters[i].empty())
        correct(waiters[i].rbegin()->SE);
      else if (SIZE(participants[i]) > maxParticipants)
        correct(participants[i].begin()->SE);
    }
  }

  void wypisz()
  {
    //cerr << "STAN\n";
    REP(i, workshopsNum)
    {
      cerr << "  " << i << ": ";
      set<PII>::iterator it = participants[i].end();
      while (it != participants[i].begin())
      {
        --it;
        cerr << allKnoxes[it->SE] << " ";
      }
      /*cerr << "| ";
      it = waiters[i].end();
      while (it != waiters[i].begin())
      {
        --it;
        cerr << allKnoxes[it->SE] << " ";
      }*/
      cerr << "\n";
    }
  }

public:
  int workshopsNum, maxParticipants;

  int registration(int id)
  {
    int res = -1;
    PII e = encode(id);
    int newId = -1;
    REP(i, workshopsNum)
    {
      int wid = allPreferences[id][i];
      if (SIZE(participants[wid]) < maxParticipants || participants[wid].begin()->FI < e.FI)
      {
        participants[wid].insert(e);
        res = wid;
        if (SIZE(participants[wid]) > maxParticipants)
          newId = participants[wid].begin()->SE;
        break;
      } else
      {
        waiters[wid].insert(e);
      }
    }
    if (newId != -1)
      correct(newId);
    assert(res != -1);
    //wypisz();
    return res;
  }

  int unregistration(int id)
  {
    int wid = remove(id);
    assert(wid != -1);
    if (!waiters[wid].empty()) // potential bug - forgetting about this "if"
      correct(waiters[wid].rbegin()->SE);
    //wypisz();
    return wid;
  }
} R;

class WAR : public iWAR {
public:
  virtual void init(int workshopsNum, int maxParticipants)
  {
    R.workshopsNum = workshopsNum;
    R.maxParticipants = maxParticipants;
    currentEmployee = 0;
  }
  virtual int registration(int byteid, char level[], int preferences[])
  {
    /*cerr << "- `registration(" << byteid << ", \"" << level << "\", [";
    REP(i, R.workshopsNum) cerr << preferences[i] << ", ";
    cerr << "])`\n";*/
    byteToId[byteid] = currentEmployee;
    allKnoxes[currentEmployee] = byteid;
    allLevels[currentEmployee] = (char)levelInt(level);
    REP(i, R.workshopsNum)
      allPreferences[currentEmployee][i] = (char)preferences[i];
    return R.registration(currentEmployee++);
  }
  virtual int unregistration(int byteid)
  {
    //cerr << "- `unregistration(" << byteid << ")`\n";
    return R.unregistration(byteToId[byteid]);
  }
};

int main() {
  WAR w;
  judge::run(&w);
}
