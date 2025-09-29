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

const ll INF = 1e9 + 9;
ll DP[1010101] = {0,};
int T;

void HandleInput(istream &ins)
{
	ins >> T;
	vector<int> commands;
	int mx = -INF;
	while(T--) {
		int inNum; ins >> inNum;
		commands.push_back(inNum);
		mx = max(mx, inNum);
	}
	DP[1] = 1;
	DP[2] = 2;
	DP[3] = 4;
	DP[4] = 7;
	DP[5] = 13;
	DP[6] = 24;
	DP[7] = 44;
	DP[8] = 81;
	DP[9] = 149;
	DP[10] = 274;

	for(ll i = 11; i <= mx; i++) {
		DP[i] = (DP[i-1] + DP[i-2] + DP[i-3]) % INF;
	}
	for(auto& e : commands) {
		cout << DP[e] << '\n';
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
