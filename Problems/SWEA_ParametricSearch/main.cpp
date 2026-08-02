#include <cstdio>
#include <vector>

using namespace std;
typedef long long ll;

// lo(마지막 참)와 hi(첫 거짓)는 어떤 문제든 항상 정확히 1칸 차이난다.
// (lo+1==hi). 이건 예외 없는 구조적 성질

int LowAnsTTTFFF(const vector<int>& ribbons, ll& lo, ll& hi, const int target)
{
	while (lo + 1 < hi)
	{
		ll mid = (lo + hi) / 2;
		ll ribbonCnt = 0;
		for (auto& len : ribbons)
			ribbonCnt += (len / mid);
		// 조건을 만족하는 가장 큰 L
		if (ribbonCnt >= target) lo = mid; // mid 참
		else hi = mid; // mid 거짓
	}
	return lo;
}

int HiAnsFFFTTT(const vector<int>& ribbons, ll& lo, ll& hi, const int target)
{
	while (lo + 1 < hi)
	{
		ll mid = (lo + hi) / 2;
		ll ribbonCnt = 0;
		for (auto& len : ribbons) ribbonCnt += (len / mid);
		// 처음으로 불가능해지는 L
		if (ribbonCnt < target) hi = mid; // hi 참
		else lo = mid; // lo 거짓
	}
	return hi;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T, K, N;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		scanf("%d %d", &K, &N);
		vector<int> ribbons(K, 0);
		ll lo = 1, hi = 1e9;
		for (int i = 0; i < K; ++i)
			scanf("%d", &ribbons[i]);

		// lo는 확실히 참, hi는 확실히 거짓. 답은 (lo, hi) 사이.
		HiAnsFFFTTT(ribbons, lo, hi, N);

		printf("#%d %lld\n", tc, lo);
	}
	return 0;
}
