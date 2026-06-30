#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	// freopen("input.txt", "r", stdin);
	int arr[100][100] = {0};
	for (int t = 1; t <= 10; t++)
	{
		int thresh;
		scanf("%d", &thresh);

		int sr = 0;
		for (int i = 0 ; i < 100; i++)
		{
			for (int j = 0 ; j < 100; j++)
			{
				scanf("%d", &arr[i][j]);
			}
		}
		int mn = 10101;
		int mnr = 0;
		vector<pair<int, int>> res;
		for (int orr = 0; orr < 100; ++orr )
		{
			int r = orr;
			int dir = 0;
			int c = 99;
			if (arr[c][r] == 0) continue;
			int cnt = 0;
			while (c >= 0 && (0 <= r && r < 100))
			{
				if (dir != 0)
				{
					r += dir;
					if (arr[c - 1][r] == 1)
						dir = 0;
				}
				else if (dir == 0)
				{
					--c;
					if (!(r >= 99) && arr[c][r + 1] == 1)
						dir = 1;
					else if (!(r <= 0) && arr[c][r - 1] == 1)
						dir = -1;
				}
				cnt++;
				if (c == 0) break;
			}
			if (cnt < mn)
			{
				mn = cnt;
				mnr = r;
			}
		}
		printf("#%d %d\n", t, mnr);
	}
}