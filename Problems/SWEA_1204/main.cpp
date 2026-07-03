#include <iostream>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	int TC;
	scanf("%d", &TC);
	for (int t = 1 ; t <= TC; t++)
	{
		int num; scanf("%d", &num);
		int SCORES[1010] = {0};
		int temp; char c;
		while (scanf("%d%c", &temp, &c) == 2)
		{
			++SCORES[temp];
			if (c == '\n') break;
		}
		int mxIdx = 0;
		for (int i = 0; i < 101; i++)
			if (SCORES[mxIdx] <= SCORES[i])
				mxIdx = i;
		printf("#%d %d\n", t, mxIdx);
	}
}