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
int N, M;
double D[V_MAX];
vector<int> G[V_MAX];

void HandleInput(istream &ins)
{
	ins >> N >> M; D[1] = 100;
	for(int i = 1; i <= M; i++) {
		int s, e; ins >> s >> e;
		G[s].push_back(e);
	}
	for(int i = 1; i <= N; i++) {
		if(G[i].empty()) continue;
		double nxt = D[i] / G[i].size();
		for(auto& j : G[i]) D[j] += nxt;
		D[i] = 0;
	}
	cout << fixed << setprecision(20) << *max_element(D+1, D+N+1);
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
