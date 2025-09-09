#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);
#define Y first
#define X second
typedef vector<vector<int>> imatrix;
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
const int V_MAX = 1010;
int N, M;

void BFSKahn(istream& ins) {

	vector<int> G[V_MAX];
	vector<int> IN_DEG;
	bool HAS_EDGE[V_MAX][V_MAX] = { {false,} };

	ins >> N >> M;
	int singers[V_MAX] = {
	    0,
	};
	IN_DEG = vector<int>(N+1, 0);
	for (int i = 0; i < M; i++)
	{
		int pd;
		ins >> pd;
		for (int j = 0; j < pd; j++)
		{
			ins >> singers[j];
		}
		for (int j = 0; j < pd - 1; j++)
		{
			int k = j + 1;
			int from = singers[j];
			int to = singers[k];
			if(!HAS_EDGE[from][to]) {
				G[from].push_back(to);
				IN_DEG[to]++;
				HAS_EDGE[from][to] = true;
			}
		}
		fill(singers, singers + V_MAX, 0);
	}

	// for(int i = 1; i <= N; i++) {	// DEBUG
		// cout << i << "-IN_DEG : " << IN_DEG[i] << '\n';	// DEBUG
	// }	// DEBUG

	queue<int> q;
	for(int i = 1; i <= N; i++) {
		if(!IN_DEG[i])
			q.push(i);
	}

	vector<int> res;

	while(!q.empty()) {
		int cur = q.front(); q.pop();
		res.push_back(cur);
		for(auto& nxt : G[cur]) {
			IN_DEG[nxt]--;
			if(!IN_DEG[nxt])
				q.push(nxt);
		}
	}

	// cout << "res.size() : "<< res.size() << '\n'; // DEBUG

	if(res.size() != N) {
		cout << 0 << '\n';
		return;
	}

	for(auto& e : res) cout << e << '\n';
	return;
}

constexpr char YET = 0;
constexpr char ENTERING = 1;
constexpr char VISITED = 2;

void DFS(int cur, 
	vector<char>& color, const imatrix& graph, vector<int>& backtrack,
	bool& isCycle) 
{
	color[cur] = ENTERING;

	for(auto& nxt : graph[cur]) {
		if(color[nxt] == YET) DFS(nxt, color, graph, backtrack, isCycle);
		else if(color[nxt] == ENTERING) {isCycle = true; return;}
		if(isCycle) return;
	}
	color[cur] = VISITED;
	backtrack.push_back(cur);
}

void DFSColoring(istream &ins) {
	ins >> N >> M;
	imatrix G(N+1);
	vector<char> COLOR(N+1, YET);
	vector<int> BACK_TRACK;
	bool HAS_EDGE[V_MAX][V_MAX] = {false};

	for(int i = 1; i <= M; i++) {
		int pd; ins >> pd;
		vector<int> singers(pd);
		for(int j = 0; j < pd; j++) ins >> singers[j];
		for(int j = 1; j < pd; j++) {
			int from = singers[j-1];
			int to = singers[j];
			if(!HAS_EDGE[from][to]) {
				HAS_EDGE[from][to] = true;
				G[from].push_back(to);
			}
		}
	}

	//for(int i = 1; i <= N; i++) {	// DEBUG
	//	cout << i << " : ";	// DEBUG
	//	for(auto& v : G[i]) {	// DEBUG
	//		cout << v << ' ';	// DEBUG
	//	}	// DEBUG
	//	cout << '\n';	// DEBUG
	//}	// DEBUG

	bool isCycle = false;
	for(int i = 1; i <= N; i++) {
		if(isCycle) break;
		if(COLOR[i] == YET)
			DFS(i, COLOR, G, BACK_TRACK, isCycle);
	}

	if(isCycle) {cout << 0 << '\n'; return;}

	reverse(BACK_TRACK.begin(), BACK_TRACK.end());

	for(auto& e : BACK_TRACK) {
		cout << e << '\n';
	} cout << '\n';
	return;
}

void HandleInput(istream &ins)
{
	DFSColoring(ins);
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
