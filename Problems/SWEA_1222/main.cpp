#include <iostream>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		int N; scanf("%d", &N);
		long long sum = 0;
		long long val = 0;
		for (int i = 0; i < N; ++i)
		{
			char trsh;
			scanf("%lld%c", &val, &trsh);
			sum += val;
			// printf("%lld\n", val);
		}
		scanf("%lld", &val);
		sum += val;
		printf("#%d %lld\n", t, sum);
	}
}