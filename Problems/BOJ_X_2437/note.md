#### 핵심은 그리디 + 가능한 무게의 연속 구간 l, r

* 연속 구간이 끊어지는 상황이 바로 무게를 잴 수 없는 최소값인것.
* 시각화를 통해 해결하는것도 좋다.

```
1 1 1 1 1 1 1 1 의 최소값은 어떻게 구하지?
한번 쫙 합을 구하게 된다.

2 2 2 2 2 2 2 의 최소값은 어떻게 구하지?
무조건 1이될텐데.
3 4 5 6 7 8 9 10의 최소는 어떻게 구하지?
무조건 2일텐데
1 1 2 3 6 7 30의 최소는 어떻게 구하지?


측정할 수 없다는건.. 

완탐을 할 수 밖에 없다는것을 가정하자.

---

사용하고 안하고, 둘중하나를

조합론적인 문제임
가지치기를 해야함.

1 1 2 3 6 7 30
    1 2 3 6 7 30

int cantable = 1;
-
    1 1 1 2 3 6 7 30
int cantable = 4;
1
    1 1 2 3 6 7 30
int cantable = 5;
1 1
    2 3 6 7 30
int cantable = 10;
1 1 2 = 4
    3 6 7 30
int cantable = 12;
1 1 2 3 = 7
    6 7 30
int cantable = 15;
1 1 2 3 6 = 13
    7 30
int cantable = 21;

그리디 문제다.

---

1 1 1 1 1 1 1 1
```

#### 더 손쉬운 풀이가 있었다
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

int main(void){
    int N,arr[1000],i,max=0;
    
    scanf("%d",&N);
    for(i=0;i<N;i++) scanf("%d",arr+i);
    
    sort(arr,arr+N);
    
    for(i=0;i<N;i++){
        if(max + 1 < arr[i]) break;
        max=max+arr[i];
    }
    
    printf("%d",max+1);
    
    return 0;
}
```