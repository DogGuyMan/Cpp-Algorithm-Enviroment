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

int N, M, A[9] = {0, }, ANS[9] = {0,};

void PrintAns()
{
	for (int i = 1; i <= M; i++)
	{
		printf("%d ", ANS[i]);
	}
	printf("\n");
}

void BT(int ck)
{
	if (ck == M + 1)
	{
		PrintAns();
		return;
	}
	for (int i = ck; i < N; ++i)
	{
		if(ck > 0 && ANS[ck-1] > A[i]) continue;
		ANS[ck] = A[i];
		BT(ck + 1);
		ANS[ck] = 0;
	}
}

void HandleInput(istream &ins)
{
	ins >> N >> M;
	for(int i = 0; i < N; ++i) {
		ins >> A[i];
	}
	sort(A, A+N);
	BT(0);
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
