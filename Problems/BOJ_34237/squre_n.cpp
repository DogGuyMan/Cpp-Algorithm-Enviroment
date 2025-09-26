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

struct bet {
	int a; int b;
	int founded = false;
};

vector<bet> G[101];
queue<bet*> FOUNDED;
int ANS = 0;

void BF(const int& max_count, int cur_a, int cur_b) {
	if(cur_a + cur_b >  max_count) return;
	for(auto& b : G[cur_a + cur_b]) {
		if(b.founded == true) continue;
		if(b.a == cur_a && b.b == cur_b) {
			ANS++;
			b.founded = true;
			FOUNDED.push(&b);
		}
	}
	BF(max_count, cur_a+1	,cur_b);
	BF(max_count, cur_a	,cur_b+1);
}

void HandleInput(istream &ins)
{
	ins >> N >> M;
	int a = 0; int b = 0;
	for(int i = 0; i< N; i++) {
		ins >> a >> b;
		G[a+b].push_back({a, b, false});
	}

	int ia = 0; int ib = 0;
	while(M--) {
		int gameCnt ; ins >> gameCnt;
		ins >> ia >> ib;
		BF(gameCnt, ia, ib);
		cout << ANS << '\n';
		ANS = 0;
		while (!FOUNDED.empty())
		{
			bet* poped = FOUNDED.front(); 
			FOUNDED.pop();
			poped->founded=false;
		}
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
