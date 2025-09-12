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

ull A;
ull B;

// 2와 5로 이뤄져야 하는 최소 공배수
ull TWO_FIVE[2] = {0};


void HandleInput(istream &ins)
{
	ins >> A >> B;
	for (ull i = A; i <= B; i++)
	{
		// cout << "cur : " << i << '\n'; // DEBUG
		ull temp = i;
		ull tempTwo = 0, tempFive = 0;
		while ((temp % 5 == 0))
		{
			// cout << temp << '\n'; // DEBUG
			tempFive++;
			temp /= 5;
		}
		while ((temp % 2 == 0))
		{
			// cout << temp << '\n'; // DEBUG
			tempTwo++;
			temp /= 2;
		}

		TWO_FIVE[0] = max(TWO_FIVE[0], tempTwo);
		TWO_FIVE[1] = max(TWO_FIVE[1], tempFive);

		// cout << tempTwo << " " << tempFive << '\n'; // DEBUG
		// cout << TWO_FIVE[0] << " " << TWO_FIVE[1] << '\n'; // DEBUG
	}
	cout << TWO_FIVE[0] << ' ' << TWO_FIVE[1] << '\n'; // DEBUG
	int tenPair = min(TWO_FIVE[0], TWO_FIVE[1]);
	cout << tenPair << '\n';
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
