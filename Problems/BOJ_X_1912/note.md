#### 1차적인 해결법
```cpp

int A[101010] = {0,};

void HandleInput(istream &ins)
{
	int mx = -MAX;
	int N; ins >> N;
	FOR(i, 0, N) { ins >> A[i]; }
	FOR(i, 0, N) {
		int subSum = 0;
		FOR(j, i, N) {
			subSum += A[j];
			mx = max(mx, subSum);
		}
	}
	for(int i = N-1; i >= 0; --i) {
		int subSum = 0;
		for(int j = i; j >= 0; --j) {
			subSum += A[j];
			mx = max(mx, subSum);
		}
	}
	cout << mx << '\n';
}

```
$ ,100,000 *  100,000 * 2 = 20000000000$
200억이 넘어가니. 시간 초과 난다.

지금 문제점은 이미 계산된계 또 계산되는 중이라는것이다.
구간합을 미리 계산 해야 할 것 같다.

D[i] D[0]은 첫번째 수를 마지막 원소로 하는 구간합의 최댓값
D[1]은 두번째 수를 마지막 원소로 하는 구간합의 최댓값
```
2 1 -4 3 4 
-4 6 5 -5 1

D[1] = 0 + 2
D[2] = 0 + D[1] + 1 = 3
D[3] = D[2] + -4 = -1
D[4] = 0 + 3 = 3
D[5] = D[4] + 4 = 7
D[6] = 3
D[7] = 9
D[8] = 14
D[9] = 9
D[10] = 10
```