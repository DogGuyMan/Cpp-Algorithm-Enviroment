#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int MV_Y[2] = {0, 1};
int MV_X[2] = {1, 0};

// 다항식 롤링 해쉬 : hash = hash * 131 + 문자
// 131 은 분산이 좋아 충돌이 적으면서도 외우기 쉬운 문자열 해쉬용 소수
struct VectorCharHash
{
	size_t operator()(const vector<char>& vec) const
	{
		const size_t PRIME = 13331;
		size_t hashValue = 0;
		for (const char& ch : vec)
			hashValue = hashValue * PRIME + static_cast<size_t>(ch);
		return hashValue;
	}
};

bool IsPelin(const vector<char>& str)
{
	int l = 0, r = str.size() - 1;
	while (l < r)
	{
		if (str[l] != str[r]) return false;
		++l; --r;
	}
	return true;
}

int main()
{
	const int MXN = 100;
	const int MXTC = 10;
	// freopen("input.txt", "r", stdin);
	// const int MXN = 8;
	// const int MXTC = 1;
	char MAP[MXN + 1][MXN + 1] = {0};
	for (int t = 1; t <= MXTC; ++t)
	{
		// unordered_set<vector<char>, VectorCharHash> PELS;
		int trsh; scanf("%d", &trsh);
		for (int i = 0; i < MXN; i++)
		{
			scanf("%s", MAP[i]);
		}
		int mx = 1;
		for (int r = 0; r < MXN; ++r)
		{
			for (int c = 0; c < MXN; ++c)
			{
				vector<char> temp;
				temp.push_back({MAP[r][c]});
				for (int l = 1; l < MXN - r; ++l)
				{
					int nr = r + l;
					temp.push_back({MAP[nr][c]});
					if (mx < temp.size() && IsPelin(temp))
					{
						mx = temp.size();
						// PELS.insert(temp);
					}
				}
				temp.clear();
				temp.push_back({MAP[r][c]});
				for (int l = 1; l < MXN - c; ++l)
				{
					int nc = c + l;
					temp.push_back({MAP[r][nc]});
					if (mx < temp.size() && IsPelin(temp))
					{
						mx = temp.size();
						// PELS.insert(temp);
					}
				}
				// for (const auto& pel : PELS)
				// {
				// 	for (const auto& c : pel)
				// 	{
				// 		printf("%c", c);
				// 	}
				// 	printf("\n");
				// }

			}
		}
		printf("#%d %d\n", trsh, mx);
	}
}