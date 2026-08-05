#include <string>
#include <vector>
#include <cstdio>

using namespace std;
typedef unsigned long long llu;

long long solution(int n, vector<int> times)
{
	long long answer = 0;
	llu lo = 0, hi = 1e19, mid;
	for (auto& e : times) if (e == 0) return 0;
	for (int i = 0; i < 100; ++i)
	{
		mid = (lo + hi) / 2;
		llu candiCnt = 0;
		for (auto& e : times)
			candiCnt += (mid / (llu)e);
		if (n <= candiCnt) hi = mid;
		else lo = mid;
	}
	return hi;
}