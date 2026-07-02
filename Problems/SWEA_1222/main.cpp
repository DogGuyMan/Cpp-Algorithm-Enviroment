#include <iostream>

int main()
{
	freopen("input.txt", "r", stdin);
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