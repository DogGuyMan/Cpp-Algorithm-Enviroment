#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int TC;
int N, M;

string NUM_TABLE[10] =
{
	"0001101", // 0
	"0011001", // 1
	"0010011", // 2
	"0111101", // 3
	"0100011", // 4
	"0110001", // 5
	"0101111", // 6
	"0111011", // 7
	"0110111", // 8
	"0001011", // 9
};

int main(int argc, char** argv)
{
	//if (argc > 1)
	//freopen(argv[1], "r", stdin);

	scanf("%d", &TC);
	for (int t = 1 ; t <= TC; ++t)
	{
		scanf("%d %d", &N, &M);
		int odd = 0, even = 0;
		int flagCnt = 0;
		for (int i = 0; i < N; ++i)
		{
			char BUFF[1024];
			scanf("%s", BUFF);
			int backIdx = M - 1;
			int flag = false;
			for (; backIdx >= 0; --backIdx)
			{
				if (BUFF[backIdx] == '1') {flag = true; break;}
			}
			if (flag)
			{
				++flagCnt;
				deque<char> dq;
				while (dq.size() < 56)
					dq.push_front(BUFF[backIdx--]);
				// for (int j = 0; j < 56; ++j)
				// 	printf("%c", dq[j]);
				// printf("\n");
				vector<int> pwNum;
				for (int j = 0; j < 56; j += 7)
				{
					int tbi = 0;
					int tbres = 0;
					for (; tbi < 10; ++tbi)
					{
						bool pwFlag = true;
						for (int k = 0; k < 7; ++k)
						{
							if (NUM_TABLE[tbi][k] != dq[j + k])
								pwFlag = false;
							// printf("%c", dq[j + k]); // DEBUG
						}
						// printf("\n"); // DEBUG
						// for (int k = 0; k < 7; ++k) // DEBUG
						// printf("%c", NUM_TABLE[tbi][k]); // DEBUG
						// printf("\n"); // DEBUG
						if (pwFlag) tbres = tbi;
					}
					pwNum.push_back(tbres);
				}
				// for (const auto& e : pwNum) // DEBUG
				// 	printf("%d ", e); // DEBUG
				// printf("\n");// DEBUG
				for (int j = 0; j < pwNum.size(); ++j)
				{
					if (j & 1)
						even += pwNum[j];
					else
						odd += pwNum[j];
				}
			}
		}
		// printf("%d\n", flagCnt);
		odd /= flagCnt;
		even /= flagCnt;
		int res = ((odd * 3) + even);
		// printf("%d\n", odd);
		// printf("%d\n", even);
		// printf("%d\n", res);
		printf("#%d %d\n", t, (res % 10 == 0) ? (odd + even) : 0 );
	}
	return 0;
}