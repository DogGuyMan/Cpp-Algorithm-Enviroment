
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

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
	// freopen("input.txt", "r", stdin);
	const int MXN = 8;
	const int MXTC = 10;
	char MAP[MXN + 1][MXN + 1] = {0};
	for (int t = 1; t <= MXTC; ++t)
	{
		vector<vector<char>> PELS;
		int len;
		scanf("%d", &len);
		for (int i = 0; i < MXN; i++)
			scanf("%s", MAP[i]);
		for (int r = 0; r < MXN; ++r)
		{
			for (int c = 0; c < MXN; ++c)
			{
				vector<char> temp;
				if (len + r <= MXN)
				{
					for (int l = 0; l < len; ++l)
						temp.push_back({MAP[r + l][c]});
					if (IsPelin(temp))
						PELS.push_back(temp);
				}
				temp.clear();
				if (len + c <= MXN)
				{
					for (int l = 0; l < len; ++l)
						temp.push_back({MAP[r][c + l]});
					if (IsPelin(temp))
						PELS.push_back(temp);
				}
				temp.clear();
			}
		}
		printf("#%d %d\n", t, PELS.size());
	}
}