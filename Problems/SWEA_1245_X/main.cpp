#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#define P first
#define M second
#define L 0
#define R 1

using namespace std;
typedef pair<double, int> pdi;

inline bool IsEqualDouble(double lhs, double rhs)
{
	// printf(std::abs(%lf - %lf) = %lf < 1e-12\n", lhs, rhs,std::abs(lhs - rhs));
	return fabs(lhs - rhs) <= 1e-15;
}

inline double GrapForce(int m1, int m2, double d)
{
	return (double)((long long)m1 * (long long)m2) / (d * d);
}

// 양수
// lo 가 정답.
// TTTTTTTT/FFFFFFFFFFFF
inline int JudgeFunc(const vector<pdi>& magnets, double cur_pos)
{

	double force[2] {0, 0};
	for (auto& magnet : magnets)
	{
		if (magnet.P < cur_pos)
			force[L] += GrapForce(magnet.M, 1, magnet.P - cur_pos);
		else if (cur_pos < magnet.P)
			force[R] += GrapForce(magnet.M, 1, magnet.P - cur_pos);
	}
	// printf("res : %lf %lf\n", force[L], force[R]);
	if (IsEqualDouble(force[L], force[R])) return 0;
	return (force[R] - force[L]) < 0 ? 1 : -1;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		int N; scanf("%d", &N);
		vector<pdi> magnets(N, {(double)0, 0});
		for (int i = 0; i < N; ++i)
			scanf("%lf", &(magnets[i].P));
		for (int i = 0; i < N; ++i)
			scanf("%d", &(magnets[i].M));

		printf("#%d ", tc);
		for (int i = 0 ; i < (int)(magnets.size() - 1); ++i)
		{
			double lpos = magnets[i].P;
			double rpos = magnets[i + 1].P;

			double lo = lpos, hi = rpos;
			for (int iter = 0; iter < 100; ++iter)
			{
				double mid = (lo + hi) / (double)2.0;
				// printf("mid : %lf\n", mid); // DEBUG
				int judged = JudgeFunc(magnets, mid);
				if (judged == 0)
				{
					lo = mid; break;
				}
				else if (judged < 0) {hi = mid;}
				else if (judged > 0) {lo = mid;}
			}
			printf("%.10lf ", lo);
		}
		printf("\n");
	}
	return 0;
}
