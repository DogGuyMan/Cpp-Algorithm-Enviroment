#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int T;
int V_CNT, E_CNT;
const int MAX_V = 255;

int G[MAX_V][MAX_V] = {{0,},};
bool IS_VISIT[MAX_V] = {0,};
vector<int> BACK_TRACK;

void ResetState() {
	for(int i = 0; i < MAX_V; i++) {
		IS_VISIT[i] = 0;
		for(int j = 0; j < MAX_V; j++) {
			G[i][j] = 0;
		}
	}
	BACK_TRACK.clear();
}

void DFS(int cur) {
	IS_VISIT[cur] = true;
	for(int nxt = 1; nxt <= V_CNT; nxt++) {
		if(G[cur][nxt] == 0) continue;;
		if(IS_VISIT[nxt]) continue;
		DFS(nxt);
	}
	BACK_TRACK.push_back(cur);
}

void TopoSort(int t, int startV) {
	// DFS ALL
	
	DFS(startV);
	
	// DAG 체크
	// ...
	cout << "#" << t << ' ';
	for(auto& e : BACK_TRACK) {
		cout << e << ' ';
	} cout << '\n';
}

void HandleInput(istream& ins) {
	ins >> T;
	for(int t = 1; t <= T; t++) {
		ResetState();
		ins >> V_CNT >> E_CNT;
		int startV; ins >> startV;
		for(int i = 0; i < E_CNT; i++) {
			int from, to;
			ins >> from >> to;
			G[to][from] = 1;
		}
		TopoSort(t, startV);
	}
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

int main(int argc, const char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        HandleQuery(args[1]);
    }
}
