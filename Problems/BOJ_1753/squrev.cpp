#include <iostream>
#include <vector>
#include <algorithm>
#define X second
#define Y first
using namespace std;
typedef pair<int, int> pii;

const int INF = 1e9+7;
int V, E;

vector<pii> G[20202];
unsigned int DIST[20202] = {0,};
bool IS_VISIT[20202] = {0,};
int S;
void DIJK(){
	int now = S;

	for(int i = 1; i <= V; i++){
		IS_VISIT[now] = true;
		// update dest
		for(auto& e : G[now]){
			int nxt = e.Y;
			if(!IS_VISIT[nxt]){
				DIST[nxt] = min(DIST[nxt], DIST[now] + e.X);
			}
		}
		
		// get shortest edge in start
		int mn = INF; int nxtNow = -1;
		for(int j = 1; j <= V;j++)
		{
			if(!IS_VISIT[j] && DIST[j] < mn){
				mn = DIST[j];
				nxtNow = j;
			}
		}
		if(nxtNow == -1) break;
		now = nxtNow;
	}
}

int main(){
	cin >> V >>E;
	cin >> S;
	
	fill(DIST + 0, DIST + (V+1), INF);
	
	DIST[S] = 0;
	
	for(int i = 1; i <= E; i++){
		int from, to, w;
		cin >> from >> to >> w;
		G[from].push_back({to, w});
	}
	
	DIJK();
	for(int i =1; i <= V; i++){
		if(DIST[i] >= INF) {
			cout << "INF" << '\n';
			continue;
		}
		cout << DIST[i] << '\n';
	}
}
