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
typedef vector<char> bigint;

bigint DP[10001];

void AssignULL(bigint& bigint_ref,const ull& lhs) {
	if(!bigint_ref.empty()) bigint_ref.clear();
	if(lhs == 0) {
		bigint_ref.push_back(0);
		return;
	}
	ull temp = lhs;
	while(temp) {
		bigint_ref.push_back(temp % 10);
		temp/=10;
	}
	if(bigint_ref.size() > 1)
		reverse(bigint_ref.begin(), bigint_ref.end());
}

void AddBigint(const bigint &lhs, const bigint &rhs, bigint& out_ref)
{
	int carry = 0;
	int lSize = lhs.size();
	int rSize = rhs.size();
	while (lSize || rSize)
	{
		char lnum = 0, rnum = 0;
		if (lSize > 0)
		{
			lnum = lhs[lSize - 1];
			lSize--;
		}
		if (rSize > 0)
		{
			rnum = rhs[rSize -1];
			rSize--;
		}
		char deciSum = lnum + rnum + carry;
		out_ref.push_back(deciSum % 10);
		carry = deciSum/10;
	}
	if(carry) {
		out_ref.push_back(1);
	}
	reverse(out_ref.begin(), out_ref.end());
}

ostream& operator<<(ostream& os, const bigint& rhs) {
	for(const char& d : rhs) { os << (int)d;}
	return os;
}

ull FIBO[2] = {0, 1};

ull N;

void HandleInput(istream &ins)
{
	ins >> N;
	AssignULL(DP[0], 0ULL);
	AssignULL(DP[1], 1ULL);
	AssignULL(DP[2], 1ULL);
	for(ull i = 3; i <= N; i++) {
		AddBigint(DP[i-1], DP[i-2], DP[i]);
	}
	cout << DP[N] << '\n';
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
