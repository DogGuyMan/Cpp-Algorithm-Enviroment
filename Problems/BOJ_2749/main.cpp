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
typedef vector< vector< int > > imatrix;
typedef vector< vector< unsigned long long > > ullmatrix;

const unsigned long long MOD = 1000000;
const ullmatrix IDEN_MATRIX_2D = {
	{1, 0},
	{0, 1}
};

const ullmatrix FIBO_MAT = {
	{1, 1},
	{1, 0},
};

unsigned long long FIBO[2] = {0, 1};

ullmatrix operator*(const ullmatrix& lhs, const ullmatrix& rhs) {
	int n = lhs.size();
	int m = rhs[0].size();
	if(lhs[0].size() != rhs.size()) abort();
	int l = rhs.size();
	ullmatrix newMat(n, vector<unsigned long long>(m, 0));
	FOR(i, 0, n) {
		FOR(j, 0, m) {
			FOR(k, 0, l) {
				newMat[i][j] += ((lhs[i][k] % MOD) * (rhs[k][j] % MOD) % MOD);
				newMat[i][j] %= MOD;
			}
		}
	}
	return newMat;
}

ullmatrix TwoDimMatPow(const ullmatrix& mat, unsigned long long n) {
	if(n == 1) return mat;
	ullmatrix halfMat = TwoDimMatPow(mat, n/2);
	return (n % 2) ? halfMat * halfMat * mat : halfMat * halfMat;
}

unsigned long long N;

void HandleInput(istream &ins)
{
	ins >> N;
	if(N <= 1) {
		cout << N << '\n';
		return;
	}
	ullmatrix fiboMat = TwoDimMatPow(FIBO_MAT, N);
	cout << fiboMat[1][0] << '\n';
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
