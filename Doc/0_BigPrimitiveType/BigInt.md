### Big Int의 구현
```cpp
typedef deque<int> bigint;
```

#### 0). 유틸리티

불필요한 임시 제거: 
```
out = other; // 한 번의 복사 대입
```

```cpp
ostream& operator<<(ostream& os, const bigint& rhs) {
	for(const auto& d : rhs) { os << (int)d;}
	return os;
}
```

```cpp
inline void Trim(bigint &fill_zero)
{
	while (fill_zero.size() > 1 && fill_zero.front() == 0)
		fill_zero.pop_front();
}
```

```cpp
int Cmp(const bigint &a, const bigint &b)
{
	if (a.size() != b.size())
		return (a.size() < b.size()) ? -1 : 1;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] != b[i])
			return (a[i] < b[i]) ? -1 : 1;
	}
	return 0;
}
```

```cpp
void BigIntAssign(ull val, bigint &out)
{
	if (val < 10)
	{
		out = {(int)val};
		return;
	}
	while (val > 0)
	{
		out.push_front(val % 10);
		val /= 10;
	}
}
```

#### 1). 덧셈

```cpp
void BigIntAdd(const bigint &lhs, const bigint &rhs, bigint &out)
{
	out.clear();
	int l = lhs.size() - 1;
	int r = rhs.size() - 1;
	int carry = 0;
	while (l >= 0 || r >= 0 || carry)
	{
		int a = (l >= 0 ? lhs[l--] : 0);
		int b = (r >= 0 ? rhs[r--] : 0);
		int s = a + b + carry;
		out.push_front(s % 10);
		carry = s / 10;
	}
	Trim(out);
}
```

#### 2). 뺄셈

```cpp
void BigIntSub(const bigint &lhs, const bigint &rhs, bigint &out)
{
	bool cmpRes = Cmp(lhs, rhs);
	if (cmpRes <= 0)
	{
		out = {0};
		return;
	}
	int l = lhs.size() - 1, r = rhs.size() - 1;
	int borrow = 0;
	while (l >= 0 || r >= 0 || borrow)
	{
		int a = (l >= 0 ? lhs[l--] : 0);
		int b = (r >= 0 ? rhs[r--] : 0);
		int s = a - b - borrow;
		if (s < 0)
		{
			s += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		out.push_front(s);
	}
	Trim(out);
}

```

#### 3). 곱셈

```cpp
void BigIntMulSmall(const bigint &big_int, int m, bigint &out)
{
	if (m == 0)
	{
		out = {0};
		return;
	}
	if (m == 1)
	{
		out = big_int;
		return;
	}
	out.clear();
	int sz = big_int.size() - 1;
	int carry = 0;
	while (sz >= 0 || carry)
	{
		int deci = (sz >= 0) ? big_int[sz--] : 0;
		deci = (m * deci) + carry;
		out.push_front(deci % 10);
		carry = deci / 10;
	}
	Trim(out);
}
```

#### 4).