// 볼록 위치(원 위)에 배치된 N개 정점을 도는 닫힌 Hamiltonian cycle 의 컨투어 면적
//
//   - 간선끼리 교차해도 정확 (arrangement 로 평면분할 후 face 별 winding number 계산)
//   - 좌표는 정수 입력, 교차점은 정확 유리수로 유지 (위상 판정에 부동소수 미사용)
//   - "컨투어 면적" 이 갈리는 네 가지 정의를 전부 출력한다
//
// 이론과 측정 근거 : Doc/계산기하_평면분할과_다각형면적_보고서.md  (§3-B, 부록 F)
//
// 입력 형식
//   N
//   x1 y1 ... xN yN        정점 좌표 (원형 순서, CW 또는 CCW)
//   v1 v2 ... vN           방문 순서 (1-based 순열)

#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);
typedef long long ll;
typedef __int128 i128;

// ===================== 정확 유리수 좌표 =====================
// (mXn/mDen, mYn/mDen), mDen > 0, gcd(|mXn|,|mYn|,mDen) == 1
struct RatPoint
{
	ll mXn, mYn, mDen;
	bool operator<(const RatPoint &other) const
	{
		if (mXn != other.mXn) return mXn < other.mXn;
		if (mYn != other.mYn) return mYn < other.mYn;
		return mDen < other.mDen;
	}
	bool operator==(const RatPoint &other) const
	{
		return mXn == other.mXn && mYn == other.mYn && mDen == other.mDen;
	}
	long double ToX() const { return (long double)mXn / mDen; }
	long double ToY() const { return (long double)mYn / mDen; }
};

// libc++(macOS clang) 의 std::__gcd 는 부호 있는 타입을 거부한다 -> 직접 정의
static ll GcdLL(ll a, ll b)
{
	a = llabs(a);
	b = llabs(b);
	while (b) { ll t = a % b; a = b; b = t; }
	return a;
}

static RatPoint MakeRatPoint(ll xn, ll yn, ll den)
{
	if (den < 0) { xn = -xn; yn = -yn; den = -den; }
	ll g = GcdLL(GcdLL(xn, yn), den);   // 정규형이라야 == 로 같은 점을 합칠 수 있다
	if (g > 1) { xn /= g; yn /= g; den /= g; }
	return RatPoint{xn, yn, den};
}

// ===================== 선분과 교차 =====================
struct Segment { ll mAx, mAy, mBx, mBy; };

static ll Cross(ll ax, ll ay, ll bx, ll by) { return ax * by - ay * bx; }

static bool IsOnSegment(const Segment &s, ll px, ll py)
{
	if (Cross(s.mBx - s.mAx, s.mBy - s.mAy, px - s.mAx, py - s.mAy) != 0) return false;
	return min(s.mAx, s.mBx) <= px && px <= max(s.mAx, s.mBx) &&
	       min(s.mAy, s.mBy) <= py && py <= max(s.mAy, s.mBy);
}

static void CollectSplitPoints(const Segment &s, const Segment &t,
                               vector<RatPoint> &sPts, vector<RatPoint> &tPts)
{
	// (a) 상대 끝점이 내 선분 위 : T자 접촉과 공선 겹침이 전부 여기서 흡수된다
	if (IsOnSegment(s, t.mAx, t.mAy)) sPts.push_back(MakeRatPoint(t.mAx, t.mAy, 1));
	if (IsOnSegment(s, t.mBx, t.mBy)) sPts.push_back(MakeRatPoint(t.mBx, t.mBy, 1));
	if (IsOnSegment(t, s.mAx, s.mAy)) tPts.push_back(MakeRatPoint(s.mAx, s.mAy, 1));
	if (IsOnSegment(t, s.mBx, s.mBy)) tPts.push_back(MakeRatPoint(s.mBx, s.mBy, 1));

	// (b) 한 점에서 가로지르는 경우
	ll sdx = s.mBx - s.mAx, sdy = s.mBy - s.mAy;
	ll tdx = t.mBx - t.mAx, tdy = t.mBy - t.mAy;
	ll den = Cross(sdx, sdy, tdx, tdy);
	if (den == 0) return;                                      // 평행/공선 -> (a) 가 처리
	ll numU = Cross(t.mAx - s.mAx, t.mAy - s.mAy, tdx, tdy);   // s 위 파라미터
	ll numV = Cross(t.mAx - s.mAx, t.mAy - s.mAy, sdx, sdy);   // t 위 파라미터
	if (den < 0) { den = -den; numU = -numU; numV = -numV; }
	if (numU < 0 || numU > den || numV < 0 || numV > den) return;
	RatPoint p = MakeRatPoint(s.mAx * den + sdx * numU, s.mAy * den + sdy * numU, den);
	sPts.push_back(p);
	tPts.push_back(p);
}

