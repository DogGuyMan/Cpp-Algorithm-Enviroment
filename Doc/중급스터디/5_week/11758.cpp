#include <iostream>
#include <fstream>
#include <deque>
#include <iomanip>
#include <cmath>
using namespace std;
#define FASTIO ios::sync_with_stdio(false); cin.tie(nullptr);
#define X first
#define Y second
typedef long long ll;
typedef pair<ll, ll> pll;

ll CCW_(const pll &a, const pll &b, const pll &c)
{
	return (a.X * b.Y + b.X * c.Y + c.X * a.Y) - (a.Y * b.X + b.Y * c.X + c.Y * a.X);
}

int CCW(const pll &a, const pll &b, const pll &c) {
	ll ret = CCW_(a, b, c);
	return (ret > 0) - (ret < 0);
}


ll PPDistSq(const pll &a, const pll &b) {
	ll dx = a.X - b.X;
	ll dy = a.Y - b.Y;
	return dx*dx + dy*dy;
}

ll Area(const pll &a, const pll &b, const pll &c) {
	pll vab = pll(b.X - a.X, b.Y - a.Y);
	pll vbc = pll(c.X - b.X, c.Y - b.Y);
	return CCW_({0, 0}, vab, vbc);
}

ll PLDistSq(const pll &p, const pll &a, const pll &b) {
	return (Area({0, 0}, a, b) * Area({0, 0}, a, b)) / PPDistSq(a, b);
}

int main()
{
	pll a, b, c;
	{
		ll x, y; cin >> x >> y;
		a = {x, y};
	}
	{
		ll x, y; cin >> x >> y;
		b = {x, y};
	}
	{
		ll x, y; cin >> x >> y;
		c = {x, y};
	}
	cout << CCW(a, b, c) << '\n';
}