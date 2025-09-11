
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
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

ull A, B;

// a, b 구간내, x의 배수가 존재하는지 판정

inline bool CheckExistsMul(ull x) {
	return A + ((x - (A % x)) % x) <= B;
}

int GetMaxExpo(ull num) {
	int expo = 0;
	ull pw = 1;
	while(pw <= B / num) {
		pw*=num;
		if(CheckExistsMul(pw)) ++expo;
		else break;
	}
	return expo;
}

void HandleInput(istream &ins)
{
	ins >> A >> B;
	cout << min(GetMaxExpo(2), GetMaxExpo(5)) << '\n';
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
