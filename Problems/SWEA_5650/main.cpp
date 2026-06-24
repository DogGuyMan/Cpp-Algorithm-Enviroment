/*
테케 T
    N + 2 x N + 2 -> 인접 리스트 혹은 무엇. 모든 끄트머리는 블럭 5번
    빈 공간에서 상하좌우 수행하기.

    블랙홀은 뭐지? 이해 게임 끝
    빈곳은 뭐지? 이해  시작점.
        블럭에서 시작할 수 이있나?
        단, 블록, 웜홀 또는 블랙홀이 있는 위치에서는 출발할 수 없다.
    블럭은 튕기는 곳인가? Move방향과 Block 타입에 따라 맞다. 방향 전환
    웜홀은 링킹되어 있나? 맞다. 태그한 위치로 이동한다.
        방향 유지.
    블럭 6개로 Pos 반환

    핀볼판 모양
    -1 ~ 10 사이 정수
    Scanf
    t 결과 출력

    공이 튀긴 횟수. 방향 변경 횟수가 곧 점수

    공의 초기 위치
    공의 위치, 공이 Forward하는 방향 두가지 정보.
    Finish 조건

    공의 위치 Input. bool True False


    가 아니라 인접 리스트로
    1. 아주 짧게 붙어있는 블럭도 작동 가능함
    2. 폐쇠된 위치
        블럭이면 반드시 1
        블랙홀은 반드시 0
*/

/////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#define NMAX 100
#define X second
#define Y first

using namespace std;

typedef pair<int, int> pii;

int TEST_CASE;
set<pii> EMPTY_POS;
vector<pii> WHOLE[11];
int T;
int N;
int HIT_CNT = 0;
int MAX_CNT = 0;
pii MAX_POS = {0, 0};

pii MV[4]{
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0},
};
bool BACK_TRACK = false;
pii BALL_CUR_POS = {0, 0};
pii BALL_MV_DIR = {0, 0};

pii WarpPos(pii &curPos, int v)
{
	for (const auto &p : WHOLE[v])
	{
		if (curPos.X == p.X && curPos.Y == p.Y)
			continue;
		return p;
	}
	return {-1, -1};
}

bool IsBound(pii pos)
{
	if (!(0 <= pos.Y && pos.Y <= N + 1))
		return false;
	if (!(0 <= pos.X && pos.X <= N + 1))
		return false;
	return true;
}

void MoveToward(pii &curPos, pii &mvDir)
{
	curPos = {
	    curPos.Y + mvDir.Y,
	    curPos.X + mvDir.X};
}

pii GetNxtDir(const pii &curDir, int blockType)
{
	pii nxtDir = {999, 999};
	switch (blockType)
	{
	case 1: {
		if (curDir.Y == MV[0].Y && curDir.X == MV[0].X)
		{
			nxtDir = MV[2];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[1].Y && curDir.X == MV[1].X)
		{
			nxtDir = MV[3];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[2].Y && curDir.X == MV[2].X)
			nxtDir = MV[1];
		else if (curDir.Y == MV[3].Y && curDir.X == MV[3].X)
			nxtDir = MV[0];
		break;
	}
	case 2: {
		if (curDir.Y == MV[0].Y && curDir.X == MV[0].X)
		{
			nxtDir = MV[2];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[1].Y && curDir.X == MV[1].X)
			nxtDir = MV[0];
		else if (curDir.Y == MV[2].Y && curDir.X == MV[2].X)
			nxtDir = MV[3];
		else if (curDir.Y == MV[3].Y && curDir.X == MV[3].X)
		{
			nxtDir = MV[1];
			BACK_TRACK = true;
		}
		break;
	}
	case 3: {
		if (curDir.Y == MV[0].Y && curDir.X == MV[0].X)
			nxtDir = MV[3];
		else if (curDir.Y == MV[1].Y && curDir.X == MV[1].X)
			nxtDir = MV[2];
		else if (curDir.Y == MV[2].Y && curDir.X == MV[2].X)
		{
			nxtDir = MV[0];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[3].Y && curDir.X == MV[3].X)
		{
			nxtDir = MV[1];
			BACK_TRACK = true;
		}
		break;
	}
	case 4: {
		if (curDir.Y == MV[0].Y && curDir.X == MV[0].X)
			nxtDir = MV[1];
		else if (curDir.Y == MV[1].Y && curDir.X == MV[1].X)
		{
			nxtDir = MV[3];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[2].Y && curDir.X == MV[2].X)
		{
			nxtDir = MV[0];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[3].Y && curDir.X == MV[3].X)
			nxtDir = MV[2];
		break;
	}
	case 5: {

		if (curDir.Y == MV[0].Y && curDir.X == MV[0].X)
		{
			nxtDir = MV[2];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[1].Y && curDir.X == MV[1].X)
		{
			nxtDir = MV[3];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[2].Y && curDir.X == MV[2].X)
		{
			nxtDir = MV[0];
			BACK_TRACK = true;
		}
		else if (curDir.Y == MV[3].Y && curDir.X == MV[3].X)
		{
			nxtDir = MV[1];
			BACK_TRACK = true;
		}
		break;
	}
	default:
		break;
	}

	return nxtDir;
}