// ===================== 각도 정렬용 정수 방향 =====================
struct Dir { ll mX, mY; };

static Dir MakeDir(const RatPoint &from, const RatPoint &to)
{
	ll dx = to.mXn * from.mDen - from.mXn * to.mDen;   // 공통분모를 곱해 정수화
	ll dy = to.mYn * from.mDen - from.mYn * to.mDen;
	ll g = GcdLL(dx, dy);
	if (g > 1) { dx /= g; dy /= g; }
	return Dir{dx, dy};
}

static int HalfOf(const Dir &d) { return (d.mY < 0 || (d.mY == 0 && d.mX < 0)) ? 1 : 0; }

static bool DirLess(const Dir &a, const Dir &b)   // +x 축 기준 CCW
{
	int ha = HalfOf(a), hb = HalfOf(b);
	if (ha != hb) return ha < hb;
	return (i128)a.mX * b.mY - (i128)a.mY * b.mX > 0;
}

// ===================== 평면분할 -> face 추출 =====================
struct FaceInfo
{
	long double mArea;            // 항상 양수 (유계 face)
	long double mRepX, mRepY;     // 내부 대표점
	int mWinding = 0;
};

struct ContourResult
{
	long double mOuterArea = 0.0L;   // 최외곽 윤곽이 감싸는 면적 (구멍까지 메움)
	vector<FaceInfo> mFaces;         // 유계 face 전부
	int mVertexCount = 0, mEdgeCount = 0;
};

