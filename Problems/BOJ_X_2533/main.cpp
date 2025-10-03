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

int N;
vector<vector<int>> G;
vector<pii> DP;

ostream& operator<<(ostream& os, pii pr) {
	os << pr.Y << ' ' << pr.X;
	return os;
}

void DFS(int cur, int par) {
	DP[cur].Y = 1;
	DP[cur].X = 0;
	for(auto& e : G[cur]) {
		if(e == par) continue;
		DFS(e, cur);
	}
	for(auto& e : G[cur]) {
		if(e == par) continue;
		DP[cur].X += DP[e].Y;
		DP[cur].Y += min(DP[e].Y, DP[e].X);
	}
}

void HandleInput(istream &ins)
{
	ins >> N;
	G.assign(N+1, {});
	DP.assign(N+1, {0, 0});
	for(int i = 1; i < N; ++i) {
		int u, v; ins >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	DFS(1, 0);
	cout << min(DP[1].Y, DP[1].X) << '\n';
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
