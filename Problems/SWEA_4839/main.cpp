#include <cstdio>
#include <math.h>

int main(int argc, const char* argv[])
{
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		int P, A, B; scanf("%d %d %d", &P, &A, &B);
		int upper = log2(1010) + 1;
		int res = 0; // 1, 0, -1
		int l[2] = {1, 1};
		int r[2] = {P, P};
		int c[2] = {(l[0] + r[0]) / 2, (l[1] + r[1]) / 2};
		for (int i = 1; i <= upper; ++i)
		{
			bool flag = false;
			if (c[0] == A) {res += 1; flag = true;}
			else if (c[0] < A) {l[0] = c[0];}
			else if (c[0] > A) {r[0] = c[0];}

			if (c[1] == B) {res -= 1; flag = true;}
			else if (c[1] < B) {l[1] = c[1];}
			else if (c[1] > B) {r[1] = c[1];}
			if (flag == true) break;

			c[0] = (l[0] + r[0]) / 2;
			c[1] = (l[1] + r[1]) / 2;
		}
		char resChar;
		if (res == 0)  resChar = '0';
		else if (res < 0) resChar = 'B';
		else if (res > 0) resChar = 'A';

		printf("#%d %c\n", tc, resChar);
	}
	return 0;
}
