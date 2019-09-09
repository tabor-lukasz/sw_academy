#include "judge.h"
#include <iostream>
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

inline void sswap(int &a,int &b) { int c=a; a=b; b=c; }
class KopiecMin
{
private:
  int t[MAX_CALLS + 1], n;
  int gdzie[MAX_CALLS + 1];
  int value[MAX_CALLS + 1];
  void kswap(int i, int j)
  {
    sswap(t[i], t[j]);
    gdzie[t[i]] = i; gdzie[t[j]] = j;
  }
  void downheap(int i)
  {
    while (1)
    {
      int best = i;
      if (2 * i <= size && value[t[2 * i]] < value[t[best]])
        best = 2 * i;
      if (2 * i + 1 <= size && value[t[2 * i + 1]] < value[t[best]])
        best = 2 * i + 1;
      if (best == i)
        break;
      kswap(i, best);
      i = best;
    }
  }
  void upheap(int i)
  {
    while (i > 1 && value[t[i]] < value[t[i / 2]])
    {
      kswap(i, i / 2);
      i /= 2;
    }
  }
  void dikskey(int x, int v)
  {
    value[v] = x;
    upheap(gdzie[v]);
  }

public:
  int size;
  void init(int nn = 0)
  {
    size = 0;
    n = nn;
    REP(i, n)
      gdzie[i] = -1;
  }
  int getmin()
  {
    return value[t[1]];
  }
  int getminel()
  {
    return t[1];
  }
  void insert(int x, int v)
  {
    ++size;
    t[size] = v;
    value[v] = x; gdzie[v] = size;
    upheap(size);
  }
  void delmin()
  {
    assert(size > 0);
    kswap(1, size);
    gdzie[t[size]] = -1;
    --size;
    downheap(1);
  }
  void remove(int v)
  {
    if (gdzie[v] != -1)
    {
      dikskey(-1000000000, v);
      delmin();
    }
  }
  bool exists(int v)
  {
    return gdzie[v] != -1;
  }
};

int currentEmployee;
int allKnoxes[MAX_CALLS];
char allLevels[MAX_CALLS];
char allPreferences[MAX_CALLS][MAX_WORKSHOPS];
int byteToId[MAX_KNOX_ID + 1];

class Registrations
{
private:
  KopiecMin participants[MAX_WORKSHOPS], waiters[MAX_WORKSHOPS];

  inline int encode(int id)
  {
    return ((int)allLevels[id] + 1) * MAX_KNOX_ID - allKnoxes[id];
  }

  int remove(int id)
  {
    int wid = -1;
    REP(i, workshopsNum)
    {
      if (participants[i].exists(id))
      {
        participants[i].remove(id);
        wid = i;
      }
      waiters[i].remove(id);
    }
    return wid;
  }

  void correct(int id)
  {
    int e = encode(id);
    remove(id);
    REP(i, workshopsNum)
    {
      int wid = allPreferences[id][i];
      if (participants[wid].size < maxParticipants || participants[wid].getmin() < e)
      {
        participants[wid].insert(e, id);
        break;
      } else
      {
        waiters[wid].insert(-e, id);
      }
    }
    REP(i, workshopsNum)
    {
      if (participants[i].size < maxParticipants && waiters[i].size)
        correct(waiters[i].getminel());
      else if (participants[i].size > maxParticipants)
        correct(participants[i].getminel());
    }
  }

  void wypisz()
  {
    REP(i, workshopsNum)
    {
      cerr << "\n";
    }
  }

public:
  int workshopsNum, maxParticipants;

  void init()
  {
    REP(i, workshopsNum)
    {
      participants[i].init(MAX_CALLS);
      waiters[i].init(MAX_CALLS);
    }
  }

  int registration(int id)
  {
    int res = -1;
    int e = encode(id);
    int newId = -1;
    REP(i, workshopsNum)
    {
      int wid = allPreferences[id][i];
      if (participants[wid].size < maxParticipants || participants[wid].getmin() < e)
      {
        participants[wid].insert(e, id);
        res = wid;
        if (participants[wid].size > maxParticipants)
          newId = participants[wid].getminel();
        break;
      } else
      {
        waiters[wid].insert(-e, id);
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
    if (waiters[wid].size) // potential bug - forgetting about this "if"
      correct(waiters[wid].getminel());
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
    R.init();
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
