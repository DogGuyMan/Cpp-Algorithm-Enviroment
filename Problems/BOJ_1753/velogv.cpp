#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#define Y first
#define X second

using namespace std;
typedef pair<int, int> pii;

struct ADJE
{
	int to, w;

	bool operator<(const ADJE &rhs) const
	{
		return w > rhs.w;
	}
};

const int INF = 1e9 + 7;
const int VMAX = 20202;
int V, E, K;

vector<pii> G[VMAX];
int DIST[VMAX] = {
    0,
};

void Dijk()
{
	DIST[K] = 0;
	priority_queue<ADJE, vector<ADJE>> pq;
	pq.push({K, 0});
	while (!pq.empty())
	{
		int mn = INF;
		ADJE popped = pq.top();
		pq.pop();
		int now = popped.to;
		if (popped.w > DIST[now])
			continue;
		for (auto &e : G[now])
		{
			int nxt = e.Y;
			if (DIST[nxt] > DIST[now] + e.X)
			{
				DIST[nxt] = DIST[now] + e.X;
				pq.push({nxt, DIST[nxt]});
			}
		}
	}
}

int main()
{
	cin >> V >> E >> K;
	fill(DIST, DIST + (V + 1), INF);
	for (int i = 1; i <= E; i++)
	{
		int from, to, w;
		cin >> from >> to >> w;
		G[from].push_back({to, w});
	}
	Dijk();
	for (int i = 1; i <= V; i++)
	{
		if (DIST[i] == INF)
			cout << "INF" << '\n';
		else
			cout << DIST[i] << '\n';
	}
}
