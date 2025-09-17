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
int A[101010] = {0,};

inline int SafeIdx(int idx) {
	return ((idx-1) % N) + 1;
}

inline int CWLine(int cur) {
	return cur;
}

inline int CCWLine(int cur) {
	if (cur - 1 <= 0)
		return N;
	else 
		return cur-1;
}

inline int CWMove(int cur) {
	return cur+1;
}
inline int CCWMove(int cur) {
	if(cur - 1 == 0) 
		return N;
	else 
		return cur-1;
}

void HandleInput(istream &ins)
{
	ins >> N >> M;
	for(int i = 1; i <= N; i++) {
		ins >> A[i];
	}
	if(M == 1) {cout << 0 << '\n'; return;}
	ll maxCount = N * M;
	cout << "---CW---" << '\n';
	int cwCurPos = 1;
	int cwTime = 0;
	for(ll time = 1; time <=maxCount; time++) {
		int timeToSafeIdx = SafeIdx(time);
		int activatedLine = A[timeToSafeIdx];
		cout	<< "time : " << time << ' '
			<< "timeToSafeIdx : " << timeToSafeIdx << ' '
			<< "activatedLine : " << A[timeToSafeIdx] << ' '
			<< "CWLine(cwCurPos) : " << CWLine(cwCurPos) << ' '
			<< "cwCurPos : " << cwCurPos <<'\n';
		if(CWLine(cwCurPos) == activatedLine) {
			cwCurPos = CWMove(cwCurPos);
		}
		if(cwCurPos == M) {
			cwTime = time; 
			cout << "FINISHED " << '\n';
			cout	<< "time : " << time << ' '
				<< "timeToSafeIdx : " << timeToSafeIdx << ' '
				<< "activatedLine : " << A[timeToSafeIdx] << ' '
				<< "CWLine(cwCurPos) : " << CWLine(cwCurPos) << ' '
				<< "cwCurPos : " << cwCurPos <<'\n';
			break;
		}
	}
	cout << cwTime << '\n';

	cout << "---CCW ---" << '\n';
	int ccwCurPos = 1;
	ll ccwTime = 0;
	for(ll time = 1; time <=maxCount; time++) {
		int timeToSafeIdx = SafeIdx(time);
		int activatedLine = A[timeToSafeIdx];
		cout	<< "time : " << time << ' '
			<< "timeToSafeIdx : " << timeToSafeIdx << ' '
			<< "activatedLine : " << A[timeToSafeIdx] << ' '
			<< "CCWLine(ccwCurPos) : " << CCWLine(ccwCurPos) << ' '
			<< "ccwCurPos : " << ccwCurPos <<'\n';
		if(CCWLine(ccwCurPos) == activatedLine) {
			ccwCurPos = CCWMove(ccwCurPos);
		}
		if(ccwCurPos == M) {
			ccwTime = time;
			cout << "FINISHED " << '\n';
			cout	<< "time : " << time << ' '
				<< "timeToSafeIdx : " << timeToSafeIdx << ' '
				<< "activatedLine : " << A[timeToSafeIdx] << ' '
				<< "CCWLine(ccwCurPos) : " << CCWLine(ccwCurPos) << ' '
				<< "ccwCurPos : " << ccwCurPos <<'\n';
			break;
		}
	}
	cout << ccwTime << '\n';
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
