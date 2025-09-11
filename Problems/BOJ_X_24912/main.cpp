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

int N, CARD[1000100] = {0,};
vector<int> NON_COLORED_IDX;

inline bool CheckColorable(int idx, int color) {
	if(idx-1 >= 0 && CARD[idx-1] == color) return false;
	if(idx+1 < N && CARD[idx+1] == color) return false;
	return true;
}

void HandleInput(istream &ins)
{
	ins >> N;
	for(int i = 0; i < N; i++) {
		ins >> CARD[i];
		if(i > 0 && CARD[i-1] != 0 && CARD[i-1] == CARD[i]) {
			cout << -1 << '\n';
			return;
		}
		if(CARD[i] == 0)
			NON_COLORED_IDX.push_back(i);
	}

	if(NON_COLORED_IDX.empty()) {
		for(int i = 0; i < N; i++) {
			cout << CARD[i] << ' ';
		}
		return;
	}

	for(auto& idx : NON_COLORED_IDX) {
		int usableColor = 0;
		for(int c = 1; c <= 3; c++) {
			if(CheckColorable(idx, c)) {
				usableColor = c;
				break;
			}
		}
		CARD[idx] = usableColor;
	}

	for(int i = 0; i < N; i++) {
		cout << CARD[i] << ' ';
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
