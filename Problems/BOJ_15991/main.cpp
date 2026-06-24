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

const ll MOD = 1e9 + 9;
int N;
ll DP[101010] = {0,};

void HandleInput(istream &ins)
{
	ins >> N;
	vector<ll> q;
	ll mx = -MOD;
	while(N--) {
		ll inNum; ins >> inNum;
		q.push_back(inNum);
		mx = max(mx, inNum);
	}
	DP[0] = 1; DP[1] = 1; DP[2] = 2; DP[3] = 2; DP[4] = 3; DP[5] = 3; DP[6] = 6;
	for(int i = 7; i <= mx; ++i) {
		DP[i] = (DP[i - 2] + DP[i - 4] + DP[i - 6]) % MOD;
	}

	for(size_t i = 0; i < q.size(); i++) {
		cout << DP[q[i]] << '\n';
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
