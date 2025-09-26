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

int N;
int A[20][20] = { 0, };
bool SEQ_BUFF[333] = { 0, };
bool IsSeq(int n, int r1, int r2, int c1, int c2)
{
	memset(SEQ_BUFF, false, 333 * sizeof(bool));
	for (int i = r1; i <= r2; ++i)
	{
		for (int j = c1; j <= c2; ++j)
		{
			if (SEQ_BUFF[A[i][j]])
				return false;
			SEQ_BUFF[A[i][j]] = true;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (SEQ_BUFF[i] == false)
			return false;
	}
	return true;
}
void HandleInput(istream &ins)
{
	ins >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			ins >> A[i][j];
		}
	}
	int ANS = 0;

	for (int r1 = 1; r1 <= N; ++r1)
	{
		for (int r2 = r1; r2 <= N; ++r2)
		{
			for (int c1 = 1; c1 <= N; ++c1)
			{
				for (int c2 = c1; c2 <= N; ++c2)
				{
					if ((r2 - r1 + 1) * (c2 - c1 + 1) <= 0)
						continue;
					if (IsSeq((r2 - r1 + 1) * (c2 - c1 + 1), r1, r2, c1, c2))
					{
						ANS++;
					}
				}
			}
		}
	}
	cout << ANS << '\n';
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
