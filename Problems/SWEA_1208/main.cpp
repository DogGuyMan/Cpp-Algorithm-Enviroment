#include <iostream>
#include <algorithm>
#include <vector>
#define IDX first
#define CNT second
using namespace std;

typedef pair<int, int> pii;

int main()
{
	// freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; t++)
	{
		vector<pii> orders;
		int DCNT; scanf("%d", &DCNT);
		int arr[101] = {0};
		for (int i  = 0; i < 100; i++)
		{
			scanf("%d", &arr[i]);
			orders.push_back({i, arr[i]});
		}
		bool flag = false;
		int mxGap = 0;
		for (int i = 0; i < 100 - 1; i++)
			mxGap = max(mxGap, arr[i] - arr[i + 1]);
		if (mxGap == 0)
		{
			printf("#%d %d\n", t, 0);
			continue;
		}
		const auto comp = [&](const pii & lhs, const pii & rhs) -> bool
		{
			if (lhs.CNT == rhs.CNT)
				return lhs.IDX < rhs.IDX;
			return lhs.CNT < rhs.CNT;
		};
		for (int d = 1; d <= DCNT; ++d)
		{
			sort(orders.begin(), orders.end(), comp);
			orders.front().CNT = orders.front().CNT + 1;
			orders.back().CNT = orders.back().CNT - 1;
		}
		sort(orders.begin(), orders.end(), comp);
		printf("#%d %d\n", t, (orders.back().CNT - orders.front().CNT));
		// for (const auto& e : orders) printf("%3d", e.IDX); printf("\n");
		// for (const auto& e : orders) printf("%3d", e.CNT); printf("\n");
	}
}