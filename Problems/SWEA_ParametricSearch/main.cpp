#include <cstdio>
#include <vector>

using namespace std;
typedef long long ll ;

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		int K, N; scanf("%d %d", &K, &N);
		vector<int> arr(K, 0);
		for (int i = 0; i < K; ++i)
			scanf("%d", &arr[i]);

		ll lo = 0, hi = *max_element(arr.begin(), arr.end()) + 1, mid;
		// lo가 정답, lo + 1 == hi 는 오답
		// TTTFFF
		while (lo + 1 < hi)
		{
			mid = lo + (hi - lo) / 2;
			ll ribbonCnt = 0;
			for (auto& len : arr)
				ribbonCnt += (len / mid);

			if (ribbonCnt >= N) lo = mid;
			else hi = mid;
		}
		printf("#%d %lld", tc, lo);

		// 절대 hi가 정답인게 불가능 ❌ lo + 1 == hi가 정답, lo 는 오답
		// 절대 hi가 정답인게 불가능 ❌ FFFTTT
		// 절대 hi가 정답인게 불가능 ❌ while (lo + 1 < hi)
		// 절대 hi가 정답인게 불가능 ❌ {
		// 절대 hi가 정답인게 불가능 ❌ 	mid = lo + (hi - lo) / 2;
		// 절대 hi가 정답인게 불가능 ❌ 	ll ribbonCnt = 0;
		// 절대 hi가 정답인게 불가능 ❌ 	for (auto& len : arr)
		// 절대 hi가 정답인게 불가능 ❌ 		ribbonCnt += (len / mid);
		// 절대 hi가 정답인게 불가능 ❌ 	if (ribbonCnt < N) hi = mid;
		// 절대 hi가 정답인게 불가능 ❌ 	else lo = mid;
		// 절대 hi가 정답인게 불가능 ❌ }
		// 절대 hi가 정답인게 불가능 ❌ printf("#%d %lld", tc, hi);
	}
	return 0;
}