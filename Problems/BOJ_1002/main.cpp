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

struct Circle
{
	int x, y, r;
};

int T;
Circle C[2] = {{0,0,0},{0,0,0}};
int mxR, mnR, distSq, outerSq, innerSq;

int DistSq(const Circle &lhs, const Circle &rhs)
{
	return ((lhs.x - rhs.x) * (lhs.x - rhs.x)) + ((lhs.y - rhs.y) * (lhs.y - rhs.y));
}

void HandleInput(istream &ins)
{
	ins >> T;
	while (T--)
	{
		
		ins >> C[0].x >> C[0].y >> C[0].r;
		ins >> C[1].x >> C[1].y >> C[1].r;
		if (C[0].x == C[1].x && C[0].y == C[1].y)
		{
			if (C[0].r == C[1].r) cout << -1 << '\n';
			else cout << 0 << '\n';
			continue;
		}
		mxR = max(C[0].r, C[1].r);
		mnR = min(C[0].r, C[1].r);
		distSq = DistSq(C[0], C[1]);
		outerSq = (mxR - mnR) * (mxR - mnR);
		innerSq = (C[0].r + C[1].r) * (C[0].r + C[1].r);
		if (distSq == innerSq)
		{
			cout << 1 << '\n';
			continue;
		}
		if (distSq == outerSq)
		{
			cout << 1 << '\n';
			continue;
		}
		if (distSq > innerSq)
		{
			cout << 0 << '\n';
			continue;
		}
		if (distSq < outerSq)
		{
			cout << 0 << '\n';
			continue;
		}
		cout << 2 << '\n';
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
