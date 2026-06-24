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

struct Vert {
	int cur = 0;
	int order = 0;
};
int N, M, R;
vector<vector<int>> G;
vector<Vert> IS_VISIT;


void HandleInput(istream &ins)
{
	ins >> N >> M >> R;
	G.assign(N+1, vector<int>());
	IS_VISIT.assign(N+1, {0, 0});
	for(int i =0; i < M; i++){
		int u, v; ins >> u >> v;
		G[v].push_back(u);
		G[u].push_back(v);
	}
	for(vector<int>& e : G) {
		sort(e.begin(), e.end());
	}
	queue<int> q; q.push(R);
	IS_VISIT[R] = {R, 1};
	int idx = 1;
	while(!q.empty()){
		int poped = q.front(); q.pop();
		for(auto& e : G[poped]) {
			if(IS_VISIT[e].cur !=0) continue;
			IS_VISIT[e] = {e, ++idx};
			q.push(e);
		}
	}

	for(int i = 1; i <= N; i++) {
		cout << IS_VISIT[i].order << '\n';
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
