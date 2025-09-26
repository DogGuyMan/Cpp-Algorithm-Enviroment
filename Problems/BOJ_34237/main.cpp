#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define X first
#define Y second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int N, M;
vector<pii> BETS;

void HandleInput(istream &ins)
{
	ins >> N >> M;
	int a = 0;
	int b = 0;
	for (int i = 0; i < N; i++)
	{
		ins >> a >> b;
		BETS.push_back({a, b});
	}

	pii mi;
	int gameCnt = 0;
	pii p1, p2;
	while (M--)
	{
		int ANS = 0;
		ins >> gameCnt;
		ins >> mi.X >> mi.Y;
		p1 = {mi.X, mi.Y + gameCnt};
		p2 = {mi.X + gameCnt, mi.Y};
		for (auto &bet : BETS)
		{
			if(	(bet.X + bet.Y) > gameCnt) continue;
			if (	(mi.X > bet.X) || (mi.Y > bet.Y)) continue;
			if ((bet.Y - p1.Y) + gameCnt >= (-1) * (bet.X - p1.X))
				ANS++;
		}
		cout << ANS << '\n';
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
