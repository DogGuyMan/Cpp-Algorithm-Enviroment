#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int TC;
int N, K;
int RES;
int MVX[4] = {1, 0, -1, 0};
int MVY[4] = {0, -1, 0, 1};
int MAP[8][8] = {0};
bool IS_VISIT[8][8] = {0};

inline bool IS_INBOUND(int cy, int cx)
{
	if (cx < 0 || cx >= N) return false;
	if (cy < 0 || cy >= N) return false;
	return true;
}

void DFS(int cy, int cx, int cnt, int brk)
{
	IS_VISIT[cy][cx] = true;

	RES = max(RES, cnt);
	for (int i = 0; i < 4; i++)
	{
		int ny = cy + MVY[i];
		int nx = cx + MVX[i];
		if (!IS_INBOUND(ny, nx)) continue;
		if (IS_VISIT[ny][nx]) continue;

		if ((MAP[cy][cx] <= MAP[ny][nx]) && brk > 0 && MAP[cy][cx] > (MAP[ny][nx] - K))
		{
			int oriMap = MAP[ny][nx];
			MAP[ny][nx] = MAP[cy][cx] - 1;
			DFS(ny, nx, cnt + 1, 0);
			MAP[ny][nx] = oriMap;
		}
		else if (MAP[cy][cx] > MAP[ny][nx])
			DFS(ny, nx, cnt + 1, brk);
	}
	IS_VISIT[cy][cx] = false;
}

int main()
{

	scanf("%d", &TC);

	for (int tc = 1; tc <= TC; ++tc)
	{
		scanf("%d %d", &N, &K);
		int topVal = 0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &MAP[i][j]);
				topVal = max(topVal, MAP[i][j]);
			}
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (MAP[i][j] == topVal)
					DFS(i, j, 1, 1);
		printf("#%d %d\n", tc, RES);
		memset(MAP, 0, sizeof(MAP));
		memset(IS_VISIT, 0, sizeof(IS_VISIT));
		RES = 0;
	}
	return 0;
}