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

struct Module {
	int idx;
	int eff;
	bool operator<(const Module& rhs) const {
		return eff > rhs.eff;
	}
};

vector<Module> A;

// 1 2 3 
// 5 1 7 

// 3 1 4 2
// 7 5 2 1

// 100 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20
// 100 100 100 300
// 100 20 120 240
// 100 20 140
// 100 20 160
// 100 20 180
// 100 20 180
// 100 20 20 20 20 20 20 20 20 20 2

vector<Module> ANSS;

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
	sort(A.begin(), A.end());
	ANSS.push_back(A[0]);
	LEFF = ANSS.back().eff;
	HEFF = ANSS.back().eff;
	SUM = ANSS.back().eff;
	MX = LEFF + HEFF + SUM;
	int mxWindow = 0;

	for(int i = 1; i < N; i++) {
		ull nxtLeff = A[i].eff;
		ull nxtSum = A[i].eff + SUM;
		if(MX <= nxtLeff + nxtSum + HEFF) {
			MX = nxtLeff + nxtSum + HEFF;
			mxWindow = i;
		}
		LEFF = nxtLeff;
		SUM = nxtSum;
		ANSS.push_back(A[i]);
	}
	cout << ANSS.size() << '\n';
	for(int i = 0; i <= mxWindow; i++) {
		cout << ANSS[i].idx << ' ';
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
