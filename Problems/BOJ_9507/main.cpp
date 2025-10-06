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

int Q;
ull DP[70] = {0,};

ull Koong(int n) {
	if(n <= 1) return DP[n] = 1;
	if(n == 2) return DP[n] = 2;
	if(n == 3) return DP[n] = 4;
	if(DP[n] != 0) return DP[n];
	return DP[n] = Koong(n-1) + Koong(n-2) + Koong(n-3) + Koong(n-4);
}

void HandleInput(istream &ins)
{
	ins >> Q;
	queue<int> inputQ;
	int mx = -1234567890;
	while(Q--) {
		int inNum; ins >> inNum;
		inputQ.push(inNum);
		mx = max(mx, inNum);
	}
	Koong(mx);
	while(!inputQ.empty()) {
		int front = inputQ.front(); inputQ.pop();
		cout << Koong(front) << '\n';
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
