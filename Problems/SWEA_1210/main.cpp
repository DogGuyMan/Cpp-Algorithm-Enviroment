#include <iostream>
#include <queue>
using namespace std;

inline bool IsBound(int curY, int curX)
{
	return 0 <= curY && 0 <= curX && curY < 100 && curX < 100;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	for (int tc = 1; tc <= 10; ++tc)
	{
		int arr[101][101];
		bool visit[101][101] = {{0}};
		int thrash; scanf("%d", &thrash);
		int StartX;
		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				int tmp;
				scanf("%d", &tmp);
				arr[i][j] = tmp;
				if (tmp == 2) StartX = j;
			}
		}

		queue<pair<int, int>> q;
		q.push({99, StartX});
		int resX = -1;
		while (!q.empty())
		{
			auto cur = q.front(); q.pop();
			int& curX = cur.second;
			resX = curX;
			int& curY = cur.first;
			visit[curY][curX] = true;
			if 	(IsBound(curY, curX - 1) && !visit[curY][curX - 1] && arr[curY][curX - 1] == 1) { q.push({curY, curX - 1});}
			else if (IsBound(curY, curX + 1) && !visit[curY][curX + 1] && arr[curY][curX + 1] == 1) { q.push({curY, curX + 1});}
			else if (IsBound(curY - 1, curX) && !visit[curY - 1][curX] && arr[curY - 1][curX] == 1) { q.push({curY - 1, curX});}
		}
		printf("#%d %d\n", tc, resX);
	}
	return 0;
}