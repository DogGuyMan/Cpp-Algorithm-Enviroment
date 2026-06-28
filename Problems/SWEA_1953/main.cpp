/*
시간당 한칸 음직일 수 있음
TC 주어짐.
테케 주어짐
	세로 N
	가로 M
	맨홀 뚜겅? 시작점이 주어진다.  세로 가로 R C
	소요 시간 L
	탈주범이 있을 장소
	최대 유량? DFS하고 끝까지 이동하기. BF하는게 맞는듯.
	가만히 있을 수도 있다.
*/

#include <iostream>
#include <vector>
#include <set>
#define Y first
#define X second
using namespace std;

typedef pair<int, int> pii;
typedef vector<vector<int>> mati;

int TC;
int N, M;
int R, C;
int L;

vector<pii> PIPE[8] =
{
	{{0, 0}},
	{{0, 1}, {-1, 0}, {0, -1}, {1, 0}},
	{{-1, 0}, {1, 0}},
	{{0, 1}, {0, -1}},
	{{-1, 0}, {0, 1}},
	{{1, 0}, {0, 1}},
	{{1, 0}, {0, -1}},
	{{-1, 0}, {0, -1}},
};

bool IsBound(const mati& map, pii pos)
{
	if (pos.Y < 0 || pos.Y >= N) return false;
	if (pos.X < 0 || pos.X >= M) return false;
	return true;
}

void DFS(const mati& map, mati& is_visit, set<pii>& back_track, pii cur)
{
	int sz = back_track.size();
	if (sz > L) return;
	if (sz <= L)
	{
		// printf("btsz : %d", back_track.size());
		for (auto pos : back_track)
			is_visit[pos.Y][pos.X] = 1;
		if (sz == L) return;
	}
	back_track.insert(cur);
	int curPipe = map[cur.Y][cur.X];
	if (curPipe == 0) return;
	for (const auto& dir : PIPE[curPipe])
	{
		pii nxt = {cur.Y + dir.Y, cur.X + dir.X};
		if (nxt.Y < 0 || nxt.Y >= N || nxt.X < 0 || nxt.X >= M) continue;
		int opval = map[nxt.Y][nxt.X];
		if (opval <= 0) continue;
		bool flag = false;
		for (const auto& opDir : PIPE[opval])
		{
			pii opPos = {opDir.Y + nxt.Y, opDir.X + nxt.X};
			if (opPos == cur) {flag = true; break;}
		}
		if (!flag) continue;
		if (back_track.find(nxt) != back_track.end()) continue;

		back_track.insert(nxt);
		DFS(map, is_visit, back_track, nxt);
		back_track.erase(nxt);
	}
}

void PRINT_MAP(const mati& map)
{
	printf("----------\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%5d ", map[i][j]);
		}
		printf("\n");
	}
	printf("----------\n");
}

int main()
{
	freopen("sample.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		mati map = mati(N, vector<int>(M, 0));
		mati isVisit = mati(N, vector<int>(M, 0));
		set<pii> backTrack;
		bool flag = false;
		for (int i = 0 ; i < N; ++i)
		{
			for (int j = 0 ; j < M; ++j)
			{
				scanf("%d", &map[i][j]);
				if (map[i][j] != 0) flag = true;
			}
		}

		if (!flag || L == 1)
		{
			printf("#%d %d\n", t, 1);
			continue;
		}
		DFS(map, isVisit, backTrack, {R, C});
		// PRINT_MAP(isVisit);
		int cnt = 0;
		for (int i = 0 ; i < N; ++i)
			for (int j = 0 ; j < M; ++j)
				if (isVisit[i][j] != 0) cnt++;


		printf("#%d %d\n", t, cnt);
	}
	return 0;
}