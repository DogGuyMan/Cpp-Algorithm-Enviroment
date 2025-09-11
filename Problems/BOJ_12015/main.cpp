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

const int MAX = 1e3*1e3 + 1;
int N;
int A[MAX] = {0,};
int DP[MAX] = {0,};

void HandleInput(istream &ins)
{
	ins >> N;
	for(int i = 1; i <= N; i++) { ins >> A[i]; }
	for(int i = 1; i <= N; i++) {
		for(int j = 0; j < A[i]; j++) {
			DP[A[i]] = max(DP[A[i]], DP[j] + 1);
		}
	}
	int res = -MAX;
	for(int i = 1; i <= MAX; i++) { res=max(res, DP[i]); }
	cout << res << '\n';
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
