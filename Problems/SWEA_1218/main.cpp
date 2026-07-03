#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(int argc, char** argv)
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		vector<char> st;
		int N; scanf("%d", &N);
		char BUFF[1010101]; scanf("%s", BUFF);
		// printf("%s\n", BUFF);
		for (int i = 0; i < N; ++i)
		{
			if (st.empty() && (BUFF[i] == '}' || BUFF[i] == ')' || BUFF[i] == '>' || BUFF[i] == ']'))
				break;
			else if (!st.empty() && (st.back() == '{' && BUFF[i] == '}')) {st.pop_back();}
			else if (!st.empty() && (st.back() == '(' && BUFF[i] == ')')) {st.pop_back();}
			else if (!st.empty() && (st.back() == '<' && BUFF[i] == '>')) {st.pop_back();}
			else if (!st.empty() && (st.back() == '[' && BUFF[i] == ']')) {st.pop_back();}
			else st.push_back(BUFF[i]);
			// for (const auto& e : st)
			// 	printf("%c", e);
			// printf("\n");
		}
		printf("#%d %d\n", t, ((st.empty() == true) ? 1 : 0));
	}
}