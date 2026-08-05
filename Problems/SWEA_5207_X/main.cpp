#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

int BinarySearchIdx(const vector<int>& arr, int target)
{
	int lo = -1, hi = (int)arr.size(), mid;
	int dir = 0;

	while (lo + 1 < hi)
	{
		mid = (lo + hi) / 2;

		if (target < arr[mid])
		{
			if (dir == 1) return -1;
			dir = 1; hi = mid;
		}
		else if (target > arr[mid])
		{
			if (dir == -1) return -1;
			dir = -1; lo = mid;
		}
		else
			return mid;
	}
	return -1;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		int N, M; scanf("%d %d", &N, &M);
		int ans = 0;
		vector<int> arr(N, 0);
		for (int i = 0; i < N; i++)
			scanf("%d", &arr[i]);
		sort(arr.begin(), arr.end());

		for (int i = 0; i < M; i++)
		{
			int target; scanf("%d", &target);
			int idx = BinarySearchIdx(arr, target);
			if (idx >= 0) ++ans;
		}
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}
