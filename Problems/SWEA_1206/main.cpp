#include <iostream>
#include <vector>

using namespace std;
int main()
{
	// freopen("input.txt", "r", stdin);

	int N;
	int TC = 1;
	while (scanf("%d", &N) != EOF)
	{
		vector<int> v;
		int temp; char thresh;
		// printf("%d\n", N); // DEBUG
		while (scanf("%d%c", &temp, &thresh) == 2)
		{
			v.push_back(temp);
			if (thresh == '\n')
				break;
		}
		int cnt = 0;
		for (int i = 2; i < v.size() - 2; ++i)
		{
			int mn = 999;
			for (int gap = -2; gap <= 2; gap++)
			{
				if (gap == 0) continue;
				if (v[i] - v[i + gap] < mn)
					mn = v[i] - v[i + gap];
			}
			if (mn <= 0) continue;
			cnt += mn;
		}
		// for (auto& e : v) // DEBUG
		// printf("%d ", e); // DEBUG
		// printf("\n"); // DEBUG
		printf("#%d %d\n", TC++, cnt);
	}
	return 0;
}