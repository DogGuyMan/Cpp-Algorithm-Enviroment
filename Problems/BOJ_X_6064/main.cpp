#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define Y first
#define X second
using namespace std;
#define DEBUG 1
typedef unsigned long long ll;

int T;
int M, N;

pair<int,int> GDCLCM(ll a, ll b) {
    if(b > a) {
        auto tmp = gcd(a, b);
        return {tmp, (a * b) / tmp};
    }
    else {
        auto tmp = gcd(b, a);
        return {tmp, (a * b) / tmp};
    }
}

int GetWave(int x, int y) {
    return (x - y);
}

void HandleInput(istream& ins) {
    ins >> T;
    while(T--) {
        int x, y;
        ins >> M >> N >> x >> y;
        auto MN = GDCLCM(M, N);
        int tmpx = 1, tmpy = 1;
        int res =-1;
#if DEBUG
        // cout << " MN.X : "<< MN.X << " MN.Y : " <<MN.Y << '\n';
#endif
        if(x == M && y == N) {cout << MN.X << '\n'; continue;}
        for(int i = 1; i <= (MN.X); ) {
            if(x == tmpx && y == tmpy) {
                res = i; break;
            }
            if(x == tmpx) {
                tmpx+=M; tmpy+=M;
                tmpx = ((tmpx - 1) % M) + 1;
                tmpy = ((tmpy - 1) % N) + 1;
                i+=M;
            }
            else {
                tmpx++; tmpy++;
                tmpx = ((tmpx - 1) % M) + 1;
                tmpy = ((tmpy - 1) % N) + 1;
                i++;
            }
        }

// #if DEBUG
//         int prev = 0;
//         for(int i = 1; i <= (MN.X); i++) {
//             if(x == tmpx && y == tmpy) {
//                 if(res == -1) {
//                     res = i;
//                     // cout << "\033[1;31m" << setw(8) << GetWave(tmpx, tmpy) << "\033[0m" << ' ';
//                     cout << "\033[1;31m" <<  setw(4) << i << ": 째 <" << " x:" << tmpx << ", " << "y:" << tmpy << ">" << "\033[0m" << '\n';
//                     continue;
//                 }
//             }
//             cout << setw(4) << i << ": 째 <" << " x:" << tmpx << ", " << "y:" << tmpy << ">" << '\n';
//             tmpx++; tmpy++;
//             tmpx = ((tmpx - 1) % M) + 1;
//             tmpy = ((tmpy - 1) % N) + 1;
//             // if(prev != GetWave(tmpx, tmpy)) {
//             //     prev = GetWave(tmpx, tmpy);
//             //     cout << '\n';
//             // }
//             // cout << setw(8) << GetWave(tmpx, tmpy) << ' ';
//         }
// #endif
        cout << res << '\n';
    }
}

void HandleQuery(char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}
