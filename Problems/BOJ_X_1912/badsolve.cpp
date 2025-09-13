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

void HandleInput(istream &ins)
{
	int mx = -MAX;
	int N; ins >> N;
	FOR(i, 0, N) { ins >> A[i]; }
	FOR(i, 0, N) {
		int subSum = 0;
		FOR(j, i, N) {
			subSum += A[j];
			mx = max(mx, subSum);
		}
	}
	for(int i = N-1; i >= 0; --i) {
		int subSum = 0;
		for(int j = i; j >= 0; --j) {
			subSum += A[j];
			mx = max(mx, subSum);
		}
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
