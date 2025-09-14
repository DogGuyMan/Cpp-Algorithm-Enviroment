#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for( int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

constexpr int INF = 1e9+7;
constexpr int MAX = 1e6+1;
int N;
int DP[MAX] = {0,};
void HandleInput(istream &ins)
{
	ins >> N;
	fill(DP+1, DP+N, INF);
	DP[1] = 0;
	for(int i = 2; i <= N ; i++) {
		DP[i] = DP[i-1]+1;
		if(i%2==0) DP[i] = min(DP[i], DP[i/2] + 1);
		if(i%3==0) DP[i] = min(DP[i], DP[i/3] + 1);
	}
	cout << DP[N] << '\n';
	int idx= N;
	while(idx >= 1) {
		cout << idx << ' ';
		if(DP[idx-1] + 1 == DP[idx]) idx--;
		else if(idx%2 ==0 && DP[idx/2] + 1 == DP[idx])  idx/=2;
		else idx/=3;
	}
}

void HandleQuery(const char *FILE_PATH)
{
	fstream fs(FILE_PATH);
	if (fs.is_open())
	{
		HandleInput(fs);
	}
}

int main(int argc, const char *args[])
{
	if (argc <= 1)
	{
		FASTIO;
		HandleInput(cin);
	}
	else
	{
		HandleQuery(args[1]);
	}
}
