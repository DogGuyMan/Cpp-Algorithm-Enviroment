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

const int INF = 1e9+7;
int DP[1010101] = {0,};

void HandleInput(istream &ins)
{
	int N; ins >> N;
	DP[0] = 0;  DP[1] = 0;  DP[2] = 1;  DP[3] = 1;  DP[4] = 2; 
	for(int i = 5; i <= N; i++) {
		int mn = INF;
		if(i % 3 == 0) mn = min(mn, DP[i/3] + 1);
		if(i % 2 == 0) mn = min(mn, DP[i/2] + 1);
		DP[i] = min(mn, DP[i-1] + 1);
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
	return 0;
}
