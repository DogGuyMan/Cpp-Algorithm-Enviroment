#include <iostream>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		long long mn = 1e10, mx = -mn;
		int N; scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			int tmp; scanf("%d", &tmp);
			if (mn > tmp) {mn = tmp;};
			if (mx < tmp) {mx = tmp;};
		}
		printf("#%d %lld", t, mx - mn);
	}
}