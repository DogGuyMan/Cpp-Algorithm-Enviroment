#include <cstdio>
#include <vector>

using namespace std;

// arr이 0이면 lo = -1 보장해 줘야 하는듯.
int BSLTTTFFF(const vector<int>& arr, int target)
{
	int lo = -1, hi = (int)arr.size();

	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		if (arr[mid] <= target) lo = mid; // true임
		else hi = mid; // false임
	}
	if (0 <= lo && arr[lo] == target) return lo;

	return -1;
}

int BSHFFFTTT(const vector<int>& arr, int target)
{
	int lo = -1, hi = (int)arr.size();
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		if (target <= arr[mid]) hi = mid; // true임.
		else lo = mid; // false임
	}
	if (hi < (int)arr.size() && arr[hi] == target) return hi;
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
		int M, N; scanf("%d %d", &M, &N);
		vector<int> arr; arr.resize(M);
		for (int i = 0; i < M; ++i)
			scanf("%d", &arr[i]);
		printf("#%d ", tc);
		for (int i = 0 ; i < N; ++i)
		{
			int tmp; scanf("%d", &tmp);
			printf("%d ", BSHFFFTTT(arr, tmp));
		}
		printf("\n");
	}
	return 0;
}