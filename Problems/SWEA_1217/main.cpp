// 숫자 2개

#include <iostream>
#include <cstdio>

int Pow(int lhs, int rhs)
{
	if (rhs == 0)
		return 1;
	if (rhs == 1)
		return lhs;
	if (rhs == 2)
		return lhs * lhs;
	if (rhs % 2 == 0)
		return Pow(lhs, (rhs >> 1)) * Pow(lhs, (rhs >> 1));
	else
		return lhs * Pow(lhs, (rhs >> 1)) * Pow(lhs, (rhs >> 1));
}
int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		int ct; scanf("%d", &ct);
		int N, M; scanf("%d %d", &N, &M);
		if (N <= 1)
			printf("#%d %d\n", ct,  N);
		else
			printf("#%d %d\n", ct,  Pow(N, M));
	}
}