static ContourResult BuildArrangement(const vector<Segment> &segments)
{
	int segCount = (int)segments.size();

	// --- 1. 교차점 수집 ---
	vector<vector<RatPoint>> splitPts(segCount);
	for (int i = 0; i < segCount; ++i)
	{
		splitPts[i].push_back(MakeRatPoint(segments[i].mAx, segments[i].mAy, 1));
		splitPts[i].push_back(MakeRatPoint(segments[i].mBx, segments[i].mBy, 1));
	}
	for (int i = 0; i < segCount; ++i)
		for (int j = i + 1; j < segCount; ++j)
			CollectSplitPoints(segments[i], segments[j], splitPts[i], splitPts[j]);

	// --- 2. 선분 조각내기 + 정점 ID ---
	map<RatPoint, int> vertexId;
	vector<RatPoint> vertices;
	auto GetVertexId = [&](const RatPoint &p) {
		auto it = vertexId.find(p);
		if (it != vertexId.end()) return it->second;
		int id = (int)vertices.size();
		vertexId[p] = id;
		vertices.push_back(p);
		return id;
	};

	set<pair<int, int>> edgeSet;   // 중복 간선 제거
	for (int i = 0; i < segCount; ++i)
	{
		ll dx = segments[i].mBx - segments[i].mAx;
		ll dy = segments[i].mBy - segments[i].mAy;
		auto &pts = splitPts[i];
		sort(pts.begin(), pts.end(), [&](const RatPoint &a, const RatPoint &b) {
			// 방향으로의 사영이 선분을 따라 단조 증가한다
			i128 ka = ((i128)a.mXn * dx + (i128)a.mYn * dy) * b.mDen;
			i128 kb = ((i128)b.mXn * dx + (i128)b.mYn * dy) * a.mDen;
			return ka < kb;
		});
		pts.erase(unique(pts.begin(), pts.end()), pts.end());
		for (size_t k = 0; k + 1 < pts.size(); ++k)
		{
			int u = GetVertexId(pts[k]), v = GetVertexId(pts[k + 1]);
			if (u != v) edgeSet.insert({min(u, v), max(u, v)});
		}
	}

	// --- 3. half-edge (e 와 e^1 이 twin) ---
	int vertexCount = (int)vertices.size();
	vector<int> heFrom, heTo;
	for (const auto &[u, v] : edgeSet)
	{
		heFrom.push_back(u); heTo.push_back(v);
		heFrom.push_back(v); heTo.push_back(u);
	}
	int heCount = (int)heFrom.size();

	vector<Dir> heDir(heCount);
	for (int e = 0; e < heCount; ++e)
		heDir[e] = MakeDir(vertices[heFrom[e]], vertices[heTo[e]]);

	// --- 4. 정점별 CCW 정렬 (= rotation system) ---
	vector<vector<int>> outgoing(vertexCount);
	for (int e = 0; e < heCount; ++e) outgoing[heFrom[e]].push_back(e);
	vector<int> slotOf(heCount);
	for (int v = 0; v < vertexCount; ++v)
	{
		auto &list = outgoing[v];
		sort(list.begin(), list.end(), [&](int a, int b) { return DirLess(heDir[a], heDir[b]); });
		for (int k = 0; k < (int)list.size(); ++k) slotOf[list[k]] = k;
	}

	// next(u->v) = v 에서 (v->u) 의 CCW 순서상 바로 앞 간선
	auto NextHalfEdge = [&](int e) {
		int twin = e ^ 1;
		auto &list = outgoing[heFrom[twin]];
		int k = slotOf[twin];
		return list[(k + (int)list.size() - 1) % (int)list.size()];
	};

	// --- 5. face 순회 ---
	ContourResult result;
	result.mVertexCount = vertexCount;
	result.mEdgeCount = heCount / 2;

	vector<char> visited(heCount, 0);
	for (int start = 0; start < heCount; ++start)
	{
		if (visited[start]) continue;
		long double twiceArea = 0.0L;
		int e = start;
		do {
			visited[e] = 1;
			const RatPoint &p = vertices[heFrom[e]];
			const RatPoint &q = vertices[heTo[e]];
			twiceArea += p.ToX() * q.ToY() - q.ToX() * p.ToY();
			e = NextHalfEdge(e);
		} while (e != start);

		long double area = twiceArea / 2.0L;
		if (area < -1e-9L) { result.mOuterArea += -area; continue; }   // 무한면 경계
		if (area <= 1e-9L) continue;                                   // dangling edge 왕복 -> 0

		// 유계 face : 가장 긴 half-edge 중점에서 왼쪽 법선으로 살짝 밀어 내부 대표점을 잡는다
		// (유계 face 는 CCW 로 순회되므로 진행 방향의 왼쪽이 내부)
		long double bestLen = -1, repX = 0, repY = 0;
		int e2 = start;
		do {
			const RatPoint &p = vertices[heFrom[e2]];
			const RatPoint &q = vertices[heTo[e2]];
			long double x1 = p.ToX(), y1 = p.ToY(), x2 = q.ToX(), y2 = q.ToY();
			long double dx = x2 - x1, dy = y2 - y1, len = sqrtl(dx * dx + dy * dy);
			if (len > bestLen)
			{
				bestLen = len;
				const long double EPS = 1e-7L;
				repX = (x1 + x2) / 2 - dy / len * EPS;
				repY = (y1 + y2) / 2 + dx / len * EPS;
			}
			e2 = NextHalfEdge(e2);
		} while (e2 != start);

		result.mFaces.push_back({area, repX, repY, 0});
	}
	return result;
}

// ===================== winding number =====================
static int WindingNumber(const vector<pair<ll, ll>> &poly, long double px, long double py)
{
	int wn = 0, n = (int)poly.size();
	for (int i = 0; i < n; ++i)
	{
		long double x1 = (long double)poly[i].first,  y1 = (long double)poly[i].second;
		long double x2 = (long double)poly[(i + 1) % n].first, y2 = (long double)poly[(i + 1) % n].second;
		long double isLeft = (x2 - x1) * (py - y1) - (px - x1) * (y2 - y1);
		if (y1 <= py) { if (y2 >  py && isLeft > 0) ++wn; }
		else          { if (y2 <= py && isLeft < 0) --wn; }
	}
	return wn;
}

