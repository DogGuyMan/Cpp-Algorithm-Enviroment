#include <iostream>
#include <deque>
#include <string>

using namespace std;

inline int OpOrder(char op)
{
	if (op == '+') return 1;
	if (op == '*') return 2;
	return 0;
}

inline int Calc(int l, int r, char op)
{
	if (op == '+') return l + r;
	if (op == '*') return l * r;
	return 0;
}

void Squash(deque<int>& val_st, deque<char>& op_st)
{
	int l = val_st.back(); val_st.pop_back();
	int r = val_st.back(); val_st.pop_back();
	char op = op_st.back(); op_st.pop_back();
	val_st.push_back(Calc(l, r, op));
}

int main()
{
	freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		int exprLen = 0; scanf("%d", &exprLen);
		string exprStr;
		{
			char BUFF[1024]; scanf("%s", BUFF);
			exprStr = string(BUFF);
		}
		deque<int> valSt;
		deque<char> opSt;
		for (const auto& ch : exprStr)
		{
			if ('0' <= ch && ch <= '9') {valSt.push_back(ch - '0'); continue;}

			if (ch == '(') opSt.push_back(ch);
			else if (ch == ')')
			{
				while (opSt.back() != '(') Squash(valSt, opSt);
				opSt.pop_back();
			}
			else
			{
				while (!opSt.empty() && OpOrder(opSt.back()) >= OpOrder(ch)) Squash(valSt, opSt);
				opSt.push_back(ch);
			}
		}
		while (!opSt.empty()) Squash(valSt, opSt);
		printf("#%d %d\n", t, valSt.back());
	}
}