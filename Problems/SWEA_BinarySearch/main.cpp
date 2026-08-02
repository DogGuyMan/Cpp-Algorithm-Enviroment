#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int T, M, N;

// 몸통(참이면 lo, 거짓이면 hi)은 고정. lo가 정답 — 마지막으로 target 이하인 인덱스.
int BinarySearchLo(vector<int>& arr, int target)
{
	int lo = -1, hi = (int)arr.size();
	auto isLo = [&](int mid) { return arr[mid] <= target; };
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		if (isLo(mid)) lo = mid;
		else hi = mid;
	}
	if (lo >= 0 && arr[lo] == target) return lo;
	return -1;
}

// 몸통이 뒤집힘(참이면 hi, 거짓이면 lo). hi가 정답 — 처음으로 target 이상인 인덱스.
int BinarySearchHi(vector<int>& arr, int target)
{
	int lo = -1, hi = (int)arr.size();
	auto isHi = [&](int mid) { return arr[mid] >= target; };
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		if (isHi(mid)) hi = mid;
		else lo = mid;
	}
	if (hi < (int)arr.size() && arr[hi] == target) return hi;
	return -1;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		// input
		vector<int> arr;
		vector<int> targets;
		{
			scanf("%d %d", &M, &N);
			arr.resize(M);
			targets.resize(N);
			for (int i = 0; i < M; ++i)
				scanf("%d", &arr[i]);
			for (int i = 0; i < N; ++i)
				scanf("%d", &targets[i]);
		}

		printf("#%d ", tc);
		for (auto& target : targets)
			printf("%d ", BinarySearchLo(arr, target));
		printf("\n");
	}
	return 0;
}