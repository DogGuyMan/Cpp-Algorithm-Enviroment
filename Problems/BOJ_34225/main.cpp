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

const ull INF = 2e14;

int N;

vector<pii> A;
vector<pii> ANSS;

ull LEFF = 0, HEFF = 0, SUM = 0;
ull MX = -INF;

void HandleInput(istream &ins)
{
	ins >> N;
	int iEff;
	for(int i = 1; i <= N; i++) {
		ins >> iEff;
		A.push_back({i, iEff});
	}
	sort(A.begin(), A.end(), [&](const pii& lhs, const pii& rhs) {
		return lhs.X > rhs.X;
	});
	ANSS.push_back(A[0]);
	LEFF = ANSS.back().X;
	HEFF = ANSS.back().X;
	SUM = ANSS.back().X;
	MX = LEFF + HEFF + SUM;
	int mxWindow = 1;

	for(int i = 1; i < N; i++) {
		ull nxtLeff = A[i].X;
		ull nxtSum = A[i].X + SUM;
		if(MX <= nxtLeff + nxtSum + HEFF) {
			MX = nxtLeff + nxtSum + HEFF;
			mxWindow = i+1;
		}
		LEFF = nxtLeff;
		SUM = nxtSum;
		ANSS.push_back(A[i]);
	}
	cout << mxWindow  << '\n';
	for(int i = 0; i < mxWindow; i++) {
		cout << ANSS[i].Y << ' ';
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
