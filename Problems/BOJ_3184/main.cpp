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

int R, C;
char G[255][255] 	= {{0},};
bool IS_VISIT[255][255] = {{0},};
vector<pii> VPOS;
pii ANS = {0,0};

const pii MV[4] {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

inline bool isBound(const pii& pos) {
	if(pos.Y < 0 || pos.Y >= R) return false;
	if(pos.X < 0 || pos.X >= C) return false;
	return true;
}
void BFS(const pii& cur, int& lamb, int& wolf) {
	queue<pii> q;
	q.push(cur);
	while(!q.empty()) {
		pii ppos = q.front(); q.pop();
		if(IS_VISIT[ppos.Y][ppos.X] == true) continue;
		IS_VISIT[ppos.Y][ppos.X] = true;
		if(G[ppos.Y][ppos.X] == 'v') ++wolf;
		if(G[ppos.Y][ppos.X] == 'o') ++lamb;
		for(int i = 0; i < 4; ++i) {
			pii npos = {ppos.Y + MV[i].Y, ppos.X + MV[i].X};
			if(!isBound(npos)) continue;
			if(G[npos.Y][npos.X] == '#') continue;
			if(IS_VISIT[npos.Y][npos.X] == true) continue;
			q.push(npos);
		}
	}
}

void HandleInput(istream &ins)
{
	ins >> R >> C;
	FOR(i, 0, R){
		string tmp;
		ins >> tmp;
		FOR(j, 0, C) {
			G[i][j] = tmp[j];
			if(G[i][j] == 'v') VPOS.push_back({i, j});
			if(G[i][j] == 'o') VPOS.push_back({i, j});
		}
	}
	for(const auto& pos : VPOS) {
		int lamb = 0, wolf = 0;
		BFS(pos, lamb, wolf);
		if(lamb > wolf) ANS.Y += lamb;
		else ANS.X += wolf;
	}
	cout << ANS.Y << ' ' << ANS.X << '\n';
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
