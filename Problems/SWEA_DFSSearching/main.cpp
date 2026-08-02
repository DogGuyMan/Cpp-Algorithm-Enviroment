#include <cstdio>
#include <vector>
using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1) freopen(argv[1], "r", stdin);

	int TC; scanf("%d", &TC);
	int M, N, S, E;

	for (int tc = 1; tc <= TC; ++tc)
	{
		scanf("%d %d %d %d", &M, &N, &S, &E);
		vector<vector<int>> G(M + 1, vector<int>());
		vector<int> IsVisit(M + 1, 0);
		int ans = 1e9;
		for (int e = 0; e < N; ++e)
		{
			int f, t; scanf("%d %d", &f, &t);
			G[f].push_back(t);
		}

		auto DFS = [&](auto&& Self, int cur, int depth) -> void
		{
			if (cur == E)
			{
				ans = min(depth, ans);
				return;
			}
			IsVisit[cur] = 1;
			for (auto nxt : G[cur])
			{
				if (IsVisit[nxt]) continue;
				Self(Self, nxt, depth + 1);
			}
			IsVisit[cur] = 0;
		};
		DFS(DFS, S, 0);
		printf("%d %d\n", tc, ans == 1e9 ? -1 : ans);
	}
}