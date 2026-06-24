#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for( int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int Q, I;
pii start, dest;


inline bool IS_BOUND(const pii& pos) {
	if(pos.Y < 0 || pos.Y >= I) return false;
	if(pos.X < 0 || pos.X >= I) return false;
	return true;
}

pii MV[8] = {
	{2, 1},
	{1, 2},
	{-2, 1},
	{-1, 2},
	{2, -1},
	{1, -2},
	{-2, -1},
	{-1, -2},
};

struct State {
	int cnt = 0;
	pii cur = {0,0};
};

void HandleInput(istream &ins)
{
	ins >> Q;
	while(Q--) {
		ins >> I;
		ins >> start.Y >> start.X;
		ins >> dest.Y >> dest.X;
		if(start.Y == dest.Y && start.X == dest.X) {
			cout << 0 << '\n';
			continue;
		}

		queue<State> q;
		vector<vector<bool>> isVisit(I, vector<bool>(I, false));
		q.push({0, start});
		isVisit[start.Y][start.X] = true;
		while(!q.empty()) {
			State poped = q.front(); q.pop();
			if( poped.cur.Y == dest.Y && poped.cur.X == dest.X) {
				cout << poped.cnt << '\n';
				break;
			}
			for(int i = 0; i < 8; i++) {
				pii nxt = {
					poped.cur.Y + MV[i].Y,
					poped.cur.X + MV[i].X,
				};
				if(!IS_BOUND(nxt)) continue;
				if(isVisit[nxt.Y][nxt.X]) continue;
				q.push({poped.cnt + 1, nxt});
				isVisit[nxt.Y][nxt.X] = true;
			}
		}
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
