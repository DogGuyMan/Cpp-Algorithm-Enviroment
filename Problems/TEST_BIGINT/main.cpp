#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

typedef deque<int> bigint;
inline void Trim(bigint &fill_zero);
int Cmp(const bigint &a, const bigint &b);
void BigIntAssign(ull val, bigint &out);
void BigIntAdd(const bigint &lhs, const bigint &rhs, bigint &out);
void BigIntSub(const bigint &lhs, const bigint &rhs, bigint &out);
void BigIntMulSmall(const bigint &big_int, int m, bigint &out);
ostream &operator<<(ostream &os, const bigint &rhs)
{
	for (const auto &d : rhs)
	{
		os << (int)d;
	}
	return os;
}

inline void Trim(bigint &fill_zero)
{
	while (fill_zero.size() > 1 && fill_zero.front() == 0)
	{
		fill_zero.pop_front();
	}
}

int Cmp(const bigint &a, const bigint &b)
{
	if (a.size() != b.size())
		return (a.size() < b.size()) ? -1 : 1;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] != b[i])
			return (a[i] < b[i]) ? -1 : 1;
	}
	return 0;
}

void BigIntAssign(ull val, bigint &out)
{
	if (val < 10)
	{
		out = {(int)val};
		return;
	}
	out.clear();
	while (val > 0)
	{
		out.push_front(val % 10);
		val /= 10;
	}
}

inline void BigIntAssign(const bigint &big_int, bigint &out)
{
	out = big_int;
}

void BigIntAdd(const bigint &lhs, const bigint &rhs, bigint &out)
{
	out.clear();
	int l = lhs.size() - 1;
	int r = rhs.size() - 1;
	int carry = 0;
	while (l >= 0 || r >= 0 || carry)
	{
		int a = (l >= 0 ? lhs[l--] : 0);
		int b = (r >= 0 ? rhs[r--] : 0);
		int s = a + b + carry;
		out.push_front(s % 10);
		carry = s / 10;
	}
	Trim(out);
}

void BigIntSub(const bigint &lhs, const bigint &rhs, bigint &out)
{
	bool cmpRes = Cmp(lhs, rhs);
	if (cmpRes <= 0)
	{
		out = {0};
		return;
	}
	int l = lhs.size() - 1, r = rhs.size() - 1;
	int borrow = 0;
	while (l >= 0 || r >= 0 || borrow)
	{
		int a = (l >= 0 ? lhs[l--] : 0);
		int b = (r >= 0 ? rhs[r--] : 0);
		int s = a - b - borrow;
		if (s < 0)
		{
			s += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		out.push_front(s);
	}
	Trim(out);
}

void BigIntMulSmall(const bigint &big_int, int m, bigint &out)
{
	if (m == 0)
	{
		out = {0};
		return;
	}
	if (m == 1)
	{
		out = big_int;
		return;
	}
	out.clear();
	int sz = big_int.size() - 1;
	int carry = 0;
	while (sz >= 0 || carry)
	{
		int deci = (sz >= 0) ? big_int[sz--] : 0;
		deci = (m * deci) + carry;
		out.push_front(deci % 10);
		carry = deci / 10;
	}
	Trim(out);
}

void BigIntMul(const bigint &lhs, const bigint &rhs, bigint &out)
{
	if (lhs.size() == 1)
	{
		BigIntMulSmall(rhs, lhs[0], out);
		return;
	}
	if (rhs.size() == 1)
	{
		BigIntMulSmall(lhs, rhs[0], out);
		return;
	}
	if (lhs.size() < rhs.size())
	{
		BigIntMul(rhs, lhs, out);
		return;
	}

	out.assign(1, 0); // 누적 초기화
	bigint shifted, sum;

	for (int i = 0; i < (int)rhs.size(); ++i)
	{
		BigIntMulSmall(lhs, rhs[rhs.size() - 1 - i], shifted);
		for (int j = 0; j < i; ++j)
			shifted.push_back(0);
		BigIntAdd(out, shifted, sum);
		out = sum;
	}
	Trim(out);
}

void HandleInput(istream &ins)
{
	ull test = 12345;
	bigint b_temp;
	BigIntAssign(test, b_temp);
	bigint out_temp;
	// for(int i = 0; i < 10; ++i) {
	// 	BigIntMulSmall(b_temp, i, out_temp);
	// 	cout << out_temp << '\n';
	// }

	ull lull = 103;
	for (ull i = 11; i <= 101; i += 3)
	{
		ull tlull = i * lull;
		cout << tlull << " " << lull << '\n';
		lull = tlull;
	}

	bigint ltmp = {1, 0, 3}, rtmp = {0}, big_i = {0};
	for (ull i = 11; i <= 101; i += 3)
	{
		BigIntAssign(i, big_i);
		BigIntMul(big_i, ltmp, rtmp);
		cout << rtmp << " " << ltmp << '\n';
		BigIntAssign(rtmp, ltmp);
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
