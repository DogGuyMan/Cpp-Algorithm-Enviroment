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

const int V_MAX = 33333;
int V, E;

vector<int> G[V_MAX];
vector<int> IN_DEG(V_MAX);

void HandleInput(istream &ins) {
	ins >> V >> E;
	for(int i = 1;i <= E;i++){
		int from, to;
		ins >> from >> to;
		G[from].push_back(to);
		IN_DEG[to]++;
	}
	priority_queue<int, vector<int>> pq;
	for(int i = 1; i <= V; i++){
		if(IN_DEG[i] == 0)
			pq.push(-i);
	}
	
	while(!pq.empty()){
		int poped = -pq.top(); pq.pop();
		cout << poped << ' ';
		for(auto& e : G[poped]){
			IN_DEG[e]--;
			if(IN_DEG[e] == 0)
				pq.push(-e);
		}
	}
	cout << '\n';
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
