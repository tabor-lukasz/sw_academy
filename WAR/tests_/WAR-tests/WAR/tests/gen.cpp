#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<numeric>
#include<cassert>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;

int seed = 0;
int pseudo_rand()
{
  seed = seed * 134775813 + 1;
  return ((seed & 0x7FFFFFFF) % 1000000007 + 1000000007) % 1000000007;
}

int nr=0;

void test(int a,int b,int c,int d,int e)
{
  ++nr;
  seed=nr;
  int r=pseudo_rand();
  char st[100];
  sprintf(st,"WAR%da.in",nr);
  fprintf(stderr,"Test %s\n",st);
  freopen(st,"w",stdout);
  printf("2 0 %d %d %d %d %d %d \n",r,a,b,c,d,e);
  sprintf(st,"WAR%db.in",nr);
  fprintf(stderr,"Test %s\n",st);
  freopen(st,"w",stdout);
  printf("2 1 %d %d %d %d %d %d \n",r,a,b,c,d,e);
  assert(c+d<=500000);
  assert(1 <= a && a <= 5);
  assert(1 <= b && b <= 100000);
}

void TESTY(int reg,int unreg)
{
  seed=nr;
  REP(i,10)
  {
    int a = pseudo_rand()%5+1;
    int b = pseudo_rand()%100000+1;
    if (a*b > 2*(reg+unreg) || a*b < (reg+unreg)/2) { --i; continue; }
    int e=0;
    if (pseudo_rand()%10==0) e=1;
    test(a,b,reg,unreg,e);
  }
}

int main()
{
  // 1-10
  test(1,1,1,1,0);
  test(1,10,10,5,0);
  test(2,10,30,15,0);
  test(3,10,40,20,0);
  test(4,10,50,25,0);
  test(5,10,70,30,0);
  test(5,10,50,0,0);
  test(5,1,5,0,0);
  test(5,1,5,0,1);
  test(5,1,10,10,1);

  TESTY(100,50);
  TESTY(1000,500);
  TESTY(10000,5000);
  TESTY(50000,10000);
  TESTY(120000,80000);
  TESTY(100000,0);
  TESTY(400000,100000);
  TESTY(250000,250000);

  // 91-100
  test(5,100000,500000,0,0);
  test(5,100000,500000,0,1);
  test(5,100000,500000,0,0);
  test(5,100000,500000,0,1);
  test(5,60000,400000,100000,0);
  test(5,60000,400000,100000,1);
  test(5,100000,400000,100000,0);
  test(5,100000,400000,100000,1);
  test(4,100000,350000,150000,0);
  test(4,100000,350000,150000,1);

  return 0;
}
