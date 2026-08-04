#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define Y first
#define X second
#define INF 101010
typedef pair<int, int> pii;

int N;
int ANS = INF;

inline pii Promising(const vector<pii>& arr, const vector<bool>& sel)
{
	int SX = 0, SY = 0;
	//  printf("size : %d\n", (int)sel.size());
	for (int i = 0; i < N; ++i)
	{
		if (sel[i]) SX += arr[i].X;
		else SY += arr[i].Y;
	}
	return {SY, SX};
}


void BF(const vector<pii>& arr, vector<bool>& sel, int prevSel = -1)
{
	// printf("%d\n", ++cnt);
	auto res = Promising(arr, sel);
	int candi = (res.X >= res.Y) ? res.X : 1e9;
	ANS = min(ANS, candi);
	for (int i = 0; i < N; ++i)
	{
		if (sel[i] == true)
			printf("%5d ", i + 1);
		else
			printf("%5d ", 0);
	}
	printf(" : %5d >= %5d -> %5d\n", res.X, res.Y, candi);

	for (int i = prevSel + 1; i < N; ++i)
	{
		sel[i] = true;
		BF(arr, sel, i);
		sel[i] = false;
	}
}

int DP[1010][2020];

int DPSolve(const vector<pii>& piiarr, const vector<int>& accum, const int mxSx)
{
	for (int Sx = 1; Sx <= mxSx; ++Sx)
	{
		for (int selIdx = 1; selIdx <= N; ++selIdx)
		{
			int newVal = DP[selIdx - 1][Sx];
			if (Sx - piiarr[selIdx].X >= 0)
			{
				int candiVal = DP[selIdx - 1][Sx - piiarr[selIdx].X] - piiarr[selIdx].Y;
				if (candiVal < newVal)
					newVal = candiVal;
			}
			DP[selIdx][Sx] = newVal;
			if (Sx >= newVal) return Sx;
		}
	}
	return mxSx;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		ANS = 1e9;

		scanf("%d", &N);
		vector<pii> piiarr(N + 1, {0, 0});
		vector<bool> used(N, false);
		for (int i = 1; i <= N; ++i)
		{
			scanf("%d %d", &(piiarr[i].X), &(piiarr[i].Y));
		}
		sort(piiarr.begin(), piiarr.end(), [&](const pii & lhs, const pii & rhs)->bool
		{
			if (lhs.X == rhs.X) return lhs.Y < rhs.Y;
			return lhs.X < rhs.X;
		});
		// {
		// 	for (auto& pr : piiarr)
		// 		printf("%5d ", pr.Y);
		// 	printf("\n");
		// 	BF(piiarr, used);
		// 	printf("#%d %d\n", tc, ANS);
		// }

		int mxSy = 0, mxSx = 0;
		vector<int> accum; accum.push_back(0);
		for (auto& pr : piiarr)
		{
			mxSy += pr.Y;
			mxSx += pr.X;
			accum.push_back(mxSx);
		}
		for (int selIdx = 0; selIdx <= N; ++selIdx)
			for (int Sx = 0; Sx <= mxSx; ++Sx)
				DP[selIdx][Sx] = INF;
		for (int i = 0; i <= N; ++i)
			DP[i][0] = mxSy;

		int ansSx = DPSolve(piiarr, accum, mxSx);
		// for (int selIdx = 0; selIdx <= N; ++selIdx)
		// {
		// 	printf("%d | ", selIdx);
		// 	for (int Sx = 0; Sx <= mxSx; ++Sx)
		// 	{

		// 		printf("%6d ", DP[selIdx][Sx]);
		// 	}
		// 	printf("\n");
		// }
		printf("#%d %d\n", tc, ansSx);

		// for (auto& pr : pairarr)
		// {
		// 	printf("%d %d\n", pr.X, pr.Y);
		// }
		// printf("\n");
	}
	return 0;
}
