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
vector<int> A;

void HandleInput(istream &ins)
{
	ins >> N;
	A.assign(N, 0);
	for(int i = 0; i < N; i++){
		ins >> A[i];
	}
	sort(A.begin(), A.end());
	int l = 0, r =0;
	for(auto& e : A) {
		int nxtL = l + e, nxtR  = r + e;
		if( nxtL <= r + 1) {
			r = nxtR;
		}
		else {
			break;
		}
	}
	cout << r + 1 << '\n';
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
