#include <iostream>

int main()
{
	//freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; t++)
		//for (int t = 1; t <= 1; t++)
	{
		int thresh;
		scanf("%d", &thresh);
		int arr[100][100] = {0};
		int sr = 0;
		for (int i = 0 ; i < 100; i++)
		{
			for (int j = 0 ; j < 100; j++)
			{
				scanf("%d", &arr[i][j]);
				if (i == 99 && arr[i][j] == 2) sr = j;
			}
		}
		int dir = 0;
		int c = 99;
		int r = sr;
		while (c >= 0 && (0 <= r && r < 100))
		{
			// printf("dir : %d {%d %d}\n", dir, c, r);
			if (dir != 0)
			{
				r += dir;
				if (arr[c - 1][r] == 1)
					dir = 0;
			}
			else if (dir == 0)
			{
				--c;
				if (r < 99 && arr[c][r + 1] == 1)
					dir = 1;
				else if (r >= 1 && arr[c][r - 1] == 1)
					dir = -1;
			}
			arr[c][r] = 8;
		}
		// for (int i = 0 ; i < 100; i++)
		// {
		// 	for (int j = 0 ; j < 100; j++)
		// 	{
		// 		printf("%3d", arr[i][j]);
		// 	}
		// 	printf("\n");
		// }
		for (int i = 0; i < 100; i++)
			if (arr[0][i] == 8) r = i;
		printf("#%d %d\n", t, r);
	}
}