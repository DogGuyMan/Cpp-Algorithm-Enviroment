#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

bool IsPrime(int n)
{
	if (n < 2) return false;
	if (n < 4) return true;                             // 2, 3
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6)                 // i*i <= n 이어야 완전제곱수(4, 9, 49...)를 놓치지 않는다
	{
		if (n % i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}

int solution(string numbers)
{
	// digits 는 "만들고 있는 수"가 아니라 "쓸 수 있는 숫자 타일 주머니".
	// 끝까지 통짜 int 로 변환되지 않는다.
	vector<int> digits;
	digits.reserve(numbers.size());
	for (char c : numbers)
		digits.push_back(c - '0');
	sort(digits.begin(), digits.end());                 // 아래 중복 가지치기가 성립하려면 같은 값이 인접해야 한다

	vector<bool> used(digits.size(), false);
	unordered_set<int> made;

	// DFS 노드 하나 = 만들 수 있는 수 하나.
	// 루트에서 현재 노드까지의 경로가 곧 자릿수 순서이므로 자릿수 벡터를 따로 들 필요가 없다.
	// i 를 매번 0 부터 도는 것이 핵심 — 조합이 아니라 순열이어야 하므로 인덱스 역행을 허용해야 한다. (145 와 514 는 다른 수)
	auto Build = [&](auto&& Self, int cur) -> void
	{
		for (size_t i = 0; i < digits.size(); ++i)
		{
			if (used[i]) continue;
			// 값이 같은 타일은 항상 왼쪽 것부터 쓴다.
			// 왼쪽 쌍둥이가 미사용인데 오른쪽을 쓰면 왼쪽을 쓰는 가지의 완전한 복제가 된다.
			// 왼쪽이 이미 사용중이면 "두 번째 같은 숫자"이므로 허용해야 한다. (예: 22)
			if (i > 0 && digits[i] == digits[i - 1] && !used[i - 1]) continue;

			used[i] = true;
			int next = cur * 10 + digits[i];            // 앞자리 0 은 여기서 자연히 사라진다 ("011" -> 11)
			made.insert(next);
			Self(Self, next);
			used[i] = false;
		}
	};
	Build(Build, 0);

	int answer = 0;
	for (int n : made)
	{
		if (IsPrime(n)) ++answer;
	}
	return answer;
}
