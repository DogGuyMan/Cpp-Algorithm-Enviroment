#include <bits/stdc++.h>
using namespace std;

const int V_MAX = 101;
const int INF = 1e9 + 7;

int DP[V_MAX][V_MAX] = { {0,}, };
int N, M;

int HandleInput(istream& ins)
{
	ins >> N >> M;
	for (int i = 0; i <= N; i++)
	{
		fill(DP[i], DP[i] + (N + 1), INF);
		DP[i][i] = 0;
	}
	for (int i = 0; i < M; i++)
	{
		int from, to, w;
		ins >> from >> to >> w;
		DP[from][to] = min(DP[from][to], w);
	}

	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (i == k)
				continue;
			for (int j = 1; j <= N; j++)
			{
				if (i == j)
					continue;

				DP[i][j] = min(DP[i][j], DP[i][k] + DP[k][j]);
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (DP[i][j] == INF)
			{
				cout << 0 << ' ';
				continue;
			}
			cout << DP[i][j] << ' ';
		}
		cout << '\n';
	}
}

void HandleQuery(const char* FILE_PATH){
	fstream fs(FILE_PATH);
	if(fs.is_open())
		HandleInput(fs);
}

int main(int argc, const char *args[])
{
	if (argc <= 1)
	{
		ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
		HandleInput(cin);
	}
	else
	{
		HandleQuery(args[1]);
	}
}
