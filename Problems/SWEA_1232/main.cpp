#include <iostream>
#include <cstring>
using namespace std;

bool IS_OP[1024];
char OP[1024];
double VAL[1024];
int N, L[1024], R[1024];

double PostOrder(int c_idx)
{
	if (c_idx == 0) return -1;
	if (!IS_OP[c_idx]) return VAL[c_idx];
	double lhs = PostOrder(L[c_idx]);
	double rhs = PostOrder(R[c_idx]);
	switch (OP[c_idx])
	{
	case '+': { return lhs + rhs;}
	case '-': { return lhs - rhs;}
	case '*': { return lhs * rhs;}
	case '/': { return lhs / rhs;}
	default: {return -1;}
	}
}

int main(int argc, char** argv)
{
	// if (argc > 1)
	// 	freopen(argv[1], "r", stdin);
	for (int t = 1; t <= 10; ++t)
	{
		memset(IS_OP, 0, sizeof(IS_OP));
		memset(OP, 0, sizeof(OP));
		memset(VAL, 0, sizeof(VAL));
		memset(L, 0, sizeof(L));
		memset(R, 0, sizeof(R));

		scanf("%d", &N);

		for (int i = 0; i < N; i++)
		{
			char BUFF[1024];
			scanf(" %[^\n]", BUFF);
			int midx, ridx, lidx;
			midx = ridx = lidx = -1;
			int cnt = 1;

			{
				int h = 0;
				int strsz = strlen(BUFF);
				while (h < strsz) {if (BUFF[h++] == ' ') ++cnt;}
			}

			if (cnt == 2)
			{
				int tok;
				sscanf(BUFF, "%d %d", &midx, &tok);
				VAL[midx] = (double)tok;
			}
			else if (cnt == 4)
			{
				char tok;
				sscanf(BUFF, "%d %c %d %d", &midx, &tok, &lidx, &ridx);
				IS_OP[midx] = true; OP[midx] = tok;
				if (lidx != -1) L[midx] = lidx;
				if (ridx != -1) R[midx] = ridx;
			}
		}
		// InOrder(1);
		printf("#%d %.0lf\n", t, PostOrder(1));
	}
}