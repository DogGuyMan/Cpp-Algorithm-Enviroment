### vector 배열 기반 큰수 뎃셈

```cpp
void AssignULL(bigint& bigint_ref,const ull& lhs) {
	if(!bigint_ref.empty()) bigint_ref.clear();
	if(lhs == 0) {
		bigint_ref.push_back(0);
		return;
	}
	ull temp = lhs;
	while(temp) {
		bigint_ref.push_back(temp % 10);
		temp/=10;
	}
	if(bigint_ref.size() > 1)
		reverse(bigint_ref.begin(), bigint_ref.end());
}

void AddBigint(const bigint &lhs, const bigint &rhs, bigint& out_ref)
{
	int carry = 0;
	int lSize = lhs.size();
	int rSize = rhs.size();
	while (lSize || rSize)
	{
		char lnum = 0, rnum = 0;
		if (lSize > 0)
		{
			lnum = lhs[lSize - 1];
			lSize--;
		}
		if (rSize > 0)
		{
			rnum = rhs[rSize -1];
			rSize--;
		}
		char deciSum = lnum + rnum + carry;
		out_ref.push_back(deciSum % 10);
		carry = deciSum/10;
	}
	if(carry) {
		out_ref.push_back(1);
	}
	reverse(out_ref.begin(), out_ref.end());
}

ostream& operator<<(ostream& os, const bigint& rhs) {
	for(const char& d : rhs) { os << (int)d;}
	return os;
}
```

### 고속 푸리에 변환 

https://greeksharifa.github.io/algorithm%20&%20data%20structure/2018/07/07/algorithm-FFT/

