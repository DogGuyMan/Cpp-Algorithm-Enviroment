#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		int V, E, S, D; scanf("%d %d %d %d", &V, &E, &S, &D);
		int mnPath = 1e9;
		vector<int> G[101];
		bool Visit[101] = {false,};
		for (int i = 1; i <= E; ++i)
		{
			int f, t; scanf("%d %d", &f, &t);
			G[f].push_back(t);
		}
		auto DFS = [&](auto&& Self, int cur, int depth) -> void
		{
			if (cur == D)
			{
				mnPath = min(mnPath, depth);
				return;
			}
			Visit[cur] = true;
			for (const auto& nxt : G[cur])
			{
				if (Visit[nxt]) continue;
				Self(Self, nxt, depth + 1);
			}
			Visit[cur] = false;
		};
		DFS(DFS, S, 0);
		printf("#%d %d\n", tc, mnPath == 1e9 ? -1 : mnPath);
	}
	return 0;
}