#include <iostream>
#include <string>
#include <deque>
#include <cstdio>
using namespace std;
typedef long long ll;

/*
Stack의 기본 빝바탕은 deque
	1. deque
	2. vector
	3. list

그냥 deque와 vector를 쓰는게 유연성이 좋다

deque VS vector
	1. 랜덤 접근 둘다 상수지만
		vector가 동일 공간 지역성이 우수해
			캐시 히트율이 좋다 연속 메모리 공간이니.
		deque는 블럭 단위로 접근해서 블록 경계마다
			Heap 주소가 끊긴다.
			그래도 연속 메모리 공간은
			map[i/블록] + i%블록 단위로
			블록 길이만큼은 캐시 히트는 가능
	2. push/pop 비용이 일정하고 안정
		vector는 2배씩 heap 메모리 이동이 생기므로
			reserve를 하지 않으면 스파이크가 튄다.
			또한 push_front에서는 O(n)
		deque는 앞뒤로 O(1)
*/
int PrecOrder(char op)
{
	if (op == '*' || op == '/') return 2;
	if (op == '+' || op == '-') return 1;
	return 0;
}

ll Apply(ll left, ll right, char op)
{
	switch (op)
	{
	case '+' : return left + right;
	case '-' : return left - right;
	case '*' : return left * right;
	case '/' : return left / right;
	}
	return 0;
}

void Collapse(deque<ll>& values, deque<char>& ops)
{
	ll right = values.back(); values.pop_back();
	ll left = values.back(); values.pop_back();
	char op = ops.back(); ops.pop_back();
	values.push_back(Apply(left, right, op));
}

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		int N; scanf("%d", &N);
		ll sum = 0;
		string expr;
		{
			char BUFF[1010101];
			scanf("%s", BUFF);
			expr = string(BUFF);
		}
		std::deque<ll> values;
		std::deque<char> ops;
		for (const char& ch : expr)
		{
			if ('0' <= ch && ch <= '9') values.push_back(ch - '0');
			else if (ch == '(') ops.push_back('(');
			else if (ch == ')')
			{
				while (ops.back() != '(') Collapse(values, ops);
				ops.pop_back();
			}
			else
			{
				while (!ops.empty() && PrecOrder(ops.back()) >= PrecOrder(ch)) Collapse(values, ops);
				ops.push_back(ch);
			}
		}
		while (!ops.empty()) Collapse(values, ops);
		printf("#%d %lld\n", t, values.back());
	}
}