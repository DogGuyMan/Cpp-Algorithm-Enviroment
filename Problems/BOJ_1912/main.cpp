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

const int MAX = 1e9+7;
int N;
// 최대 부분 배열
int DP[101010] = {0,};

// 10 ,6, 6+3, 9+1, 10+5, 15 +6, -14, 12, 31, 
void HandleInput(istream &ins)
{
	ins >> N;
	int inNum; ins >> inNum;
	DP[1] = inNum;
	int res = inNum;
	for(int i = 2; i <= N; i++) {
		ins >> inNum;
		DP[i] = max(DP[i] + inNum, DP[i-1] + inNum);
		res = max(res, DP[i]);
	}
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
