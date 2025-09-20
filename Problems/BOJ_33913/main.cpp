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
typedef tuple<int, int, int> tiii;

const ll MOD = 1e9+7;
int N;


ull DQPow(ull a, ull e) {
	if(e == 0) return 1;
	if(e == 1) return a;
	ull x = DQPow(a, e>>1);
	ull evenRes = (x * x) % MOD;
	if((e % 2) == 0)
		return evenRes;
	return (evenRes * a) % MOD;
}

ull ANS = 0;

void HandleInput(istream &ins)
{
	ins >> N;
	ll INV2 = 500000004;
	// for(ll i = 1; i <= MOD; i++) {
	// 	if(((2*i)% MOD) == 1) {
	// 		INV2 = i;
	// 		break;
	// 	}
	// }
	ull a = DQPow(26, N);
	ull b = DQPow(22, N);
	ull temp = ((a + b) % MOD);
	cout << (temp * INV2) % MOD << '\n';
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
