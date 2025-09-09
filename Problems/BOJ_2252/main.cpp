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

const int V_MAX = 32001;

int V, E;
vector<int> G[V_MAX];
vector<int> IS_VISIT(V_MAX);
vector<int> BACK_TRACK;

void DFS(int sV){
	IS_VISIT[sV] = true;
	for(auto& nxt : G[sV]){
		if(!IS_VISIT[nxt])
			DFS(nxt);
	}
	BACK_TRACK.push_back(sV);
}

void HandleInput(istream &ins)
{
	ins >> V >> E;
	for(int i = 1;i <= E; i++)
	{
		int a, b;
		ins >> a >> b;
		G[a].push_back(b);
	}
	
	for(int i = 1; i<=V; i++){
		if(!IS_VISIT[i]){
			DFS(i);
		}
	}
	reverse(BACK_TRACK.begin(), BACK_TRACK.end());
	
	for(auto& e : BACK_TRACK){
		cout << e << ' ';
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
