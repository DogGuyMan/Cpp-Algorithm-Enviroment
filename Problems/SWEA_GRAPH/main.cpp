#include <bits/stdc++.h>
using namespace std;
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int MAX_V = 101;

int T;
int V_CNT, E_CNT, Q_CNT;
vector<int> G[MAX_V];

void ResetState()
{
	for (int i = 0; i < MAX_V; i++)
		G[i].clear();
}

void HandleInput(istream &ins)
{
	ins >> T;
	for (int t = 1; t <= T; t++)
	{
		cout << "#" << t << ' ' << t << '\n';
		ins >> V_CNT >> E_CNT >> Q_CNT;
		ResetState();
		for (int i = 0; i < E_CNT; i++)
		{
			int from, to;
			ins >> from >> to;
			G[from].push_back(to);
			G[to].push_back(from);
		}
		for (int i = 0; i < Q_CNT; i++)
		{
			int inputV;
			ins >> inputV;
			for (auto &e : G[inputV])
			{
				cout << e << ' ';
			}
			cout << '\n';
		}
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
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
		HandleInput(cin);
	}
	else
	{
		HandleQuery(args[1]);
	}
}
