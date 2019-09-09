#include "judge.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

namespace
{
  long long seed = 0;
  int pseudo_rand()
  {
    seed = seed * 134775813 + 1;
    return (seed & 0x7FFFFFFF) % 1000000007;
  }

  const int MAX_WORKSHOPS = 5;
  const int MAX_LEVELS = 5;
  const int MAX_KNOX_ID = 20 * 1000 * 1000;
  const int MAX_CALLS = 500 * 1000;

  char levels[5][15] = {"noneligible", "intermediate", "advanced", "professional", "expert"};
} // namespace

void judge::run(iWAR *w)
{	
  int typ;
  cin >> typ;
  if (typ == 1) {
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
        //cout << "  wynik: " << w->registration(byteid, level, preferences) << "\n";
        cout << w->registration(byteid, level, preferences) << "\n";
      } else {
        int byteid;
        cin >> byteid;
        //cout << "  wynik: " << w->unregistration(byteid) << "\n";
        cout << w->unregistration(byteid) << "\n";
      }
    }
  } else if (typ == 2)
  {
    int java, workshopsNum, maxParticipants, regNum, unregNum, callsNum, eqPref, HASH;
    cin >> java >> seed >> workshopsNum >> maxParticipants >> regNum >> unregNum >> eqPref >> HASH;
    w->init(workshopsNum, maxParticipants);
    if (java == 1) { cout << HASH << "\n"; return; } // test dla Javy
    callsNum = regNum + unregNum;
    
    char oper[MAX_CALLS];
    for (int i = 0; i < regNum; ++i) oper[i] = 0;
    for (int i = regNum; i < callsNum; ++i) oper[i] = 1;
    for (int i = 1; i < callsNum; ++i) swap(oper[i], oper[pseudo_rand() % i]);
    for (int i = 1; i < callsNum; ++i) swap(oper[i], oper[pseudo_rand() % i]);

    set<int> byteS;
    vector<int> byteV;
    int hash = 0;
    int realOps = 0;
    int preferences[MAX_WORKSHOPS];
    for (int i = 0; i < workshopsNum; ++i) preferences[i] = i;
    for (int i = 1; i < workshopsNum; ++i) swap(preferences[i], preferences[pseudo_rand() % i]);

    for (int op = 0; op < callsNum; ++op)
    {
      if ((int)oper[op] == 0)
      {
        if ((int)byteV.size() >= workshopsNum * maxParticipants)
        {
          continue;
        }
        int byteid = -1;
        while (1)
        {
          byteid = pseudo_rand() % MAX_KNOX_ID + 1;
          if (byteS.find(byteid) == byteS.end())
          {
            byteS.insert(byteid);
            break;
          }
        }
        byteV.push_back(byteid);
        int level = pseudo_rand() % MAX_LEVELS;
        if (!eqPref)
        {
          for (int i = 1; i < workshopsNum; ++i) swap(preferences[i], preferences[pseudo_rand() % i]);
        }
        int res = w->registration(byteid, levels[level], preferences);
        hash = (hash * 11 + res) % 1000000007;
        ++realOps;
      } else
      {
        if (byteV.empty())
        {
          continue;
        }
        int pos = pseudo_rand() % ((int)byteV.size());
        int byteid = byteV[pos];
        swap(byteV[pos], byteV.back());
        byteV.pop_back();
        int res = w->unregistration(byteid);
        hash = (hash * 11 + res) % 1000000007;
        ++realOps;
      }
    }
    cout << hash << "\n";
    cerr << "num ops: " << realOps << "\n";
  }
}
