#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#define Y first
#define X second
using namespace std;
typedef pair<int, int> pii;

pii& operator+=(pii& lhs, const pii& rhs)
{
	lhs.Y += rhs.Y;
	lhs.X += rhs.X;
	return lhs;
}

pii MV[4] =
{
	{ 0,  1},
	{-1,  0},
	{ 0, -1},
	{ 1,  0}
};

int MAP[16][16];
int IS_VISIT[16][16];

bool FLAG = false;

void DFS(const pii& cur, const pii& e_pos)
{
	if (cur == e_pos) {FLAG = true; return;}
	IS_VISIT[cur.Y][cur.X] = true;


	for (int mvi = 0; mvi < 4; ++mvi)
	{
		pii nxt = cur; nxt += MV[mvi];
		if (0 > nxt.Y || nxt.Y >= 16 || 0 > nxt.X || nxt.X >= 16) continue;
		if (MAP[nxt.Y][nxt.X] == 1) continue;
		if (IS_VISIT[nxt.Y][nxt.X]) continue;
		DFS(nxt, e_pos);
	}
}

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	for (int t = 1; t <= 10; ++t )
	{
		FLAG = false;
		int ct; scanf("%d", &ct);
		pii sPos, ePos;
		memset(IS_VISIT, 0, sizeof(IS_VISIT));
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 16; ++j)
			{
				scanf("%1d", &MAP[i][j]);
				if (MAP[i][j] == 2) sPos = {i, j};
				if (MAP[i][j] == 3) ePos = {i, j};
			}
		}

		DFS(sPos, ePos);
		printf("#%d %d\n", t, FLAG);
	}
}