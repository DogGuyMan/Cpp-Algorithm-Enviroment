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

string s, t;
vector<int> DP;

void HandleInput(istream &ins)
{
	while((ins >> s >> t)) {
		DP.clear();
		int tSz = t.size();
		DP.resize(tSz, 0);
		int matchCnt= 0;
		for(int i = 0; i < tSz; i++) {
			if(t[i] == s[matchCnt]) {
				matchCnt++;
			}
			DP[i] = matchCnt;
			if(DP[i] == s.size()) break;
		}
		(matchCnt == s.size()) ? 
			cout << "Yes" << '\n' :
			cout << "No" << '\n';
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
