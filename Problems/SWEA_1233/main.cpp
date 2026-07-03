#include <cstdio>
#include <cstring>

int  N;
// bool IS_OP[1024];
// char OP[1024];
// int  VAL[1024];
// int  L[1024], R[1024];

// double Eval(int i)
// {
// 	if (!IS_OP[i]) return VAL[i];
// 	double a = Eval(L[i]);
// 	double b = Eval(R[i]);
// 	switch (OP[i])
// 	{
// 	case '+': return a + b;
// 	case '-': return a - b;
// 	case '*': return a * b;
// 	case '/': return b == 0 ? 0 : a / b;
// 	}
// 	return 0;
// }

int main(int argc, char** argv)
{
	// if (argc > 1)
	// 	freopen(argv[1], "r", stdin);

	for (int t = 1; t <= 10; ++t)
	{
		scanf("%d", &N);

		// memset(IS_OP, 0, sizeof(IS_OP));
		// memset(L, 0, sizeof(L));
		// memset(R, 0, sizeof(R));

		bool valid = true;
		for (int i = 0; i < N; i++)
		{
			char buff[1024];
			scanf(" %[^\n]", buff);

			int midx, lidx, ridx; char op;
			int cnt = sscanf(buff, "%d %c %d %d", &midx, &op, &lidx, &ridx);
			bool isDigit = ('0' <= op && op <= '9');

			if (cnt == 2 && !isDigit) valid = false;
			if (cnt == 4 &&  isDigit) valid = false;

			// if (cnt == 4)
			// {
			// 	IS_OP[midx] = true;
			// 	OP[midx] = op;
			// 	L[midx] = lidx;
			// 	R[midx] = ridx;
			// }
			// else
			// {
			// 	IS_OP[midx] = false;
			// 	VAL[midx] = isDigit ? (op - '0') : 0;
			// }
		}

		// if (valid)
		// 	printf("   [debug] value = %.0f\n", Eval(1));

		printf("#%d %d\n", t, valid ? 1 : 0);
	}
	return 0;
}
