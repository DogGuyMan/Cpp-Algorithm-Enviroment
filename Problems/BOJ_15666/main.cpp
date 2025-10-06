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
set<int> SET;
vector<vector<int>> ANS;

void BF(vector<int>& seq) {
	if(seq.size() >= (size_t)M) {
		ANS.push_back(vector<int>(seq));
		return;
	}
	for(const int& e : SET) {
		if(!seq.empty() && seq.back() > e) continue;
		seq.push_back(e);
		BF(seq);
		seq.pop_back();
	}
}

void HandleInput(istream &ins)
{
	ins >> N >> M;
	for(int i = 0; i < N; i++) {
		int inNum; ins>> inNum;
		SET.insert(inNum);
	}
	vector<int> seq;
	BF(seq);
	for(const vector<int>& e : ANS) {
		for(const auto& c : e) {
			cout << c << ' ';
		} cout << '\n';
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
