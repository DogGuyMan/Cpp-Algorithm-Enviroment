set을 사용하지 않고, 그리고, 상태마다 backtrack을 저장하지 않는 방법

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

const int MN = 1e4 + 1;

vector<int> E[MN];
vector<int> picked;

int dp[MN][2];
int W[MN];
int n, a,b, ret;

void dfs(int n, int prev)
{
	for(int nxt : E[n]) if(nxt != prev){
		dfs(nxt,n);
		dp[n][0] += max(dp[nxt][0], dp[nxt][1]);
		dp[n][1] += dp[nxt][0];
	}
	dp[n][1]+=W[n];
}
void track(int n, int prev, int select)
{
	if(select) picked.push_back(n);
	for(int nxt : E[n]) if(nxt != prev){
		if(select) track(nxt, n, 0);
		else track(nxt, n, dp[nxt][1] > dp[nxt][0]);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i<=n; i++)
		scanf("%d", &W[i]);
	for(int i=0; i<n-1; i++){
		scanf("%d %d", &a, &b);
		E[a].push_back(b); E[b].push_back(a);
	}
	dfs(1,-1);
	int select = dp[1][0] < dp[1][1];
	track(1,-1,select);
	sort(picked.begin(), picked.end());
	printf("%d\n", max(dp[1][0], dp[1][1]));
	for(auto it : picked)
		printf("%d ", it);	
	return 0;
}
```