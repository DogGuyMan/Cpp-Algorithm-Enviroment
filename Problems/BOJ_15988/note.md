어떻게 이걸 벡터로 해석한거지.
```cpp
#include <cstdio>
#include <vector>

using namespace std;

const int mod = 1000000009;

using lint = long long;
typedef vector<vector<lint>> matrix;

matrix operator*(matrix& a, matrix& b) {
    matrix res = matrix(a.size(), vector<lint>(b[0].size()));

    for (int y = 0; y < a.size(); y++) {
        for (int x = 0; x < b[0].size(); x++) {
            lint result = 0;
            for (int i = 0; i < a[0].size(); i++) {
                result += a[y][i] * b[i][x] % mod;
                result %= mod;
            }
            res[y][x] = result;
        }
    }

    return res;
}

lint solve(lint n) {
    matrix ret = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    matrix piv = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};

    while (n) {
        if (n & 1) ret = piv * ret;
        piv = piv * piv;
        n >>= 1;
    }

    return ret[0][0];
}

int main() {
    lint n, m;
    scanf("%lld", &n);
    while (n--) {
        scanf("%lld", &m);
        printf("%lld\n", solve(m));
    }
}
```