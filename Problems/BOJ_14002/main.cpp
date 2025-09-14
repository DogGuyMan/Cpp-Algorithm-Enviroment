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

void HandleDirty(bool& is_dirty) {
	CAPTURE.clear();
	size_t aSz = A.size();
	CAPTURE.resize(aSz);
	for(int i = 0; i < aSz; i++) 
		CAPTURE[i] = A[i];
	is_dirty = false;
}

void HandleInput(istream &ins)
{
	ins >> N;
	A.push_back(-INF);
	CAPTURE.push_back(-INF);
	int mxLen = 1; bool isDirty = false;

	for(int i = 1; i <= N; i++) {
		ll cur; ins >> cur;
		if(A.back() < cur) {
			if(A.back() == CAPTURE.back()) {
				CAPTURE.push_back(cur);
			}
			else {
				isDirty = true;
			}
			A.push_back(cur);
			mxLen = max(mxLen, (int)A.size());
		}
		else {
			if(isDirty) HandleDirty(isDirty);
			auto it = lower_bound(A.begin(), A.end(), cur);
			*it = cur;
		}
	} 
	if(isDirty) HandleDirty(isDirty);

	cout << mxLen -1 <<  '\n';
	for(auto& e : CAPTURE) {
		if(e == -INF) continue;
		cout << e << ' ';
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
