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
/*********************************************************************************
트리의 정점의 수 N과 루트의 번호 R, 쿼리의 수 Q가 주어진다. (2 ≤ N ≤ 105, 1 ≤ R ≤ N, 1 ≤ Q ≤ 105)

이어 N-1줄에 걸쳐, U V의 형태로 트리에 속한 간선의 정보가 주어진다. (1 ≤ U, V ≤ N, U ≠ V)

이는 U와 V를 양 끝점으로 하는 간선이 트리에 속함을 의미한다.

이어 Q줄에 걸쳐, 문제에 설명한 U가 하나씩 주어진다. (1 ≤ U ≤ N)

입력으로 주어지는 트리는 항상 올바른 트리임이 보장된다.
*********************************************************************************/
const int V_MAX = 1e5+3;

int N, R, Q;

vector<int> A[V_MAX];
int DP[V_MAX] = {0,};
bool IS_VISIT[V_MAX] = {0,};

int DFS(int cur, int prev) {
	IS_VISIT[cur] = true;
	if(A[cur].size() == 1 && A[cur][0] == prev) {
		return DP[cur] = 1;
	}
	if(DP[cur] > 0) return DP[cur];
	for(auto& c : A[cur]) {
		if(cur == prev) continue;
		if(IS_VISIT[c]) continue;
		DP[cur] += DFS(c,cur);
	}
	return DP[cur] += 1;
}

void HandleInput(istream &ins)
{
	ins >> N >> R >> Q;
	int u = 0, v= 0; 
	for(int i = 0; i < N-1; i++) {
		ins >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}

	// for(int i = 1; i <= N; i++) { // DEBUG
	// 	cout << i << " : "; // DEBUG
	// 	for(auto& c : A[i]) { // DEBUG
	// 		cout << c << ' '; // DEBUG
	// 	} cout << '\n'; // DEBUG
	// } // DEBUG
	DFS(R, 0);
	// for(int i = 1; i <= N; i++) { // DEBUG
	// 	cout << i << ": " << DP[i] << '\n'; // DEBUG
	// } // DEBUG
	while(Q--) {
		int inNum; ins >> inNum;
		// cout << inNum << '\n'; // DEBUG
		cout << DP[inNum] << '\n';
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
