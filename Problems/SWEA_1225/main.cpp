#include <iostream>
#include <deque>
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		int ct;  scanf("%d", &ct);
		deque<int> q;
		int minVal = 1e9;
		for (int i = 0 ; i < 8; i++)
		{
			int val; scanf("%d", &val);
			q.push_back(val);
			if (minVal > val) minVal = val;
		}
		int mul = (minVal - 1) / 15;   // 이분 탐색 없이 O(1)
		for (int i = 0; i < 8; i++) q[i] -= 15 * mul;

		int itt = 0; int CYCLE = 5;
		while (q.back() != 0)
		{
			int f = q.front(); q.pop_front();
			f -= ++itt;
			if (itt == CYCLE) itt = 0;
			q.push_back((f < 0) ? 0 : f);
		}
		printf("#%d ", t);
		for (int i = 0 ; i < 8; i++)
			printf("%d ", q[i]);
		printf("\n");
	}
	return 0;
}
