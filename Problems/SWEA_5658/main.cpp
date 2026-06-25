/*
배열 회전

[입력]
TC :
숫자의 개수 이건뭐.. , 크기 순서 K? 인풋의 사이즈는 아닌것 같다.
숫자의 개수 N개 만큼 인풋이 들어옴

무조건 16진수 보장
CW
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main()
{
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	// K번째로 큰 수를 10진수로 만든 수가 비밀번호.
	// 퍼뮤테이션 아닌가?
	// 0x... 뭐시기로 해보자
	for (int i = 1; i <= TC; i++)
	{
		vector<char> CHAIN;
		int N, K;
		scanf("%d %d", &N, &K);
		// printf("%d : %d %d\n", TC, N, K);
		int edgeNum = N / 4;
		char buf[1024];
		scanf("%s", buf);
		CHAIN.assign(buf, buf + N);
		// printf("\n"); // DEBUG;
		set<long long> hlist;
		for (int i = 0; i <= N; i++)
		{
			rotate(CHAIN.begin(), CHAIN.begin() + 1, CHAIN.end());
			long long hex;
			string str(CHAIN.begin(), CHAIN.begin() + edgeNum);
			sscanf(str.c_str(), "%llx", &hex);
			// printf("%s %d\n", str.c_str(), hex);
			hlist.insert(hex);
		}
		// for (const auto& e : hlist) // DEBUG
		// {
		// 	// DEBUG
		// 	printf("%llu\n", e); // DEBUG
		// } // DEBUG
		printf("#%d %lld\n", i, *(next(hlist.begin(), hlist.size() - K)));
	}
}