#include "judge.h"
#include <vector>
#include <iostream>
#include <list>

using namespace std;

struct Link {
    int to;
    int distance;
};

class Station {
public:
    vector<Link> children;
    int parent = -1;

    vector<Link> candidates;
};


Station stations[2000+1];
int NN;

list<int> queue;


class WYB : public IWYB {

public:
  int improveNetwork(int N, int *v1, int *v2, int *d) {

      NN = N;

      for(int i = 1; i < N+1; i++) {
          stations[i] = Station();
      }

      for (int i = 0 ; i < N; i++) {
         stations[v1[i]].candidates.push_back({v2[i],d[i]});
         stations[v2[i]].candidates.push_back({v1[i],d[i]});
      }


    return 0;
  }
};

WYB solution;
int main() {
  Judge::run(&solution);
  return 0;
}
