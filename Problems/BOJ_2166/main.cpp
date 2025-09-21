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

struct vector3{
	ll x;
	ll y;
	ll z;
};

vector3 Cross(const vector3& a, const vector3& b) {
	vector3 res;
	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

vector3 Neg(const vector3& v) {
	return {-v.x, -v.y, -v.z};
}

vector3 Add(const vector3& a, const vector3& b) {
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}

vector3 Sub(const vector3& a, const vector3& b) {
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}

ll Det(const vector3& a, const vector3& b)  {
	ll i = a.y * b.z - a.z * b.y;
	ll j = a.x * b.z - a.z * b.x;
	ll k = a.x * b.y - a.y * b.x;
	return i - j + k;
}

deque<vector3> points;

void HandleInput(istream &ins)
{
	int N; ins >> N;
	ll xPrev, yPrev; ins >> xPrev >> yPrev;
	for(int i = 0; i < N; i++) {
		ll xCur, yCur; ins >> xCur >> yCur;
		points.push_back({xCur - xPrev, yCur - yPrev, 0});
		xPrev = xCur, yPrev = yCur;
	}

	ll twoSum = 0.0;

	for(int i = 2; i < N; i++) {
		auto a = points.front(); points.pop_front();
		auto b = points.front(); points.pop_front();
		points.push_front(Add(a, b));
		ll s = Det(Neg(a), b);
		twoSum += s;
	}
	double res = (abs(twoSum)*100.0)/200.0;
	cout	<< fixed << setprecision(1) << res << '\n';
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
