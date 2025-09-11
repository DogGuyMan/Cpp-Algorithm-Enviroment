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

const int INF = 1e9+7;
struct E {
	int num; int prev;
};

E DP[1010101] = {{0},};

E BF(int num) {
	int mins[4] = {INF, INF, INF, INF};
	int path = -1;
	if(num <= 1) return {0, path};
	if(DP[num].num > 0) return DP[num];

	if((num%3) == 0) mins[3] = 1 + BF(num/3).num;
	if((num%2) == 0) mins[2] = 1 + BF(num/2).num;
	mins[1] = 1 + BF(num-1).num;
	
	if(mins[2] > mins[3]) 	{ mins[0] = mins[3]; path = num/3;}
	else 			{ mins[0] = mins[2]; path = num/2;}
	if(mins[0] > mins[1]) 	{ mins[0] = mins[1]; path = num-1;}
	
	return DP[num] = {mins[0], path};
}

void HandleInput(istream &ins)
{
	int N; ins >> N;
	if(N <= 1) {cout << 0 << '\n'; cout << 1 << '\n';  return;}
	for(int i = 0; i < N; i++) { DP[i] = {-INF, -1}; }
	BF(N);
	int path = N;
	cout << DP[N].num << '\n';
	while(path != -1) {
		cout << path << ' ';
		path = DP[path].prev;
	} cout << '\n';
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
	return 0;
}
