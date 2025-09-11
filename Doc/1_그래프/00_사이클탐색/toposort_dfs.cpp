#include <bits/stdc++.h>
using namespace std;

constexpr int YET = 0;
constexpr int ENTERING = 1;
constexpr int VISITED = 2;

const int V_MAX = 32323;
int N, M; 
vector<int> COLOR(V_MAX);
vector<int> G[V_MAX];
vector<int> BACK_TRACK;
bool IS_CYCLE = false;

void DFS(int cur) {
	COLOR[cur] = ENTERING;
	for(auto& nxt : G[cur]) {
		if(IS_CYCLE) return;
		if(COLOR[nxt] == YET)  DFS(nxt);
		if(COLOR[nxt] == ENTERING) { IS_CYCLE = true; return; }
	}
	BACK_TRACK.push_back(cur);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> N >> M;
	for(int i = 1; i <= M; i++) {
		int s, e; cin >> s >> e;
		G[s].push_back(e);
	}
	for(int i = 1; i <= N; i++) {
		if(IS_CYCLE) return;
		if(!COLOR[i]) DFS(i);
	}
	reverse(BACK_TRACK.begin(), BACK_TRACK.end());
	for(auto& e : BACK_TRACK) cout << e << ' ';
}