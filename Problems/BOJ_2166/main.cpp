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

struct vec3{
	ll x, y, z;
};

inline vec3 Cross(const vec3& a, const vec3& b) {
	return { (a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x) };
}

inline vec3 Neg(const vec3& v) {
	return {-v.x, -v.y, -v.z};
}

inline vec3 Add(const vec3& a, const vec3& b) {
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline vec3 Sub(const vec3& a, const vec3& b) {
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline ll Det(const vec3& a, const vec3& b)  {
	return (a.y * b.z - a.z * b.y) - (a.x * b.z - a.z * b.x) + (a.x * b.y - a.y * b.x);
}

deque<vec3> points;

void HandleInput(istream &ins)
{
	int N; ins >> N;
	ll xPrev, yPrev; 
	ins >> xPrev >> yPrev;
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
