#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for( int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int N;
int ANS1 = 1;
int ANS2 = 1;
ull DP[44] = {0,};

ull FIBO1(ull cur) {
	if(cur <= 1) return cur;
	if(cur == 2) return 1;
	else {
		ANS1++;
		return (FIBO1(cur-1) + FIBO1(cur-2));
	}
}

ull FIBO2(ull cur) {
	if(cur <= 2) return 1;
	for(ull i = 3; i < cur; i++) {
		ANS2++;
		DP[i] = DP[i-1] + DP[i-2];
	}
	return DP[cur];
}

void HandleInput(istream &ins)
{
	ins >> N;
	FIBO1(N);
	FIBO2(N);
	cout << ANS1 << ' ' << ANS2 << '\n';
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