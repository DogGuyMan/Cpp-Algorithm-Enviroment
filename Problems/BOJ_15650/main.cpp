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

int N, M, ANS[9] = {0,};

void PrintAns()
{
	for (int i = 1; i <= M; i++)
	{
		printf("%d ", ANS[i]);
	}
	printf("\n");
}
// U가 필요하지 않는 이유는 어차피 다음 요소는 무조건 선택 안된것이 보장 되었기 때문이다
void BT(int ck)
{
	if (ck == M + 1)
	{
		PrintAns();
		return;
	}
	for (int i = 1; i <= N; ++i)
	{
		ANS[ck] = i;
		BT(ck + 1);
		ANS[ck] = 0;
	}
}

void HandleInput(istream &ins)
{
	ins >> N >> M;
	BT(1);
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
