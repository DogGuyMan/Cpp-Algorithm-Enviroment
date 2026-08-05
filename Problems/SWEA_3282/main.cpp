#include <cstdio>
#include <cstring>
#include <array>
#include <algorithm>

#ifdef DEBUG_DP
#include <map>
#include <vector>
#include <cstdlib>
#endif

#define VOL 0
#define VAL 1
#define INF 1e9

using namespace std;

int N, K, ANS;
// DP[아이템 1..i 까지][부피를 정확히 v 사용] = 최대 가치
static int DP[101][101010];
static array<int, 2> STUFFS[101] = {};

// ══════════════════════════════════════════════════════════
//  제출용 DP
// ══════════════════════════════════════════════════════════
int SolveDP()
{
	for (int i = 0; i <= N; ++i)
		for (int j = 0; j <= K; ++j)
			DP[i][j] = -INF;
	DP[0][0] = 0;

	int best = 0;
	for (int curDepth = 1; curDepth <= N; ++curDepth)
	{
		for (int curVol = 0; curVol <= K; ++curVol)
		{
			int& CUR_DP = DP[curDepth][curVol];
			int& PRV_DP = DP[curDepth - 1][curVol];
			int PRV_VOL = curVol - STUFFS[curDepth][VOL];
			CUR_DP = PRV_DP;
			if (PRV_VOL >= 0 && DP[curDepth - 1][PRV_VOL] != -INF)
				CUR_DP = max(CUR_DP, DP[curDepth - 1][PRV_VOL] + STUFFS[curDepth][VAL]);
			best = max(best, CUR_DP);
		}
	}
	return best;
}

// ══════════════════════════════════════════════════════════
//  디버그 하네스 (제출 시 컴파일되지 않음)
//  빌드:  clang++ -DDEBUG_DP --std=c++17 main.cpp -o main
// ══════════════════════════════════════════════════════════
#ifdef DEBUG_DP

// 상태 서명 (depth, vol) -> 그 상태에 도달한 가치들
static map<pair<int, int>, vector<int>> STATE_LOG;
static long long BF_CALLS;

// ── (1) 상태 기록용 완탐 ──────────────────────────────────
void BFLog(int curDepth, int curVal, int curVol)
{
	STATE_LOG[{curDepth, curVol}].push_back(curVal);
	++BF_CALLS;
	if (curDepth > N) return;

	BFLog(curDepth + 1, curVal + STUFFS[curDepth][VAL], curVol + STUFFS[curDepth][VOL]);
	BFLog(curDepth + 1, curVal, curVol);
}

// ── (2) 교차검증용 완탐 (로그 없이 답만) ──────────────────
static int BF_BEST;
void BFPlain(int curDepth, int curVal, int curVol)
{
	if (curVol > K) return;
	if (curDepth > N) { BF_BEST = max(BF_BEST, curVal); return; }

	BFPlain(curDepth + 1, curVal + STUFFS[curDepth][VAL], curVol + STUFFS[curDepth][VOL]);
	BFPlain(curDepth + 1, curVal, curVol);
}

int SolveBF()
{
	BF_BEST = 0;
	BFPlain(1, 0, 0);
	return BF_BEST;
}

// ── (3) 입력 되뱉기 + 불변량 검산 ─────────────────────────
void DumpInput()
{
	int sumVol = 0, sumVal = 0;
	printf("[입력] N=%d  K=%d\n", N, K);
	for (int i = 1; i <= N; ++i)
	{
		printf("       item %2d : vol=%3d  val=%3d\n", i, STUFFS[i][VOL], STUFFS[i][VAL]);
		sumVol += STUFFS[i][VOL];
		sumVal += STUFFS[i][VAL];
	}
	printf("[검산] 전부 선택하면 vol=%d val=%d 여야 함\n"
	       "       -> 아래 표의 depth=%d 마지막 행과 일치하는지 확인\n\n",
	       sumVol, sumVal, N + 1);
}

// ── (4) 상태별 그룹 로그: 점화식이 여기서 보인다 ──────────
void DumpStates()
{
	STATE_LOG.clear();
	BF_CALLS = 0;
	BFLog(1, 0, 0);

	printf("depth  vol | 도달 | 값들            | 집계  비고\n");
	printf("-----------+------+-----------------+------------------------\n");

	int forkCnt = 0;
	for (auto& entry : STATE_LOG)
	{
		const int d = entry.first.first;
		const int v = entry.first.second;
		vector<int>& vals = entry.second;

		int mx = *max_element(vals.begin(), vals.end());
		int mn = *min_element(vals.begin(), vals.end());

		char buf[128];
		int n = 0;
		buf[0] = '\0';
		for (size_t k = 0; k < vals.size() && n < 90; ++k)
			n += snprintf(buf + n, sizeof(buf) - n, "%d ", vals[k]);

		printf("  %2d  %3d  | %3d  | %-15s |  %3d %s%s\n",
		       d, v, (int)vals.size(), buf, mx,
		       (v > K) ? "[용량초과] " : "",
		       (mx != mn) ? "* 값이 갈림 -> max 채택" : "");

		if (mx != mn) ++forkCnt;
	}

	printf("\n[요약] 호출 %lld회 -> 고유 상태 %zu개 (압축비 %.2fx), 값이 갈린 상태 %d개\n",
	       BF_CALLS, STATE_LOG.size(), (double)BF_CALLS / (double)STATE_LOG.size(), forkCnt);
	printf("       압축비가 1.0에 가까우면 DP 이득이 없다 = 상태 정의를 다시 볼 것\n");
	printf("       '값이 갈린' 상태가 0개면 집계 함수(max)가 하는 일이 없다\n\n");
}

// ── (5) 완탐을 오라클로: 작은 무작위 입력 대조 ────────────
void CrossCheck(int trials)
{
	const int savedN = N, savedK = K;
	static array<int, 2> savedStuffs[101];
	copy(STUFFS, STUFFS + 101, savedStuffs);

	srand(12345);
	int bad = 0;
	for (int t = 0; t < trials; ++t)
	{
		N = 1 + rand() % 10;
		K = 1 + rand() % 25;
		for (int i = 1; i <= N; ++i)
		{
			STUFFS[i][VOL] = 1 + rand() % 10;
			STUFFS[i][VAL] = 1 + rand() % 10;
		}

		const int bf = SolveBF();
		const int dp = SolveDP();
		if (bf != dp)
		{
			printf("[불일치] BF=%d  DP=%d\n", bf, dp);
			DumpInput();
			if (++bad >= 3) break;
		}
	}
	if (bad == 0)
		printf("[교차검증] 무작위 %d회 대조 전부 일치 (BF == DP)\n\n", trials);

	N = savedN;
	K = savedK;
	copy(savedStuffs, savedStuffs + 101, STUFFS);
}

#endif // DEBUG_DP

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		scanf("%d %d", &N, &K);
		for (int i = 1; i <= N; ++i)
			scanf("%d %d", &STUFFS[i][VOL], &STUFFS[i][VAL]);

#ifdef DEBUG_DP
		if (tc == 1)
		{
			DumpInput();
			DumpStates();
			CrossCheck(5000);
		}
#endif

		ANS = SolveDP();
		printf("#%d %d\n", tc, ANS);
	}
	return 0;
}
