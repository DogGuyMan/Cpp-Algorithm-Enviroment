
#include <iostream>
#include <algorithm>
#include <vector>
#define VAL first
#define CAL second
#define INF 1e9

using namespace std;

typedef pair<int, int> pii;

int T;
int N, L;
int ANS_VAL = -INF;
static int DP[22][22222];

// 선택했냐 안했냐.
void BF(const vector<pii>& ingre, vector<int>& sel_idx, int cur_depth, int cur_val, int cur_cal)
{
	if (cur_depth > N)
	{
		printf("[ ");
		for (const auto& idx : sel_idx) printf("%5d, ", idx);
		printf(" ] : %5d %5d", cur_val, cur_cal);
		printf(" -> %3c\n", (cur_cal <= L) ? 'O' : 'X');
		if (cur_cal <= L)
			ANS_VAL = max(ANS_VAL, cur_val);
		return;
	}
	sel_idx.push_back(cur_depth);
	BF(ingre, sel_idx,
	   cur_depth + 1,
	   cur_val + ingre[cur_depth].VAL,
	   cur_cal + ingre[cur_depth].CAL
	  );
	sel_idx.pop_back();

	sel_idx.push_back(-1);
	BF(ingre, sel_idx,
	   cur_depth + 1,
	   cur_val,
	   cur_cal
	  );
	sel_idx.pop_back();
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		ANS_VAL = 0;
		scanf("%d %d", &N, &L);
		vector<pii> ingre(N + 1, {0, 0});
		for (int i = 1; i <= N; ++i)
		{
			scanf("%d %d", &(ingre[i].VAL), &(ingre[i].CAL));
		}

		sort(ingre.begin(), ingre.end(), [&](const pii & lhs, const pii & rhs) -> bool
		{
			if (lhs.CAL == rhs.CAL)
				return lhs.VAL < rhs.VAL;
			return lhs.CAL < rhs.CAL;
		});
		// {
		// 	for (int i = 1; i <= N; ++i)
		// 		printf("%5d %5d\n", ingre[i].VAL, ingre[i].CAL);
		// 	vector<int> selIdxs;
		// 	printf("[ ");
		// 	for (int i = 1; i <= N; ++i) printf("%5d, ", i);
		// 	printf(" ] : %5s %5s\n\n", "val", "cal");
		// 	BF(ingre, selIdxs, 1, 0, 0);
		// 	printf("ans :%d\n", ANS_VAL);

		// 	for (int i = 0; i <= N; ++i)
		// 		for (int j = 0; j <= L; ++j)
		// 			DP[i][j] = -INF;

		// 	printf("%5c |", '-');
		// 	for (int j = 0; j <= L; ++j)
		// 	{
		// 		printf("%5d |", j);
		// 	}
		// 	printf("\n");
		// 	for (int i = 0; i <= N; ++i)
		// 	{
		// 		printf("%5d |", i);
		// 		for (int j = 0; j <= L; ++j)
		// 		{
		// 			printf("%5s |", (DP[i][j] == -INF) ? "-" : to_string(DP[i][j]).c_str());
		// 		}
		// 		printf("\n");
		// 	}
		// }
		for (int i = 0; i <= N; ++i)
			for (int j = 0; j <= L; ++j)
				DP[i][j] = -INF;

		for (int i = 0; i <= N; ++i) DP[i][0] = 0;

		for (int cur_depth = 1; cur_depth <= N; ++cur_depth)
		{
			for (int cur_cal = 0; cur_cal <= L; ++cur_cal)
			{
				DP[cur_depth][cur_cal] = DP[cur_depth - 1][cur_cal];
				int prevCal = cur_cal - ingre[cur_depth].CAL;
				if (
				    prevCal >= 0 &&
				    DP[cur_depth - 1][prevCal] != (1e9))
				{
					DP[cur_depth][cur_cal] = max(
					                             DP[cur_depth][cur_cal],
					                             DP[cur_depth - 1][prevCal] + ingre[cur_depth].VAL
					                         );
				}
				ANS_VAL = max(DP[cur_depth][cur_cal], ANS_VAL);
			}
		}

		printf("#%d %d\n", tc, ANS_VAL);
	}
	return 0;
}
