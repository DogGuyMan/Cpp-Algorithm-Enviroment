즉 최대 공약수를 찾되,
2와 5가 몇번 사용되었는지를 알아야하고 
그것의 최대값을 구해야 한다.

---

그런데.. 이걸 unsinged long long의 크기를 구할 수나 있을까?

B 만알아도 된다.
B보다 작은 $2^n$의 최대 n값
B보다 작은 $5^n$의 최대값 n

이걸 구하면 된다.

log5(B) `log(B) / log(5)`
log2(B) `log(2)`

---

2하고 존나 큰 소수를 넣었을 수도 있다.
이걸 최소한 포함을 하나? A 갱신
B보다 작을때 까지 가능한가? B 갱신

구간 커팅을 하는게 맞다.

---

$[a, b]$ 구간내 배수 존재 여부
#### 1).
```cpp
inline bool CheckExistsMul(ull x) {
    if (x == 0) return false;
    ull left  = (A == 0 ? 0 : (A - 1) / x);
    ull right = B / x;
    return right > left; // floor(b/x) - floor((a-1)/x) >= 1
}
```

#### 2).
```cpp
inline bool CheckExistsMul(ull x) {
	return A + ((x - (A % x)) % x) <= B;
}
```