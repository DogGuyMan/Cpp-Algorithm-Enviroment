// 숫자 2개

#include <iostream>

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
int main()
{
	//freopen("input.txt", "r", stdin);
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