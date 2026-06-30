#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	// freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; t++)
	{
		int thresh;
		scanf("%d", &thresh);
		long long rowMx = 0;
		long long col[100] = {0};
		long long diagrd = 0;
		long long diagld = 0;
		long long MX = 0;
		for (int i = 0; i < 100; i++)
		{
			long long r = 0;
			for (int j = 0; j < 100; j++)
			{
				long long temp; scanf("%lld", &temp);
				r += temp;
				col[j] += temp;
				if (i == j) diagrd += temp;
				if (i + j == 99) diagld += temp;
			}
			rowMx = max(rowMx, r);
		}
		MX = rowMx;
		for (int i = 0; i < 100; ++i)
			MX = max(MX, col[i]);
		MX = max(MX, diagrd);
		MX = max(MX, diagld);
		printf("#%d %lld\n", t, MX);
	}
}