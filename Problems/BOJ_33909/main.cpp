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

const int MAX = 1e6;
int ALPHA_CNT[1010] = {
    0,
};
int ANS = 0;
// 밸런싱을 맞추는게 중요하다.

bool CheckMakeable(int cnt)
{
	return ALPHA_CNT['S'] - (2 * cnt) >= 0 &&
	       ALPHA_CNT['C'] - (4 * cnt) >= 0 &&
	       ALPHA_CNT['O'] - (1 * cnt) >= 0 &&
	       ALPHA_CNT['N'] - (1 * cnt) >= 0;
}

bool TryMakeString(int cnt)
{
	ALPHA_CNT['S'] -= (2 * cnt);
	ALPHA_CNT['C'] -= (4 * cnt);
	ALPHA_CNT['O'] -= (1 * cnt);
	ALPHA_CNT['N'] -= (1 * cnt);
	ANS += cnt;
	return true;
}
inline bool Convert_NS()
{
	if (ALPHA_CNT['N'] < 1)
		return false;
	ALPHA_CNT['N']--;
	ALPHA_CNT['S']++;
	return true;
}
inline bool Convert_SN()
{
	if (ALPHA_CNT['S'] < 1)
		return false;
	ALPHA_CNT['S']--;
	ALPHA_CNT['N']++;
	return true;
}
inline bool Convert_CO()
{
	if (ALPHA_CNT['C'] < 2)
		return false;
	ALPHA_CNT['C'] -= 2;
	ALPHA_CNT['O']++;
	return true;
}
inline bool Convert_OC()
{
	if (ALPHA_CNT['O'] < 1)
		return false;
	ALPHA_CNT['O']--;
	ALPHA_CNT['C'] + 2;
	return true;
}

void BalanceNS()
{
	if (ALPHA_CNT['S'] == ALPHA_CNT['N'] * 2)
		return;
	if (ALPHA_CNT['S'] > ALPHA_CNT['N'] * 2)
	{
		while (
		    (1 <= ALPHA_CNT['S']) &&
		    ((ALPHA_CNT['S'] - 1) > (ALPHA_CNT['N'] + 1) * 2))
		{
			cout << "LOOP NS" << '\n'; // DEBUG
			ALPHA_CNT['S']--;
			ALPHA_CNT['N']++;
		}
	}
	else if (ALPHA_CNT['S'] < ALPHA_CNT['N'] * 2)
	{
		while (
		    (1 <= ALPHA_CNT['N']) &&
		    ((ALPHA_CNT['S'] + 1) < (ALPHA_CNT['N'] - 1) * 2))
		{
			cout << "LOOP NS" << '\n'; // DEBUG
			ALPHA_CNT['S']++;
			ALPHA_CNT['N']--;
		}
	}
}

void BalanceOC()
{
	if (ALPHA_CNT['C'] == ALPHA_CNT['O'] * 4)
		return;
	if (ALPHA_CNT['C'] > ALPHA_CNT['O'] * 4)
	{
		while (
		    1 <= ALPHA_CNT['O'] &&
		    ((ALPHA_CNT['C'] + 2) > (ALPHA_CNT['O'] - 1) * 4))
		{
			cout << "LOOP OC" << '\n';				 // DEBUG
			cout << ALPHA_CNT['C'] << " " << ALPHA_CNT['O'] << '\n'; // DEBUG
			ALPHA_CNT['C'] += 2;
			ALPHA_CNT['O']--;
		}
	}
	else if (ALPHA_CNT['C'] < ALPHA_CNT['O'] * 4)
	{
		cout << ALPHA_CNT['C'] << " " << ALPHA_CNT['O'] << '\n'; // DEBUG
		while (
		    2 <= ALPHA_CNT['C'] &&
		    ((ALPHA_CNT['C'] - 2) < (ALPHA_CNT['O'] + 1) * 4))
		{
			cout << "LOOP OC" << '\n';				 // DEBUG
			cout << ALPHA_CNT['C'] << " " << ALPHA_CNT['O'] << '\n'; // DEBUG
			ALPHA_CNT['C'] -= 2;
			ALPHA_CNT['O']++;
		}
	}
}

void HandleInput(istream &ins)
{
	for (int i = 0; i < 4; i++)
	{
		ins >> ALPHA_CNT['S'] >> ALPHA_CNT['C'] >> ALPHA_CNT['O'] >> ALPHA_CNT['N'];
	}
	int makableCnt = 0; // 파라메트릭 서치 하기
	BalanceNS();
	BalanceOC();
	for (int i = 0; i <= MAX; i++)
	{
		if (!CheckMakeable(i))
		{
			makableCnt = --i;
			break;
		}
	}
	TryMakeString(makableCnt);

	cout << ALPHA_CNT['S'] << " " << ALPHA_CNT['C'] << " " << ALPHA_CNT['O'] << " " << ALPHA_CNT['N'] << " " << '\n'; // DEBUG
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
