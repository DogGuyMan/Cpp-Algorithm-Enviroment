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

struct State {
	int X, Y;
	unordered_set<int> BACK_TRACK_Y, BACK_TRACK_X;
};

int N;
vector<int> A;
vector<vector<int>> G;
vector<State> DP;

void DFS(int cur, int prev) {
	DP[cur].Y = A[cur]; DP[cur].X = 0; 
	DP[cur].BACK_TRACK_Y.insert(cur);

	for(auto& c : G[cur]) {
		if(c == prev) continue;
		DFS(c, cur);
		int* mxXDP; unordered_set<int> * mxXBack;
		
		if(DP[c].X > DP[c].Y)	{ mxXDP = &DP[c].X; mxXBack = &DP[c].BACK_TRACK_X; }
		else 			{ mxXDP = &DP[c].Y; mxXBack = &DP[c].BACK_TRACK_Y; }
		
		DP[cur].Y += DP[c].X;
		for(auto& bx : DP[c].BACK_TRACK_X)  DP[cur].BACK_TRACK_Y.insert(bx);

		DP[cur].X += *mxXDP;
		for(auto& bx : *mxXBack)  DP[cur].BACK_TRACK_X.insert(bx);
	}
}

void HandleInput(istream &ins)
{
	ins >> N;
	A.assign(N+1, 0);
	G.assign(N+1, {});
	DP.assign(N+1, {-1, -1, {}, {}});
	for(int i = 1; i <= N; i++) {
		ins >> A[i];
	}
	for(int i = 1; i < N; i++) {
		int u, v; ins >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	DFS(1, 0);
	
	int* resDP; unordered_set<int> * resBack;

	if(DP[1].Y > DP[1].X)	{ resDP = &DP[1].Y; resBack = &DP[1].BACK_TRACK_Y; }
	else 			{ resDP = &DP[1].X; resBack = &DP[1].BACK_TRACK_X; }
	
	vector<int> sortedBack(resBack->begin(), resBack->end());
	sort(sortedBack.begin(), sortedBack.end());
	
	cout << *resDP << '\n';
	for(auto& b : sortedBack) { cout << b << ' '; }
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
