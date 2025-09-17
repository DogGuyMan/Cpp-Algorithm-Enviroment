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

int DIGITS[100] = {
    0,
};
bool USING[100][100][100] = {0,};
long long ANS = 0;
int N;

inline void GreaterOrdering(int& a, int& b, int& c) {
	if(a > c) swap(a, c);
	if(a > b) swap(a, b);
	if(b > c) swap(b, c);
}

void HandleInput(istream &ins)
{
	ins >> N;
	int inNums[3] = {
	    0,
	};
	for (int i = 1; i <= N; ++i)
	{
		ins >> inNums[0] >> inNums[1] >> inNums[2];
		++DIGITS[--inNums[0]];
		++DIGITS[--inNums[1]]; 
		++DIGITS[--inNums[2]];
	}

	int lmr[3] = {0,};
	int chance = 3;
	FOR(i, 0, 100) {
		FOR(j, 0, 100) {
			if(i == j) continue;
			FOR(k, 0, 100) {
				if((i==k) || (j ==k)) continue;
				lmr[0] = i, lmr[1]= j, lmr[2]=k;
				GreaterOrdering(lmr[0], lmr[1], lmr[2]);
				bool& countedFlag = USING[lmr[0]][lmr[1]][lmr[2]];
				if(!countedFlag) {
					bool addable = false;
					chance = 3;
					for(int x = 99; x >= 0; --x) {
						if(DIGITS[x] > 1) continue;
						if(DIGITS[x] == 1 && chance > 0) {
							if(x == lmr[chance-1])
								--chance;
							else break;
						}
						else {
							if((x == lmr[0] || x == lmr[1] || x == lmr[2])){
								addable = true;
								break;
							}
						}
					}
					if(!addable) continue;
					countedFlag=true;
					ANS++;
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