// ===================== main =====================
int main()
{
	FASTIO
	int vertexTotal;
	if (!(cin >> vertexTotal)) return 0;

	vector<pair<ll, ll>> circlePts(vertexTotal);
	for (auto &[x, y] : circlePts) cin >> x >> y;

	vector<int> visitOrder(vertexTotal);
	for (auto &v : visitOrder) { cin >> v; --v; }   // 1-based -> 0-based

	// 입력 검증 : 중복 방문이 없어야 한다 (Hamiltonian cycle)
	{
		vector<char> seen(vertexTotal, 0);
		for (int v : visitOrder)
		{
			if (v < 0 || v >= vertexTotal || seen[v]) { cout << "invalid cycle\n"; return 1; }
			seen[v] = 1;
		}
	}

	// 방문 순서대로 닫힌 폴리곤 구성
	vector<pair<ll, ll>> polygon(vertexTotal);
	vector<Segment> segments(vertexTotal);
	for (int i = 0; i < vertexTotal; ++i)
	{
		auto [ax, ay] = circlePts[visitOrder[i]];
		auto [bx, by] = circlePts[visitOrder[(i + 1) % vertexTotal]];
		polygon[i] = {ax, ay};
		segments[i] = {ax, ay, bx, by};
	}

	// (1) raw shoelace = winding 가중 면적
	long double rawTwice = 0;
	for (int i = 0; i < vertexTotal; ++i)
	{
		auto [x1, y1] = polygon[i];
		auto [x2, y2] = polygon[(i + 1) % vertexTotal];
		rawTwice += (long double)x1 * y2 - (long double)x2 * y1;
	}
	long double rawArea = fabsl(rawTwice) / 2;

	// (2)~(4) 평면분할 후 face 별 winding number
	ContourResult arrangement = BuildArrangement(segments);
	long double nonzeroArea = 0, evenOddArea = 0, boundedSum = 0;
	int zeroWindingFaces = 0;
	for (auto &face : arrangement.mFaces)
	{
		face.mWinding = WindingNumber(polygon, face.mRepX, face.mRepY);
		boundedSum += face.mArea;
		if (face.mWinding != 0)     nonzeroArea += face.mArea; else ++zeroWindingFaces;
		if (face.mWinding % 2 != 0) evenOddArea += face.mArea;
	}

	// 자체 검증 : 연결 그래프이므로 sum(유계 face) == |무한면 사이클|
	bool identityOk = fabsl(boundedSum - arrangement.mOuterArea) < 1e-4L * max(1.0L, arrangement.mOuterArea);
	bool invariantOk = (evenOddArea <= nonzeroArea + 1e-6L) && (nonzeroArea <= arrangement.mOuterArea + 1e-6L);

	cout << fixed << setprecision(1);

	// ===== 정답 : nonzero fill =====
	// 별 모양의 중심(winding >= 2)이 칠해지는 규칙. 겹친 영역도 면적은 1번만 센다.
	cout << (double)nonzeroArea << '\n';

	if (getenv("VERBOSE") == nullptr) return 0;

	// ---------- 아래는 진단용 (VERBOSE=1 일 때만) ----------
	cerr << "\n정점 " << vertexTotal << " / 평면분할 후 V=" << arrangement.mVertexCount
	     << " E=" << arrangement.mEdgeCount << " 유계F=" << arrangement.mFaces.size()
	     << " (winding=0 인 face " << zeroWindingFaces << "개)\n\n";

	cerr << fixed << setprecision(1);
	cerr << "  nonzero fill  (winding != 0)  : " << (double)nonzeroArea << "   <-- 정답\n";
	cerr << "  even-odd fill (winding 홀수)  : " << (double)evenOddArea << "   (중심이 뚫리는 규칙)\n";
	cerr << "  raw shoelace  (winding 가중)  : " << (double)rawArea     << "   (겹침을 겹친 횟수만큼 셈)\n";
	cerr << "  outer         (윤곽 내부·구멍 메움) : " << (double)arrangement.mOuterArea << '\n';

	cerr << "\n[검증] sum(유계 face)==|outer| : " << (identityOk ? "ok" : "BROKEN")
	     << "   |   even-odd<=nonzero<=outer : " << (invariantOk ? "ok" : "BROKEN") << '\n';

	// winding 분포 : 중심이 정말 겹쳐 있는지 확인용
	map<int, int> windingHistogram;
	for (const auto &face : arrangement.mFaces) ++windingHistogram[face.mWinding];
	cerr << "[winding 분포] ";
	for (const auto &[w, cnt] : windingHistogram) cerr << "w=" << w << ":" << cnt << "개  ";
	cerr << '\n';
	return 0;
}
