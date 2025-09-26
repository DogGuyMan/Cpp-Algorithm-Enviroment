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

struct E {
	int cur;
	int w;
};

vector<bool> IS_VISIT;
vector<vector<E>> G;
vector<ll> ROOT_TO_VERT_PATH;

ll ANS = 0;

void DFS(int cur, ll XOR) {
	IS_VISIT[cur] = true;
	for(auto& [nxt, w] : G[cur]) {
		if(IS_VISIT[nxt]) continue;
		ROOT_TO_VERT_PATH[nxt] = XOR ^ w;
		DFS(nxt, XOR ^ w);
	}
}

void HandleInput(istream &ins)
{
	ins >> N;
	G.assign(N + 2, vector<E>());
	IS_VISIT.assign(N + 2, false);
	ROOT_TO_VERT_PATH.assign(N + 2, 0);
	int u, v, w;
	for(int i = 0; i < N-1; i++) {
		ins >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	DFS(1, 0);
	unordered_map<ll, ll> lenPairCnt;
	for(int i = 1; i <= N; i++)  ++lenPairCnt[ROOT_TO_VERT_PATH[i]];
	for(auto& kv : lenPairCnt) {
		ll& llpr = kv.X;
		// 같은애들끼리 조합 llpr_C_2
		ANS += llpr * (llpr-1) / 2;
	}
	cout << ANS << '\n';
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
