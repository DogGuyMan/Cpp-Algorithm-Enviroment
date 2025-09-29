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

const int INF = 1e9 + 7;
int N; 
int DP[101010] = {0,};

void HandleInput(istream &ins)
{
	memset(DP, -1, sizeof(int) * 101010);
	ins >> N;
	for(int i = 2; i <= N; i+=2) { DP[i] = i/2; }
	for(int i = 5; i <= N; i+=5) { DP[i] = i/5; }
	for(int i = 5; i <= N; ++i) {
		int sub2 = (DP[i-2] < 0) ? INF : DP[i-2];
		int sub5 = (DP[i-5] < 0) ? INF : DP[i-5];
		if(sub2 == INF && sub5 == INF) continue;
		DP[i] = min(sub2, sub5) + 1;
	}
	cout << DP[N] << '\n';
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
