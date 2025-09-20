```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int N;
int W[16][16];
int mincost[1<<15][15] {};//leftcity, start
const int MAX = 987654321;

int tsp(int leftcity, int startcity)
{
  if(mincost[leftcity][startcity]!=0)
    return mincost[leftcity][startcity];
  if(leftcity == 0){
    if(W[startcity][N-1]){
      mincost[leftcity][startcity] = W[startcity][N-1];
      return mincost[leftcity][startcity];    
    }
    else{
      mincost[leftcity][startcity] = MAX;
      return MAX;
    }
  }
  int ans = MAX;
  for(int next=0; next<N-1; next++){
    if(leftcity&(1<<next) && W[startcity][next]!=0)
      ans = min(ans, W[startcity][next] + tsp(leftcity^(1<<next), next));
      
  }
  mincost[leftcity][startcity] = ans;
  return ans;
}

int main()
{
  cin >> N;
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      cin >> W[i][j];
  int leftcity = (1<<(N-1))-1;
  cout << tsp(leftcity, N-1);
}
```