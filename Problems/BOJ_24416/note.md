```cpp
int N;
int ANS1 = 1;
int ANS2 = 1;
ull DP[44] = {0,};

void HandleInput(istream &ins)
{
	ins >> N;
	DP[1] =1; DP[2] = 1;
	for(int i = 3; i <= N; i++)
		DP[i] = DP[i-2] + DP[i-1];
	cout << DP[N] << ' ' << N-2 << '\n';
}
```

피보나치의 재귀호출의 수도, 피보나치다.