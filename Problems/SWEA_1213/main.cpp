#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> BFSearch(const string& text, const string& patt)
{
	vector<int> result;
	int n = text.size(), m = patt.size();
	if (m == 0 || m > n) return result;
	for (int i = 0; i <= n - m; ++i)
	{
		int j = 0;
		while (j < m) {if (patt[j] != text[i + j]) break; ++j;}
		if (j == m) result.push_back(i);
	}
	return result;
}

inline int MatchStep(const string& patt, const vector<int>& lps, char matchChar, int matchedLen)
{
	while (matchedLen > 0 && (matchChar != patt[matchedLen]))
		matchedLen = lps[matchedLen - 1];
	if (matchChar == patt[matchedLen])
		++matchedLen;
	return matchedLen;
}

vector<int> ComputeLPS(const string& patt)
{
	int pattSz = patt.size();
	vector<int> lps(pattSz, 0);
	int prefixLen = 0;
	for (int head = 1; head < pattSz; ++head)
	{
		prefixLen = MatchStep(patt, lps, patt[head], prefixLen);
		lps[head] = prefixLen;
	}
	return lps;
}

vector<int> KMPSearch(const string& text, const string& patt)
{
	int tsz = text.size(), psz = patt.size();
	vector<int> res;
	if (psz == 0 || psz > tsz) return res;
	int matchLen = 0;
	auto lps = ComputeLPS(patt);
	for (int head = 0; head < tsz; ++head)
	{
		matchLen = MatchStep(patt, lps, text[head], matchLen);
		if (psz == matchLen)
		{
			res.push_back(head - psz + 1);
			matchLen = lps[matchLen - 1];
		}
	}
	return res;
}


vector<int> BMSearch(const string& text, const string& patt)
{
	int tsz = text.size(), psz = patt.size();
	vector<int> res;
	if (psz == 0 || psz > tsz) return res;

	vector<int> badChar(256, -1);
	for (int i = 0; i < psz; ++i)
		badChar[(unsigned char)patt[i]] = i;

	int shift = 0;
	while (shift <= tsz - psz)
	{
		int cmpIdx = psz - 1;
		int badCharPos;                     // 선언만 (cmpIdx 확정 후 대입)
		int afterWindow = shift + psz;      // 윈도우 밖: 끝 다음 글자 (cmpIdx 무관)

		while (cmpIdx >= 0 && patt[cmpIdx] == text[shift + cmpIdx]) --cmpIdx;
		badCharPos = shift + cmpIdx;        // 윈도우 안: 불일치가 난 글자 위치

		if (cmpIdx >= 0)   // 불일치 나쁜 문자로 점프하고 다음 정렬
		{
			shift += max(1, cmpIdx - badChar[(unsigned char)text[badCharPos]]);
			continue;
		}

		// 여기 도달 = 완전 매칭
		res.push_back(shift);
		shift += (afterWindow < tsz) ? psz - badChar[(unsigned char)text[afterWindow]] : 1;
	}

	return res;
}

int main()
{
	freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		int testCnt; scanf("%d", &testCnt);
		string str[2];
		{
			char BUFF[(1 << 10)] = {0};
			for (int i = 0; i < 2; i++)
			{
				scanf("%1000s", BUFF);
				str[i] = string(BUFF);
			}
		}
		string& text = str[1];
		string& patt = str[0];
		auto res = BMSearch(text, patt);
		printf("#%d %d\n", t, res.size());
	}
}