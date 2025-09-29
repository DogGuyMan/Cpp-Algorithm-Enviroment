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

int N;

const char* SK = "SK"; // 상근
const char* CY = "CY"; // 창영
int DP[1010] = {0,};

void HandleInput(istream &ins)
{
	ins >> N;
	if(N == 1) {cout << SK << '\n'; return;}
	if(N == 2) {cout << CY << '\n'; return;} // N - 1 == 1
	if(N == 3) {cout << SK << '\n'; return;} 
	if(N == 4) {cout << CY << '\n'; return;} // N - 3 == 1 // N - 1 == 3
	if(N == 5) {cout << SK << '\n'; return;} // 
	DP[1] = 0; DP[2] = 1; DP[3] = 0; DP[4] = 1; DP[5] = 0;
	for(int i = 6; i <= N; i++) {
		DP[i] = DP[i-3]^1;
	}
	(DP[N] == 0) ? 
		cout << SK << '\n':
		cout << CY << '\n';
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
