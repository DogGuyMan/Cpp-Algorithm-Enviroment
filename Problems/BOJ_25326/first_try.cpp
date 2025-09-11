#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for( int i = (a); i < (b); ++i)
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int CNT[101010] {0,};

int GetSubHash(const string& sub) {
	if(sub == "kor") return 100;
	if(sub == "eng") return 200;
	if(sub == "math" ) return 300;
	return 0;
}

int GetFruHash(const string& fru) {
	if(fru == "apple") return 10;
	if(fru == "pear") return 20;
	if(fru == "orange"  ) return 30;
	return 0;
}

int GetColHash(const string& col) {
	if(col == "red") return 1;
	if(col == "blue") return 2;
	if(col == "green" ) return 3;
	return 0;
}

int GetHash(const string& str, int idx) {
	if(idx == 0) return GetSubHash(str);
	if(idx == 1) return GetFruHash(str);
	return GetColHash(str);
}

void WriteCnt(string (&strs)[3], int curIdx, int curHash) {
	if(curIdx > 2) {
		CNT[curHash]++;
		return;
	}
	int hCode = GetHash(strs[curIdx], curIdx);
	if(hCode == 0) {
		for(int i = 1; i <= 3; i++) {
			int hMask = pow(10, 3-curIdx-1);
			WriteCnt(strs, curIdx+1, curHash + (hMask * i));
		}
		return;
	}
	WriteCnt(strs, curIdx+1, curHash+hCode);
}

void LoadCnt(string (&strs)[3], int curIdx, int curHash, int& ans) {
	if(curIdx > 2) {
		ans += CNT[curHash];
		return;
	}
	if(strs[curIdx] == "-") {
		for(int i = 1; i <= 3; i++) {
			int hMask = pow(10, 3-curIdx-1);
			LoadCnt(strs, curIdx+1, curHash + (hMask * i), ans);
		}
		return;
	}
	LoadCnt(strs, curIdx+1, curHash+GetHash(strs[curIdx], curIdx), ans);
}

void HandleInput(istream &ins)
{
	int N, M; ins >> N >> M;
	FOR(i, 0, N) {
		string inStr[3];
		FOR(j, 0, 3) {
			ins >> inStr[j];
		}
		WriteCnt(inStr, 0, 0);
	}
	FOR(i, 0, M) {
		string inStr[3];
		FOR(j, 0, 3) {
			ins >> inStr[j];
		}
		int ans = 0;
		LoadCnt(inStr, 0, 0, ans);
		cout << ans << '\n';
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
