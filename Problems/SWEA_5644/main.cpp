#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Pos
{
	int y, x;
};

struct BC
{
	Pos pos;
	int c;
	int p;
};

Pos MV[5] = {
    {0, 0},
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

bool IsBound(Pos pos)
{
	if (pos.y > 10 || pos.y < 1)
		return false;
	if (pos.x > 10 || pos.x < 1)
		return false;
	return true;
}

int Dist(Pos s, Pos e)
{
	return abs(s.y - e.y) + abs(s.x - e.x);
}

int main(int argc, char **argv)
{
	int test_case;
	int T;

	// freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int M, A;
		scanf("%d %d", &M, &A);
		vector<int> userPaths[2];
		int tempPath;
		for (int i = 0; i < M; i++)
		{
			scanf("%d", &tempPath);
			userPaths[0].push_back(tempPath);
		}
		for (int i = 0; i < M; i++)
		{
			scanf("%d", &tempPath);
			userPaths[1].push_back(tempPath);
		}
		vector<BC> bcs;
		int x, y, c, p;
		for (int i = 0; i < A; i++)
		{
			scanf("%d %d %d %d", &x, &y, &c, &p);
			bcs.push_back({{y, x}, c, p});
		}

		long long total = 0;
		Pos userPos[2] = {{1, 1}, {10, 10}};
		for (int curTime = 0; curTime <= M; curTime++)
		{
			long long best = -1;
			
			for (int i = -1; i < A; i++)
			{
				if (!IsBound(userPos[0])) continue;
				BC curBCA = (i == -1) ? BC{{0,0}, 0,0} : bcs[i];
				if (i >= 0 && Dist(curBCA.pos, userPos[0]) > curBCA.c) continue;
				for (int j = -1; j < A; j++)
				{
					long long val = 0;
					if (!IsBound(userPos[1])) continue;
					BC curBCB = (j == -1) ? BC{{0,0}, 0,0} : bcs[j];
					if (j >= 0 &&  Dist(curBCB.pos, userPos[1]) > curBCB.c) continue;
					if(i == j && i != -1) val = curBCB.p;
					else if(i != -1 && j == -1) val = curBCA.p;
					else if(i == -1 && j != -1) val = curBCB.p;
					else if(i != -1 && j != -1) val = curBCA.p + curBCB.p;

					best = max(best, val);
				}
			}
			// printf("%d %llu\n", curTime, best); DEBUG
			total += best;
			userPos[0] = {userPos[0].y + MV[userPaths[0][curTime]].y, userPos[0].x + MV[userPaths[0][curTime]].x};
			userPos[1] = {userPos[1].y + MV[userPaths[1][curTime]].y, userPos[1].x + MV[userPaths[1][curTime]].x};
		}
		printf("#%d %lld\n", test_case, total);
	}
	return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}