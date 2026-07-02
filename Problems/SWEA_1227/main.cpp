#include <iostream>
#include <deque>
#include <vector>
#include <cstring>
#define Y first
#define X second
using namespace std;
typedef pair<int, int> pii;

pii operator+(const pii& lhs, const pii& rhs) { return {lhs.Y + rhs.Y, lhs.X + rhs.X}; }

pii MV[4] = { { 0,  1}, {-1,  0}, { 0, -1}, { 1,  0} };
int MAP[100][100];
int IS_VISIT[100][100];
bool FLAG = false;

int main()
{
	freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; ++t )
	{
		FLAG = false;
		int ct; scanf("%d", &ct);
		pii sPos, ePos;
		memset(IS_VISIT, 0, sizeof(IS_VISIT));
		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				scanf("%1d", &MAP[i][j]);
				if (MAP[i][j] == 2) sPos = {i, j};
				if (MAP[i][j] == 3) ePos = {i, j};
			}
		}

		deque<pii> q; q.push_back(sPos);
		while (!q.empty())
		{
			pii cur = q.front(); q.pop_front();
			if (cur == ePos) {FLAG = true; break;}
			IS_VISIT[cur.Y][cur.X] = true;

			for (int mvi = 0; mvi < 4; ++mvi)
			{
				pii nxt = cur + MV[mvi];
				if (0 > nxt.Y || nxt.Y >= 100 || 0 > nxt.X || nxt.X >= 100) continue;
				if (MAP[nxt.Y][nxt.X] == 1) continue;
				if (IS_VISIT[nxt.Y][nxt.X]) continue;
				q.push_back(nxt);
			}
		}

		printf("#%d %d\n", t, FLAG);
	}
}