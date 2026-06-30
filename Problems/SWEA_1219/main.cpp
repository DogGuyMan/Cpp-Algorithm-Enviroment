#include <iostream>
#include <vector>
#include <cstring>
#define S_VAL 0
#define E_VAL 99

using namespace std;

int ISVISIT[101];
int ct, N;

int main()
{
	// freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		vector<int> MAP[101];
		memset(ISVISIT, 0, sizeof(ISVISIT));
		scanf("%d %d", &ct, &N);
		for (int i = 0; i < N; ++i)
		{
			int f, t; scanf("%d %d", &f, &t);
			MAP[f].push_back(t);
		}
		vector<int> st; st.push_back(S_VAL);
		while (!st.empty())
		{
			int cur = st.back(); st.pop_back();
			ISVISIT[cur] = 1;
			if (cur == E_VAL) {break;}
			for (const auto & nxt : MAP[cur])
				if (nxt != -1 && !ISVISIT[nxt])
					st.push_back(nxt);
		}
		printf("#%d %d\n", t, ISVISIT[E_VAL]);
	}
}