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

int Ans[8] = {0,};

void HandleInput(istream &ins)
{
	int n, m; ins >> n >> m;
	Ans[0] = 100 - n;
	Ans[1] = 100 - m;
	Ans[2] = 100 - (Ans[0] + Ans[1]);
	Ans[3] = Ans[0] * Ans[1];

	Ans[4] = Ans[3] / 100;
	Ans[5] = Ans[3] % 100;

	for(int i = 0; i < 6; i++)
		cout << Ans[i] << ' ';
	cout << '\n';
	Ans[6] = Ans[2];
	Ans[7] = Ans[3];
	if(Ans[3] >= 100){
		Ans[6] = Ans[2] + Ans[4];
		Ans[7] = Ans[5];
	}
	cout << Ans[6] << ' ' << Ans[7] << '\n';
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
