```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int iter;
	long long _min = LONG_MAX, s = 0;
	
	cin >> iter;
	
	auto v = vector<long long>(iter);
	
	for(auto& i: v)
	    cin >> i;
	    
	for(auto i = v.rbegin();i!=v.rend();i++){
	    if(_min > *i)
	        _min = *i;
	    s += _min;
	}
	
	print("{}\n", s);

	return 0;
}
```