bool CheckCurTile(pii &curPos, pii &mvDir, int tileType)
{
	switch (tileType)
	{
	case -1: {

		return false;
	}
	case 0: {

		return true;
	}
	case 1:
	case 2:
	case 3:
	case 4:
	case 5: {

		HIT_CNT++;
		mvDir = GetNxtDir(mvDir, tileType);

		return true;
	}
	case 6:
	case 7:
	case 8:
	case 9:
	case 10: {

		curPos = WarpPos(curPos, tileType);
		return true;
	}
	default:
		return false;
	}
	return false;
}

void PRINT_MAP(int map[NMAX + 2][NMAX + 2])
{
	for (int i = 0; i < N + 2; i++)
	{
		for (int j = 0; j < N + 2; j++)
			printf("%3d ", map[i][j]);
		printf("\n");
	}
}

void PRINT_CUR_POS_ON_MAP(int map[NMAX + 2][NMAX + 2])
{
	for (int i = 0; i < N + 2; i++)
	{
		for (int j = 0; j < N + 2; j++)
			printf("%3c ", (i == BALL_CUR_POS.Y && j == BALL_CUR_POS.X) ? 'X' : (map[i][j] + 48));
		printf("\n");
	}
}

int main(int argc, char **argv)
{

	// freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (TEST_CASE = 1; TEST_CASE <= T; ++TEST_CASE)
	{
		int MAP[NMAX + 2][NMAX + 2] = {0};
		pii INIT_POS;
		for (int i = 0; i < 11; i++)
			WHOLE[i].clear();
		EMPTY_POS.clear();

		scanf("%d", &N);
		for (int i = 0; i < N + 2; i++)
		{
			MAP[0][i] = 5;
			MAP[N + 1][i] = 5;
		}
		for (int i = 0; i < N + 2; i++)
		{
			MAP[i][0] = 5;
			MAP[i][N + 1] = 5;
		}

		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 1; j < N + 1; j++)
			{
				scanf("%d", &MAP[i][j]);
				if (MAP[i][j] >= 6)
					WHOLE[MAP[i][j]].push_back({i, j});
				if (MAP[i][j] == 0)
					EMPTY_POS.insert({i, j});
			}
		}

		if (EMPTY_POS.empty())
		{
			printf("%d 0\n", TEST_CASE);
			continue;
			MAX_CNT = 0;
		}
		for (const auto &epos : EMPTY_POS)
		{
			for (int mvIdx = 0; mvIdx < 4; mvIdx++)
			{
				INIT_POS = BALL_CUR_POS = epos;
				BALL_MV_DIR = MV[mvIdx];
				bool BLACK_HOLE = false;
				while (true)
				{
					bool movable = IsBound(BALL_CUR_POS);
					if (!movable)
						break;

					MoveToward(BALL_CUR_POS, BALL_MV_DIR);

					const int curTileType = MAP[BALL_CUR_POS.Y][BALL_CUR_POS.X];

					bool BLACK_HOLE = CheckCurTile(BALL_CUR_POS, BALL_MV_DIR, curTileType);
					if (!BLACK_HOLE)
						break;
					if (BACK_TRACK)
						break;

					if (INIT_POS.Y == BALL_CUR_POS.Y && INIT_POS.X == BALL_CUR_POS.X)
						break;
					if (INIT_POS.Y == BALL_CUR_POS.Y && INIT_POS.X == BALL_CUR_POS.X)
						break;
				}
				int tempCnt = (BACK_TRACK) ? ((HIT_CNT - 1) * 2 + 1) : HIT_CNT;
				if (MAX_CNT < tempCnt)
				{
					MAX_CNT = tempCnt;
					MAX_POS = epos;
				}
				HIT_CNT = 0;
				BACK_TRACK = false;
			}
		}
		printf("#%d %d\n", TEST_CASE, MAX_CNT);
		// printf("{%d %d}\n", MAX_POS.Y, MAX_POS.X); // DEBUG

		MAX_CNT = 0;
	}
	return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}