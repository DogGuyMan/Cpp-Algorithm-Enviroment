#include <iostream>
using namespace std;
#define X first
#define Y second
typedef long long ll;
typedef pair<ll, ll> pll;
namespace gpt
{
	// (b - a) x (c - a) : 2 * signed area
	ll CCW_(const pll &a, const pll &b, const pll &c)
	{
		return (b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y) * (c.X - a.X);
	}

	// orientation: 1(반시계), -1(시계), 0(일직선)
	int CCW(const pll &a, const pll &b, const pll &c)
	{
		ll ret = CCW_(a, b, c);
		if (ret > 0)
			return 1;
		if (ret < 0)
			return -1;
		return 0;
	}

	// 두 점 사이 거리^2
	ll Len2(const pll &a, const pll &b)
	{
		ll dx = a.X - b.X;
		ll dy = a.Y - b.Y;
		return dx * dx + dy * dy;
	}

	// 2 * signed area
	ll Area2(const pll &a, const pll &b, const pll &c)
	{
		return CCW_(a, b, c);
	}

	// 실제 넓이 (양수)
	long double Area(const pll &a, const pll &b, const pll &c)
	{
		return fabsl((long double)Area2(a, b, c)) / 2.0L;
	}

	// 점 p와 직선 ab 사이 거리
	long double DistPointLine(const pll &p, const pll &a, const pll &b)
	{
		if (a == b)
		{
			return sqrtl((long double)Len2(p, a));
		}
		long double cross = (long double)CCW_(a, b, p);
		long double num = fabsl(cross);
		long double den = sqrtl((long double)Len2(a, b));
		return num / den;
	}
}

// // pll is point
// ll CCW(const pll &a, const pll &b, const pll &c)
// {
// 	ll ret = a.Y * b.X + b.Y * c.X + c.Y * a.Y;
// 	ret -= b.Y * a.X + c.Y * b.X + a.Y * c.Y;
// 	return (ret > 0) - (ret < 0);
// }

// ll CCW_(const pll &a, const pll &b, const pll &c)
// {
// 	ll ret = a.Y * b.X + b.Y * c.X + c.Y * a.Y;
// 	ret -= b.Y * a.X + c.Y * b.X + a.Y * c.Y;
// 	return ret;
// }

// ll Len1(const pll &a, const pll &b)
// {
// 	ll dx = a.Y - b.Y;
// 	ll dy = a.Y - b.Y;
// 	return dx * dx + dy * dy;
// }

// ll Area(const pll &a, const pll &b, const pll &c)
// {
// 	pll ab = pll(b.Y - a.Y, b.X - a.X);
// 	pll bc = pll(c.Y - b.Y, c.X - b.X);
// 	return CCW_({0, 0}, ab, bc);
// }

// // 직선과 점 사이 거리

// ll Len2(const pll &ptr, const pll &a, const pll &b)
// {
// 	auto S = Area({0, 0}, a, b);
// 	return S / Len1(a, b);
// }

// // 평행 사변형 넓이
