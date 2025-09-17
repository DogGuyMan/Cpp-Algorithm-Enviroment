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
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ull, ull> pullll;
typedef tuple<int, int, int> tiii;

// 부분 증가 수열을 사용하면 될듯?
// Prioirty Queue & DFS 

ull SUM = 0;
int N;
ull A[505050] = {0,};

struct compare {
	bool operator()(const pullll& lhs, const pullll& rhs) {
		if(lhs.X == rhs.X)
			return lhs.Y < rhs.Y;
		return lhs.X > rhs.X;
	}
};

priority_queue<pullll, vector<pullll>, compare> PQ; 

void HandleInput(istream &ins)
{
	ins >> N;
	for(int i = 1; i <= N; i++) {
		ins >> A[i];
		PQ.push({i, A[i]});
	}
	ull idxWall = 0;
	while(!PQ.empty()) {
		pullll cur = PQ.top(); PQ.pop();
		if(A[cur.Y] < cur.X) continue;
		if(idxWall > cur.Y) continue;
		ull mul = cur.Y - idxWall;
		mul *= cur.X;
		SUM += mul;
		idxWall = cur.Y;
		if(idxWall >= N) break;
	}

	cout << SUM << '\n';
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
