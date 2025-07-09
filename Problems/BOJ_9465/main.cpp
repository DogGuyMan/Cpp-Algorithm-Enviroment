#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<long long,long long> pll;

int T;

void DEBUG_PRINT(string params[], int N) {
    for(int i = 0; i < N; i++) {
        cout << params[i] << ' ';
    }
    cout << '\n';
}

void HandleInput(istream & ins) {
    ins >> T;
    // DEBUG_PRINT((string[]) {to_string(T)}, 1);
    while(T--) {
        int N; ins >> N;
        vector<int> stickers[2] = {vector<int>(N, 0), vector<int>(N, 0)};
        vector<int> dp[2] = {vector<int>(N, 0), vector<int>(N, 0)};
        // DEBUG_PRINT((string[]) {to_string(N)}, 1);
        for(int i = 0; i < N; i++) {
            ins >> stickers[0][i];
            // sum[0] += (stickers[0][i] * ((i + 0) % 2));
            // sum[1] += (stickers[0][i] * ((i + 1) % 2));
            // DEBUG_PRINT((string[]) {to_string(stickers[0][i])}, 1);
        }
        for(int i = 0; i < N; i++) {
            ins >> stickers[1][i];
            // sum[0] += (stickers[1][i] * ((i + 1) % 2));
            // sum[1] += (stickers[1][i] * ((i + 0) % 2));
            // DEBUG_PRINT((string[]) {to_string(stickers[1][i])}, 1);
        }
        dp[0][0] = stickers[0][0];
        dp[1][0] = stickers[1][0];
        if(N == 1){
            cout << max(dp[0][0], dp[1][0]) << '\n';
            continue;
        }
        dp[0][1] = stickers[0][1] + dp[1][0];
        dp[1][1] = stickers[1][1] + dp[0][0];
        if(N == 2) {
            cout << max(dp[0][1], dp[1][1]) << '\n';
            continue;
        }
        dp[0][2] = max(max(stickers[0][2] + dp[1][0], stickers[0][2] + dp[0][0]), stickers[0][2] + dp[1][1]);
        dp[1][2] = max(max(stickers[1][2] + dp[0][0], stickers[1][2] + dp[1][0]), stickers[1][2] + dp[0][1]);
        if(N == 3) {
            cout << max(dp[0][2], dp[1][2]) << '\n';
            continue;
        }
        for(int i = 3; i < N; i++) {
            dp[0][i] = max(
                max(stickers[0][i] + dp[1][i-2], stickers[0][i] + dp[0][i-2]), 
                stickers[0][i] + dp[1][i-1]
            );
            dp[1][i] = max(
                max(stickers[1][i] + dp[0][i-2], stickers[1][i] + dp[1][i-2]), 
                stickers[1][i] + dp[0][i-1]
            );
        }
        cout << max(dp[0][N-1], dp[1][N-1]) << '\n';
    }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open())
        HandleInput(fs);
}

int main(int argc, const char* argv[]) {
    if(argc > 1)
        HandleQuery(argv[1]);
    else {
        ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}
// 50 10 100 20 40
// 30 50 70 10 60

// 50 10 100 20 40 100
// 30 50 70 10 60 100