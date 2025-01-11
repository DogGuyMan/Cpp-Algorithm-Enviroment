#include <iostream>
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstring>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define DEBUG 0
typedef long long ll;
const ll INF = 1234567890;

struct Person {
    int Pnum = 0; 
    ll DistSum = INF;
};

bool operator<(const Person& lhs, const Person& rhs) {
    if(lhs.DistSum == rhs.DistSum) {
        return lhs.Pnum < rhs.Pnum;
    }
    return lhs.DistSum < rhs.DistSum;
}

int N, M;
ll DP[111][111] = {0,};
Person Min = {INF, INF};

void PrintArr() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << setw(10) << DP[i][j] << ' ';
        }
        cout << '\n';
    }
}

void HandleInput(istream& ins) {
    ins >> N >> M;
    for(int i = 1; i <= N; i++) { 
        for(int j = 1; j <= N; j++) { 
            DP[i][j] = INF;
        }
    }    
    for(int i = 0; i < M; i++) {
        ll from, to; ins >> from >> to;                
        DP[from][from] = 0;
        DP[to][to] = 0;
        DP[from][to] = 1;
        DP[to][from] = 1;
    }
#if DEBUG
    cout << "Before" << '\n';
    PrintArr();
#endif

    // 1. 플루이드 워셜 DP 채우기
    for(int k = 1; k <= N; k++) {
        for(int j = 1; j <= N; j++) {
            // DP[i][j] = DP[i][k] + DP[k][j];
            for(int i = 1; i <= N; i++) {
                ll dist = DP[i][k] + DP[k][j];
                if(DP[i][j] > dist) {
                    DP[i][j] = dist;
                    DP[j][i] = dist;
                }
            }
        }
    }
#if DEBUG
    cout << "After" << '\n';
    PrintArr();
#endif

    // 2. 모든 사람들과 관계에서 거리가 제일 짧은 사람 구하기
    for(int i = 1; i <= N; i++) {
        ll sum = accumulate(DP[i] +1, DP[i]+N+1, 0L);
#if DEBUG
        cout << sum << '\n';
#endif
        if(Min.DistSum > sum) {
            Min.DistSum = sum;
            Min.Pnum = i;
        }
#if DEBUG
        cout << " Min.Pnum : " << Min.Pnum << " Min.DistSum : " << Min.DistSum << '\n';
#endif
    }
    cout << Min.Pnum << '\n';
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