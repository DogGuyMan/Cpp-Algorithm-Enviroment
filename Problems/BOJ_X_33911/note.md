```cpp
#include <iostream>

using namespace std;
int cnt[105];

int main(void) {
    int n, a, b, c;
    cin >> n;
    int res = 0;
    for(int i = 0; i < n; i++) {
        cin >> a >> b >> c;
        cnt[a]++;
        cnt[b]++;
        cnt[c]++;
    }
    int deletecnt = 0;
    int skip = 0;
    for(int i = 100; i >= 1; i--) {
        if(cnt[i] > 1) {
            skip++;
            continue;
        }
        else if(cnt[i] == 1) {
            deletecnt++;
            skip++;
            if(deletecnt > 2) break;
        } 
        else res += (deletecnt>0?1:i-1+skip) * (deletecnt>1?1:i-2+skip) / (deletecnt==0?2:1);
    }
    cout << res << "\n";
}
```

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool f(vector<int>& v, int p1, int p2, int p3)
{
	++v[p1];
	++v[p2];
	++v[p3];

	bool possible = (v[p1] == 1 || v[p2] == 1 || v[p3] == 1);

	if (possible) {
		for (int i = (v[p3] == 1 ? p3 + 1 : (v[p2] == 1 ? p2 + 1 : p1 + 1)); i <= 100; ++i) {
			if (v[i] == 1) {
				possible = false;
				break;
			}
		}
	}

	--v[p1];
	--v[p2];
	--v[p3];
	return possible;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	cin >> N;

	vector<int> v(101);

	for (int num; cin >> num;)
		++v[num];

	int res = 0;

	for (int i = 1; i <= 100; ++i) {
		for (int j = i + 1; j <= 100; ++j) {
			for (int k = j + 1; k <= 100; ++k)
				res += f(v, i, j, k);
		}
	}

	cout << res;
}
```

```cpp
#include <stdio.h>

int d[105],ans;

int main()
{
    int i,j,k,l,n;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        d[a]++;
        d[b]++;
        d[c]++;
    }
    for(i=1;i<=100;i++)
    {
        for(j=i+1;j<=100;j++)
        {
            for(k=j+1;k<=100;k++)
            {
                d[i]++;
                d[j]++;
                d[k]++;
                for(l=100;l>=1;l--)
                {
                    if(d[l] == 1)break;
                }
                if(l == i || l == j || l == k)ans++;
                d[i]--;
                d[j]--;
                d[k]--;
            }
        }
    }
    printf("%d",ans);
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
	cin.tie(0)->sync_with_stdio(0);
	
	int n;
	cin >> n;
	vector<int>A(101);
	for(int i=0; i < n; i++){
		int a,b,c;
		cin >> a >> b >> c;
		A[a]++;A[b]++;A[c]++;
	}
	
	auto ok=[&](int x){
		if(A[x] != 1) return false;
		int r = x + 1;
		while(r <= 100){
			if(A[r] == 1) return false;
			r++;
		}
		return true;
	};

	int ans = 0;
	for(int i=1; i <= 100; i++){
		for(int j=i+1; j <= 100; j++){
			for(int k=j+1; k <= 100; k++){
				A[i]++;A[j]++;A[k]++;
				if(ok(i) || ok(j) || ok(k)) ans++;
				A[i]--;A[j]--;A[k]--;
			}
		}
	}
	cout << ans;
	
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, tmp, res = 0, cont = 0; cin >>n;
    int arr[101] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> tmp;
            arr[tmp]++;
        }
    }
    for (int i = 1; i <= 100; i++) {
        for (int j = i+1; j <= 100; j++) {
            for (int k = j+1; k <= 100; k++) {
                arr[i]++; arr[j]++; arr[k]++;
                for (int x = 100; x > 0; x--) {
                    if (arr[x] == 1) {
                        if (x == i || x == j || x == k) res++;
                        break;
                    }
                }
                arr[i]--; arr[j]--; arr[k]--;
            }
        }
    }
    cout << res;
    return 0;
}
```

```cpp
#include <iostream>
using namespace std;

int main(void){
    ios::sync_with_stdio(0); cin.tie(0);
    int a[102]{0};
    int n,v; cin >> n;
    for (int i = 0; i < 3*n; i++){
        cin >> v;
        a[v]++;
    }
    int ans = 0;
    for (int p = 100; p >= 1; p--){
        for (int q = p - 1; q >= 1; q--){
            for (int r = q - 1; r >= 1; r--){
                a[p]++;
                a[q]++;
                a[r]++;
                for (int c = 100; c >= r; c--){
                    if (a[c] == 1){
                        ans += (c == p || c == q || c == r);
                        break;
                    }
                }
                a[p]--;
                a[q]--;
                a[r]--;
            }
        }
    }
    cout << ans << "\n";
}
```