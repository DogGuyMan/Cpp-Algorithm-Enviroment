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

int N, M;
int A[101010];
int CW[101010];
int CCW[101010];

void HandleInput(istream &ins)
{
	ins >> N >> M;
	for(int i = 1; i <= N; i++) {
		ins >> A[i];
		CW[((A[i]) % N) + 1] = i;
		CCW[A[i]] = i;
	}
	if(M == 1) { 
		cout << "EQ" << '\n'; return; 
	}
	for(int i = 1; i <= N; i++) {
		// cout 	<< "A[" << i << "] : "  << A[i] << ' ' // DEBUG
			// << "CW[" << i << "] : "  << CW[i] << ' ' // DEBUG
			// << "CCW[" << i << "] : "  << CCW[i] << '\n'; // DEBUG
	}
	// CW
	int cwCurPos = 2;
	int cwCurIdx = CW[2];
	ll cwMvTime = CW[2];
	for(int i = 1; i <= N; i++) {
		int nxtPos = cwCurPos + 1;
		// cout 	<< "cwCurPos : " << cwCurPos  << ' ' // DEBUG
			// << "nxtPos : " << nxtPos  << ' ' // DEBUG
			// << "cwCurIdx : " << cwCurIdx  << ' ' // DEBUG
			// << "CW[nxtPos] : " << CW[nxtPos]  << ' ' // DEBUG
			// << "cwMvTime : " << cwMvTime  << ' '; // DEBUG
		if(cwCurPos == M) {break;}
		if(CW[nxtPos] < cwCurIdx) {
			cwMvTime += (CW[nxtPos] - cwCurIdx + N);
			// cout << "mvCnt : " << (CW[nxtPos] - cwCurIdx + N) << '\n'; // DEBUG
		}
		else {
			cwMvTime += (CW[nxtPos] - cwCurIdx);
			// cout << "mvCnt : " << (CW[nxtPos] - cwCurIdx) << '\n'; // DEBUG
		} 
		cwCurIdx = CW[nxtPos];
		cwCurPos = nxtPos;
	}

	// cout << '\n'; // DEBUG

	int ccwCurPos = N;
	int ccwCurIdx = CCW[N];
	ll ccwMvTime = CCW[N];
	for(int i = 1; i <= N; i++) {
		int nxtPos = ccwCurPos - 1;
		// cout 	<< "ccwCurPos : " << ccwCurPos  << ' ' // DEBUG
			// << "nxtPos : " << nxtPos  << ' ' // DEBUG
			// << "ccwCurIdx : " << ccwCurIdx  << ' ' // DEBUG
			// << "cCW[nxtPos] : " << CCW[nxtPos]  << ' ' // DEBUG
			// << "ccwMvTime : " << ccwMvTime  << ' '; // DEBUG
		if(ccwCurPos == M) {break;}
		if(CCW[nxtPos] < ccwCurIdx) {
			ccwMvTime += (CCW[nxtPos] - ccwCurIdx + N);
			// cout << "mvCnt : " << (CCW[nxtPos] - ccwCurIdx + N) << '\n'; // DEBUGs
		}
		else {
			ccwMvTime += (CCW[nxtPos] - ccwCurIdx);
			// cout << "mvCnt : " << (CCW[nxtPos] - ccwCurIdx) << '\n'; // DEBUG
		}
		ccwCurIdx = CCW[nxtPos];
		ccwCurPos = nxtPos;
	}
	// cout << '\n'; // DEBUG
	// cout 	<< "cwMvTime : " << cwMvTime << " " // DEBUG
	// 	<< "ccwMvTime : " << ccwMvTime << '\n'; // DEBUG
	if(cwMvTime < ccwMvTime) {
		cout << "CW" << '\n';
	}
	else if (cwMvTime > ccwMvTime) {
		cout << "CCW" << '\n';
	}
	else {
		cout << "EQ" << '\n';
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
