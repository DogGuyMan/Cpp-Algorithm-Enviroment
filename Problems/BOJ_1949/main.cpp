#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
struct Vert
{
	int sel = 0;
	int notSel = 0;
};

int A[10101] = { 0, };
vector<int> G[10101];
Vert DP[10101] = { 0, };

void HandlePar(const int &pV, const int &ppV)
{
	Vert &curParent = DP[pV];
	curParent.sel = A[pV];
	curParent.notSel = 0;
	for (auto &c : G[pV])
	{
		if (ppV == c)
			continue;
		curParent.sel += DP[c].notSel;
		curParent.notSel += max(DP[c].notSel, DP[c].sel);
	}
}

inline void HandleLeaf(const int &lV)
{
	DP[lV].sel = A[lV];
	DP[lV].notSel = 0;
}

void DFS(int cur, int prev)
{

	if (G[cur].size() == 1 && G[cur][0] == prev)
	{
		HandleLeaf(cur);
	}
	else
	{
		for (auto &nxt : G[cur])
		{
			if (nxt != prev && DP[nxt].sel <= 0)
				DFS(nxt, cur);
		}
		HandlePar(cur, prev);
	}
}

void HandleInput(istream &ins)
{
	int N;
	ins >> N;
	for (int i = 1; i <= N; ++i)
	{
		ins >> A[i];
	}

	int u, v;
	for (int i = 1; i < N; ++i)
	{
		ins >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	DFS(1, 0);
	cout << max(DP[1].notSel, DP[1].sel) << '\n';
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
