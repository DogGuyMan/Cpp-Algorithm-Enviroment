#include <cstdio>
typedef long long ll;

// 1 1 2 3 5
ll factorial(int num)
{
	if (num == 0) return 1;
	if (num <= 3) return num;
	return num * factorial(num - 1);
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int tcmax;
	scanf("%d", &tcmax);

	for (int tc = 1; tc <= tcmax; ++tc)
	{
		int num; scanf("%d", &num);
		printf("#%d %lld", tc, factorial(num));
	}
}