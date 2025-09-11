#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

char STR_IDEN[3][4] = {
    {'-', 'k', 'e', 'm'},
    {'-', 'a', 'p', 'o'},
    {'-', 'r', 'g', 'b'}};
int CNT[4][4][4] = {0};

void HandleInput(istream &ins)
{
	int N, M;
	ins >> N >> M;
	FOR(i, 0, N)
	{
		int indexedIden[3] = {
		    0,
		};
		FOR(j, 0, 3)
		{
			string inStr;
			ins >> inStr;
			indexedIden[j] = (find(STR_IDEN[j], STR_IDEN[j] + 4, inStr[0]) - STR_IDEN[j]);
		}
		for (int mask = 0; mask < 8; ++mask)
		{
			int x = (mask & 1) ? 0 : indexedIden[0];
			int y = (mask & 2) ? 0 : indexedIden[1];
			int z = (mask & 4) ? 0 : indexedIden[2];
			CNT[x][y][z]++;
		}
	}

	FOR(i, 0, M)
	{
		int indexedIden[3] = {
		    0,
		};
		FOR(j, 0, 3)
		{
			string inStr;
			ins >> inStr;
			indexedIden[j] = (find(STR_IDEN[j], STR_IDEN[j] + 4, inStr[0]) - STR_IDEN[j]);
		}
		cout << CNT[indexedIden[0]][indexedIden[1]][indexedIden[2]] << '\n';
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
