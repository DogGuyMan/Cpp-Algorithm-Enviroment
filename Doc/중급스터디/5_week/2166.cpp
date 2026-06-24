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

ll Area(const pll &a, const pll &b, const pll &c) {
	pll vab = pll(b.X - a.X, b.Y - a.Y);
	pll vbc = pll(c.X - b.X, c.Y - b.Y);
	return CCW_({0, 0}, vab, vbc);
}

int main()
{
	FASTIO
	int N; 
	deque<pll> POINTS;
	cin >> N;
	for(int i = 0; i < N; i++) {
		ll x, y; cin >> x >> y;
		POINTS.push_back({x, y});
	}
	POINTS.push_back(POINTS.front());
	ll sum = 0;
	while(POINTS.size() > 1) {
		pll pt1 = POINTS.front(); POINTS.pop_front();
		pll pt2 = POINTS.front();
		sum += Area({0, 0}, pt1, pt2);
	}
	cout << fixed << setprecision(1) << llabs(sum) / 2.0 << '\n';
}