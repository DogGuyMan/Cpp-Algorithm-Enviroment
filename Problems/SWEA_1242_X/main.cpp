#include <iostream>
#include <map>
#include <vector>
#define Y first
#define X second

using namespace std;

int TC, N, M;

// const string NUM_TABLE[10] =
// {
// 	"0001101", // 0
// 	"0011001", // 1
// 	"0010011", // 2
// 	"0111101", // 3
// 	"0100011", // 4
// 	"0110001", // 5
// 	"0101111", // 6
// 	"0111011", // 7
// 	"0110111", // 8
// 	"0001011", // 9
// };

const int RATIO_TABLE[10][4] =
{
	{3, 2, 1, 1},
	{2, 2, 2, 1},
	{2, 1, 2, 2},
	{1, 4, 1, 1},
	{1, 1, 3, 2},
	{1, 2, 3, 1},
	{1, 1, 1, 4},
	{1, 3, 1, 2},
	{1, 2, 1, 3},
	{3, 1, 1, 2},
};

int main(int argc, char**argv)
{
	if (argc > 1) freopen(argv[1], "r", stdin);
	scanf("%d", &TC);

	map<char, string> HEX_TABLE =
	{
		{'0', "0"},    {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
		{'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
		{'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
		{'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
	};

	for (int t = 1; t <= TC; ++t)
	{
		int res = 0;
		int MXW = 1;
		scanf("%d %d", &N, &M);
		map<string, bool> pwMap;
		for (int i = 0; i < N; ++i)
		{
			string tmp;
			{
				char BUFF[2048];
				scanf("%s", BUFF);
				tmp = string(BUFF);
			}
			int len = tmp.size();
			bool nonZero = false;
			for (auto it = tmp.begin(); it != tmp.end(); ++it)
			{
				if (*it == '0') continue;
				nonZero = true;
				string pw = "0000";
				while ((*it) != '0') {pw += HEX_TABLE[(*it)]; ++it;}
				pwMap.insert({pw, true});
			}
			if (!nonZero) continue;
		}
		for (const auto& e : pwMap)
		{
			printf("%s\n", e.Y.c_str());
		}
		printf("\n");
		bool validate = false;
		int odd = 0, even = 0;
		for (const auto& e : pwMap)
		{
			string curStr = e.Y;
			int sIdx = 0;
			for (int w = 1; w < MXW; ++w)
			{
				int MXLEN = 55 * w;
				for (; sIdx < curStr.size() - MXLEN; ++sIdx)
				{
					printf("curStr[sIdx + MXLEN] : %d\n", curStr[sIdx + MXLEN]);
					if (curStr[sIdx + MXLEN] == '0') continue;
					printf("sIdx : %d\n", sIdx); // DEBUG
					for (int curSIdx = sIdx; curSIdx < 56 + sIdx; ++curSIdx)
					{
						printf("%c", curStr[curSIdx]);
					}
					printf("\n");
					for (int k = 0; k < 8; ++k)
					{
						int ni = 0;
						for (; ni < 10; ++ni)
						{
							bool matchFlag = true;
							for (int klen = 0; klen < 7; ++klen)
							{
								char curChar = curStr[sIdx + (k * 7) + klen];
								char cmpChar = NUM_TABLE[ni][klen];
								printf("%c != %c\n", curChar, cmpChar);
								if (curChar != cmpChar) {matchFlag = false; break;}
							}
							printf("\n");
							if (matchFlag) break;
						}
						printf("sIdx %d & ni : %d\n", sIdx, ni); // DEBUG
						if (ni >= 10) ni = 0;
						if (k & 1) 	even += ni;
						else 		odd += ni;
					}
					if (!validate)
					{
						if (odd != 0 && even != 0 && (odd * 3 + even) % 10 == 0)
						{
							validate = true;
							res = odd + even;
							break;
						}
					}
				}
			}
			printf("#%d %d\n", t, validate ? res : 0);
		}
	}
	return 0;

}