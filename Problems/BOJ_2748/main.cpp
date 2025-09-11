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
typedef long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

ull DP[1010] = {0,};

void HandleInput(istream &ins)
{
	int N; ins >> N;
	DP[0] = 0; DP[1] = 1; DP[2] = 1;
	for(int i = 3; i <= N+17; i++) {
		DP[i] = DP[i-1] + DP[i-2];
	}
	
	// for(int i = 0; i <= 90; i++) { // DEBUG
	// 	cout << i << ":"<< DP[i] << '\n'; // DEBUG
	// } // DEBUG

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
