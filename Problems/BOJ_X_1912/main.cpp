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

const int MAX = 1e5*1e3;

// D는 어떻게 나온걸까?
// A는 어떻게 나온걸까?

int A[101010] = {0,};
int DP[101010] = {0,};

void HandleInput(istream &ins)
{
	int N; ins >> N;
	int mx = -MAX;
	FOR(i, 1, N+1) { ins >> A[i]; }
	FOR(i, 1, N+1) { 
		DP[i] = max(0 ,DP[i-1]) + A[i]; 
		mx = max(mx, DP[i]);
	}
	cout << mx << '\n';
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
