#include <bits/stdc++.h>
using namespace std;

const int V_MAX = 32323;
int N, M;
vector<int> IN_DEG(V_MAX);
vector<int> G[V_MAX];
vector<int> TRACK;

void P0_Queue_Initialize(queue<int>& q) {
	for(int i = 1; i <= M; i++) {
		int s, e; cin >> s >> e;
		G[s].push_back(e);
		IN_DEG[e]++;
	}

	for(int i = 1; i <= N; i++) {
		if(!IN_DEG[i]) q.push(i);
	}
}

void P1_Add_Answer(int cur, queue<int>& q) {
	q.pop();
	TRACK.push_back(cur);
}

void P2_HandleNext(int cur, queue<int>& q) {
	for(auto& nxt : G[cur]) {
		if(!--IN_DEG[nxt])
			q.push(nxt);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> M;	
	queue<int> q;
	P0_Queue_Initialize(q);

	while(!q.empty()) {
		int cur = q.front();
		P1_Add_Answer(cur, q);
		P2_HandleNext(cur, q);
	}
}