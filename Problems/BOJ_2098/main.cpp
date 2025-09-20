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

const int SET_CAP = (1<<16) + 1;
const int INF = 1e9+7;

int N;
int G[16][16] = {{0,}};
int endPos = 0;
int DP[16][SET_CAP] {0,};

inline int GetFill() {
	return (1 << N)-1;
}
inline bool CheckFill(const int &state) {
	return state == GetFill();
}

inline bool CheckVisited(const int& nxt, const int& state) {
	return ( (1<<nxt) & state ) > 0;
}

int TSP(const int& cur, const int& curState) {
	if (CheckFill(curState)) {
		if(G[cur][0] != 0) {
			return  G[cur][0];
		}
		return INF;
	}
	int& bestCur = DP[cur][curState];
	
	if(bestCur != 0)
		return bestCur;

	bestCur = INF;
	for (int nxt=1; nxt<N; ++nxt) { // 0 제외
		if(G[cur][nxt] == 0 || (CheckVisited(nxt, curState))) continue;
		int nxtState = (curState | 1<<nxt);
		bestCur = min(bestCur, TSP(nxt, nxtState) + G[cur][nxt]);
	}
	return bestCur;

}

void HandleInput(istream &ins)
{
	ins >> N;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			ins >> G[i][j];
		}
	}
	TSP(0, 1<<0);
	cout << DP[0][1] << '\n';
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
