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

const int INF = 1e9+7;
int N;
vector<ll> A;
vector<ll> CAPTURE;
pair<ll, ll> NUM_INDEX_PAIR[1010101];

void HandleInput(istream &ins)
{
	ins >> N;
	A.push_back(-INF);
	NUM_INDEX_PAIR[0] = {-INF, 0} ;
	int mxLen = 0; 

	for(int i = 1; i <= N; i++) {
		ll cur; ins >> cur;
		if(A.back() < cur) {
			A.push_back(cur);
			NUM_INDEX_PAIR[i] = {cur, ++mxLen};
		}
		else {

			auto it = lower_bound(A.begin(), A.end(), cur);
			*it = cur;
			NUM_INDEX_PAIR[i] = {cur, (int)(it-A.begin())};
		}
	} 

	// FOR(i, 1, N+1) { // DEBUG
	// 	cout << NUM_INDEX_PAIR[i].Y << ' '; // DEBUG
	// } cout << '\n'; // DEBUG
	// FOR(i, 1, N+1) { // DEBUG
	// 	cout << NUM_INDEX_PAIR[i].X << ' '; // DEBUG
	// } cout << '\n'; // DEBUG

	cout << mxLen <<  '\n';
	vector<ll> backTrack;
	for(int i = N; i >= 1; --i) {
		if(NUM_INDEX_PAIR[i].X == mxLen) {
			backTrack.push_back(NUM_INDEX_PAIR[i].Y);
			--mxLen;
		}
	}
	for(auto rit = backTrack.rbegin(); rit != backTrack.rend(); rit++) {
		cout << *rit << ' ';
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
