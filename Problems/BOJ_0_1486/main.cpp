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

struct E {
	pii cur; int w; int usedTime;
	bool operator<(const E& rhs) const {
		return w < rhs.w;
	}
};

const char ALPHA_INTVAL = 'A';
const int INF = 1e9+7;
const int V_MAX = 25;
const pii START_POS = {0,0};
const pii MV[4] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
};
int N, M, T, D;

int G[V_MAX][V_MAX] = {0,};
int DIST[V_MAX][V_MAX] = {0,};
unordered_map<char, int> ALPHA_HASH;
const char ALPHA_SET[52] = {
	'A','B','C','D','E',
	'F','G','H','I','J',
	'K','L','M','N','O',
	'P','Q','R','S','T',
	'U','V','W','X','Y',
	'Z','a','b','c','d',
	'e','f','g','h','i',
	'j','k','l','m','n',
	'o','p','q','r','s',
	't','u','v','w','x',
	'y','z'
};

/*********************************************************************************
 
int N, M T가 gam 제한, 

절차적으로 일단 다익스트라를 구성하자.
가장 높은곳으로 
아무리 최악이더라도 'z' -'A'
(51-0)^2;
(50 + 1)(50 + 1)

2601;

그리디는 안된다.


1. 시간 제약 없이 풀기
* 제약 걸고, 순회

*********************************************************************************/


void DEBUG_G(const int (&graph)[V_MAX][V_MAX]) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(graph[i][j] >= INF) {cout  << setw(3) << "I"; continue;}
			cout << setw(3) << graph[i][j];
		}  cout << '\n';
	}
}

void HandleInput(istream &ins)
{
	ins >> N >> M >> T >> D;
	for(int i = 0; i < 52; i++) {
		ALPHA_HASH.insert({ALPHA_SET[i], i});
	}
	
	for(int i = 0; i < V_MAX; i++)
		fill(DIST[i], DIST[i] + V_MAX, INF);
		
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			char tmp; ins >> tmp;
			G[i][j] = ALPHA_HASH[tmp];
		}
	}

	priority_queue<E, vector<E>> pq;
	DIST[START_POS.Y][START_POS.X] = 0;
	pq.push({START_POS, 0, 0});

	while(!pq.empty()) {
		E poped = pq.top(); pq.pop();
		pii cur = poped.cur;
		if(DIST[cur.Y][cur.X] < poped.w) continue;
		for(auto& mv : MV) {
			pii nxt = {cur.Y + mv.Y, cur.X + mv.X};
			int nxtDist = 1;
			if(G[nxt.Y][nxt.X] > G[cur.Y][cur.X]) {
				int gap = G[nxt.Y][nxt.X] - G[cur.Y][cur.X];
				nxtDist = gap * gap;
			}
			if(DIST[nxt.Y][nxt.X] > (DIST[cur.Y][cur.X] + nxtDist) && nxtDist <= T) {
				pq.push({nxt, nxtDist, });
				DIST[nxt.Y][nxt.X] = (DIST[cur.Y][cur.X] + nxtDist);
			}
		}
	}

	DEBUG_G(DIST); // DEBUG
	pii mxPos = {0,0}; int mx = -INF;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) {
			if(DIST[i][j] >= INF) continue;
			if(mx < DIST[i][j]){
				mx = DIST[i][j];
				mxPos = {i, j};
			}
		}
	}
	cout << G[mxPos.Y][mxPos.X] << '\n';

	// DEBUG_G(); // DEBUG
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
