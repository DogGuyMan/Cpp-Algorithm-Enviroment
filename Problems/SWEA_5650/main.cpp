#include <iostream>
#include <vector>
#define Y first
#define X second
using namespace std;
typedef pair<int, int> pii;

bool operator==(const pii& lhs, const pii& rhs)
{
	return (lhs.Y == rhs.Y) && (lhs.X == rhs.X);
}
pii& operator+=(pii& lhs, const pii& rhs)
{
	lhs.first  += rhs.first;
	lhs.second += rhs.second;
	return lhs;
}


// 0=상 1=하 2=좌 3=우
const vector<int> MV_Y = {-1, 1, 0, 0};
const vector<int> MV_X = { 0, 0, -1, 1};
const vector<int> MV_OPP_IDX = {1, 0, 3, 2};        // 반대 방향 (상<->하, 좌<->우)
// > , ^,  <,  v
const vector<int> REFLECT_LUT[6]
{
	{ 0,  1,  2,  3},  // 0 미사용
	{-1,  3,  0, -1},  // 1
	{ 3, -1,  1, -1},  // 2
	{ 2, -1, -1,  1},  // 3
	{-1,  2, -1,  0},  // 4
	{-1, -1, -1, -1},  // 5 (전부 반사)
};

int main()
{
	int TC = 0;

	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);

	for (int tc = 1; tc <= TC; ++tc)
	{
		int N = 0;
		vector<pii> HOLE_POS[11];
		vector<pii> EMPTY_POS;

		scanf("%d", &N);
		vector<vector<int>> MAP(N, vector<int>(N, 0));
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &MAP[i][j]);
				if (MAP[i][j] >= 6)
					HOLE_POS[MAP[i][j]].push_back({i, j});
				if (MAP[i][j] == 0) EMPTY_POS.push_back({i, j});
			}
		}

		int MAX_CNT = 0;
		for (const pii& epos : EMPTY_POS)
		{
			pii initPos = epos;
			for (int mv = 0; mv < 4; mv++)
			{
				pii curPos = epos;
				int HIT_CNT = 0;
				int curMv = mv;
				while (true)
				{
					// 이동하고
					curPos += {MV_Y[curMv], MV_X[curMv]};

					// printf("curPos {%d, %d}\n", curPos.Y, curPos.X);
					// 판정하기.
					if (curPos.Y < 0 || curPos.Y >= N) {++HIT_CNT; HIT_CNT = ((HIT_CNT - 1) * 2 + 1); break;}
					if (curPos.X < 0 || curPos.X >= N) {++HIT_CNT; HIT_CNT = ((HIT_CNT - 1) * 2 + 1); break;}
					if (initPos == curPos) break;

					int curVal = MAP[curPos.Y][curPos.X];
					if (curVal == 0) continue;
					if (curVal == -1) break;
					// 웜홀 판정하기
					if (curVal >= 6)
					{
						for (const auto& hPos : HOLE_POS[curVal])
							if (hPos != curPos) { curPos = hPos; break; }
						continue;
					}

					// 블록(1~5) 반사
					curMv = REFLECT_LUT[curVal][curMv];
					++HIT_CNT;
					if (curMv == -1) {HIT_CNT = ((HIT_CNT - 1) * 2 + 1); break;}
				}

				MAX_CNT = max(MAX_CNT, HIT_CNT);
			}
		}
		printf("#%d %d\n", tc, MAX_CNT);
	}
	return 0;
}