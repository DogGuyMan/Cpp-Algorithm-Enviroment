#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#define Y first
#define X second
#define H_MAX 15
#define W_MAX 12

using namespace std;
typedef pair<int, int> pii;

pii operator*(pii& lhs, const int rhs) { return {lhs.Y * rhs, lhs.X * rhs}; }
pii operator+(pii& lhs, const pii rhs) { return {lhs.Y + rhs.Y, lhs.X + rhs.X}; }
pii MV[4] { { 0,  1}, {-1,  0}, { 0, -1}, { 1,  0} };

int N, H, W;
int RES = 0;

void BF(vector<vector<int>>& shoot_orders, vector<int>& candi)
{
	if (candi.size() == N)
	{
		shoot_orders.push_back(vector<int>(candi));
		return;
	}
	for (int i = 0; i < W; i++)
	{
		candi.push_back(i);
		BF(shoot_orders, candi);
		candi.pop_back();
	}
}

// void PRINT_MAP(int map[H_MAX][W_MAX])
// {
// 	printf("{%d %d}\n", H, W);
// 	for (int i = 0; i < H; i++)
// 	{
// 		printf("%3d : ", i);
// 		for (int j = 0; j < W; j++)
// 		{
// 			printf("%3d ", map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

void PushColumn(int map[H_MAX][W_MAX], int break_map[H_MAX][W_MAX], int c)
{
	int writeRow = H - 1; // 바닥부터 채워 올라간다
	for (int readRow = H - 1; readRow >= 0; --readRow)
	{
		// 부서졌거나(break) 빈 칸(0)이면 버린다
		if (break_map[readRow][c] || map[readRow][c] == 0) continue;
		map[writeRow--][c] = map[readRow][c]; // 살아남은 벽돌만 아래로 끌어내림
	}
	while (writeRow >= 0) // 위쪽 남은 칸은 0
		map[writeRow--][c] = 0;
}

void BFS(int map[H_MAX][W_MAX], const vector<int>& shoot_orders)
{
	// for (auto& e : shoot_orders)
	// 	printf("%3d ", e);
	// printf("\n");

	for (const auto& col : shoot_orders)
	{
		int bmap[H_MAX][W_MAX] = {0};
		// PRINT_MAP(bmap); // DEBUG
		// printf("-----------------"); // DEBUG

		pii pos = {0, col};
		for (int i = 0; i < H; i++)
		{
			if (map[i][col] != 0) break;
			pos.Y++;
		}
		if (pos.Y >= H) continue;
		queue<pii> q;
		q.push(pos);
		while (!q.empty())
		{
			pii cur = q.front();
			q.pop();
			bmap[cur.Y][cur.X] = 1;
			if (map[cur.Y][cur.X] <= 1) continue;
			int& mul = map[cur.Y][cur.X];
			for (int mvi = 0 ; mvi < 4; mvi++)
			{
				for (int m = 1; m < mul; m++)
				{
					pii nxt = cur + (MV[mvi] * m);
					if (nxt.Y < 0 || nxt.Y >= H || nxt.X < 0 || nxt.X >= W) continue;
					if (bmap[nxt.Y][nxt.X] > 0) continue;
					q.push(nxt);
				}
			}
		}

		// printf("map\n"); // DEBUG
		// PRINT_MAP(map); // DEBUG
		// printf("-----------------"); // DEBUG
		// printf("bmap\n"); // DEBUG
		// PRINT_MAP(bmap); // DEBUG
		// printf("-----------------"); // DEBUG

		for (int c = 0; c < W; c++)
			PushColumn(map, bmap, c);

		// printf("amap\n"); // DEBUG
		// PRINT_MAP(map); // DEBUG
		// printf("-----------------"); // DEBUG

	}

	int cnt = 0;
	for (int i = 0 ; i < H; i++)
		for (int j = 0 ; j < W; j++)
			if (map[i][j] == 0) cnt++;
	RES =  max(RES, cnt);
	// printf("%3d VS %3d\n", RES, cnt);
}

int main()
{
	int TC;
	// freopen("sample.txt", "r", stdin);
	scanf("%d", &TC);
	for (int i = 1; i <= TC; i++)
	{
		int map[H_MAX][W_MAX] = {0};
		RES = 0;
		scanf("%d %d %d", &N, &W, &H);
		for (int i = 0; i < H; ++i)
			for (int j = 0; j < W; ++j)
				scanf("%d", &map[i][j]);

		bool flag = true;
		for (int i = 0 ; i < H; i++)
			for (int j = 0 ; j < W; j++)
				if (map[i][j] != 0) {flag = false; break;}

		if (flag) { printf("#%d %d\n", i, 0); continue; }

		vector<vector<int>> shootOrders;
		{
			vector<int> candi;
			BF(shootOrders, candi);
		}
		for (const auto& pts : shootOrders)
		{
			int temp[H_MAX][W_MAX] = {0};
			for (int i = 0 ; i < H; i++)
				for (int j = 0 ; j < W; j++)
					temp[i][j] = map[i][j];
			BFS(temp, pts);
			if (RES == (H * W)) break;
		}
		printf("#%d %d\n", i, (H * W) - RES);
	}
}