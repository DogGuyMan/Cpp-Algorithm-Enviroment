빠르게 이항 계수 구하기.
```cpp
#include<stdio.h>
int main()
{
	int k,n,m,dam;
	scanf("%d", &k);
	for(int z=0; z<k; z++)
	{
		dam=1;
		scanf("%d %d", &n, &m);
		for(int i=0; i<n; i++)
		{
			dam*=m-i; 
			dam/=1+i;
		}
		printf("%d\n", dam);
	}
}
```

```cpp
long long combinations(int n, int m) {
    if (n > m / 2) {
        n = m - n;
    }

    long long result = 1;
    for (int i = 0; i < n; ++i) {
        result = result * (m - i) / (i + 1);
    }
    return result;
}
```