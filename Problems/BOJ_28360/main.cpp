#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int V_MAX = 55;
int N, M, IN_DEG[V_MAX];
double D[V_MAX];
vector<int> G[V_MAX];

// q.push(1)만 하면 안됨 
// 1이 아닌 in-degree = 0 이 있을 수 있음


void HandleInput(istream &ins)
{
	ins >> N >> M; D[1] = 100;
	for(int i = 1; i <= M; i++) {
		int s, e; ins >> s >> e;
		G[s].push_back(e);
		IN_DEG[e]++;
	}
	queue<int> q;
	for(int i = 1; i <= N; i++) { if(!IN_DEG[i]) q.push(i); }
	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		for(auto& nxt : G[cur]) {
			D[nxt] += (D[cur] / G[cur].size());
			if(!--IN_DEG[nxt]) q.push(nxt);
		}
		if(!G[cur].empty()) {D[cur] = 0;}
	}
	cout << fixed << setprecision(20) << *max_element(D+1, D+1+N);
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

