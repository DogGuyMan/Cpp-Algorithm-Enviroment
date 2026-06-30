#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
using namespace std;


int MatchStep(const string& patt, const vector<int>& lps, char matchChar, int matchLen)
{
	while (matchLen > 0 && matchChar != patt[matchLen])
		matchLen = lps[matchLen - 1];
	if (patt[matchLen] == matchChar)
		++matchLen;
	return matchLen;
}

vector<int> ComputeLPS(const string& patt)
{
	int pattSz = patt.size();
	int prefixLen = 0;
	vector<int> lps(pattSz, 0);
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
	if (psz <= 0 || psz > tsz) return {};
	vector<int> idxs;
	int matchLen = 0;
	auto lps = ComputeLPS(patt);
	for (int i = 0; i < tsz; ++i)
	{
		matchLen = MatchStep(patt, lps, text[i], matchLen);
		if (matchLen == psz)
		{
			idxs.push_back(i - psz + 1);
			matchLen = lps[matchLen - 1];
		}
	}
	return idxs;
}



string Normalize(const string& s)
{
	string r;
	for (int i = 0; i < (int)s.size(); ++i)
	{
		if (i + 1 < (int)s.size() && s[i + 1] == '#')
		{
			r += (char)tolower(s[i++]);
			++i;
			continue;
		}
		r += s[i];
	}
	return r;
}

int GetTimeGap(const string& lhs, const string& rhs)
{
	int lH = stoi(lhs.substr(0, 2)), rH = stoi(rhs.substr(0, 2));
	int lM = stoi(lhs.substr(3, 2)), rM = stoi(rhs.substr(3, 2));
	return (rH - lH) * 60 + (rM - lM);
}

string solution(string m, vector<string> musicinfos)
{
	string answer = "(None)";
	int bestLen = -1;
	string nm = Normalize(m);

	char start[8], end[8], name[128], sheet[2048];
	for (const auto& e : musicinfos)
	{
		sscanf(e.c_str(), "%[^,],%[^,],%[^,],%s", start, end, name, sheet);
		int playLen = GetTimeGap(start, end);

		string nsheet = Normalize(sheet);
		if (nsheet.empty()) continue;



		string played;
		played.reserve(playLen);
		for (int i = 0; i < playLen; ++i)
			played += nsheet[i % nsheet.size()];


		if (!KMPSearch(played, nm).empty())
		{
			if (playLen > bestLen)
			{
				bestLen = playLen;
				answer = string(name);
			}
		}
	}
	return answer;
}
