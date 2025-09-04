#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int INF = 1e4 + 1;
const int MAX_V = 101;

int T;
int V_CNT, E_CNT;
int S_POS, E_POS;

struct E
{
	int vtx;
	int dist;
	bool operator<(const E &other) const
	{
		return dist > other.dist;
	}
};

struct MinComp
{
	bool operator()(const E &l, const E &r) const
	{
		return l.dist > r.dist;
	}
};

// priority_queue<E, vector<E>, MinComp> G[MAX_V];
vector<E> G[MAX_V];
int DIST[MAX_V] = {
    0,
};

void ResetState()
{
	for (int i = 0; i <= MAX_V; i++)
	{
		// cout << "i" << '\n'; // DEBUG
		// G[i] = priority_queue<E, vector<E>, MinComp>();
		G[i].clear();
		DIST[i] = INF;
	}
}

// DIJK: pq에 (vtx, distance)로 넣도록 수정
void DIJK(int start)
{
	// priority_queue uses E::operator< (현재 operator<: return dist > other.dist;)
	// -> top will be smallest dist (min-heap behavior) if operator< is defined that way.
	priority_queue<E, vector<E>> pq;
	pq.push({start, 0}); // vtx = start, dist = 0
	DIST[start] = 0;

	while (!pq.empty())
	{
		E curE = pq.top();
		pq.pop();
		// cout << curE.vtx << " " << curE.dist << '\n'; // DEBUG

		// if popped distance is greater than recorded best, skip
		if (curE.dist > DIST[curE.vtx])
			continue;

		for (int i = 0; i < (int)G[curE.vtx].size(); ++i)
		{
			const int &toV = G[curE.vtx][i].vtx;
			const int &edgeW = G[curE.vtx][i].dist;
			int newCost = curE.dist + edgeW;
			if (newCost < DIST[toV])
			{
				DIST[toV] = newCost;
				pq.push({toV, newCost}); // vtx, dist
			}
		}
	}
}

void HandleInput(istream &ins)
{
	ins >> T;
	for (int t = 1; t <= T; t++)
	{
		// cout << "START" << '\n'; // DEBUG
		ResetState();
		ins >> V_CNT >> S_POS >> E_POS;
		ins >> E_CNT;
		for (int i = 0; i < E_CNT; i++)
		{
			int from, to, adj;
			ins >> from >> to >> adj;
			G[from].push_back({to, adj});
		}
		DIJK(S_POS);
		cout << "#" << t << " " << DIST[E_POS] << '\n';
	}
}

void HandleQuery(const char *FILE_PATH)
{
	fstream fs(FILE_PATH);
	if (fs.is_open())
	{
		HandleInput(fs);
	}
}

int main(int argc, const char *args[])
{
	if (argc <= 1)
	{
		FASTIO;
		HandleInput(cin);
	}
	else
	{
		HandleQuery(args[1]);
	}
}
