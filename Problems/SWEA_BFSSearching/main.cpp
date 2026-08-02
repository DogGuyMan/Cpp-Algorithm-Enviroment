#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define Y first
#define X second
typedef pair<int, int> pii;

struct Node
{
	pii pos = {0, 0};
	int depth = 0;
};

static int G[55][55];
static int Visit[55][55];
pii MV[4]
{
	{ 1,  0},
	{ 0,  1},
	{-1,  0},
	{ 0, -1}
};

inline bool IsBound(pii& pos, int R, int C)
{
	return 1 <= pos.Y && 1 <= pos.X && pos.Y <= R && pos.X <= C;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int TC, R, C;
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; ++tc)
	{
		scanf("%d %d", &R, &C);
		memset(G, 0, sizeof(G));
		memset(Visit, 0, sizeof(Visit));
		for (int i = 1 ; i <= R; ++i)
		{
			for (int j = 1 ; j <= C; ++j)
			{
				scanf("%d", &G[i][j]);
			}
		}
		queue<Node> q;
		q.push({{1, 1}, 0});
		while (!q.empty())
		{
			auto cur = q.front(); q.pop();
			Visit[cur.pos.Y][cur.pos.X] = cur.depth;
			for (int mv = 0; mv < 4; ++mv)
			{
				pii nxt =
				{
					cur.pos.Y + MV[mv].Y,
					cur.pos.X + MV[mv].X
				};
				if (!IsBound(nxt, R, C)) continue;
				if (G[nxt.Y][nxt.X] == 0) continue;
				if (Visit[nxt.Y][nxt.X] > 0) continue;
				q.push({nxt, cur.depth + 1});
			}
		}
		printf("#%d %d\n", tc, Visit[R][C]);
	}
}