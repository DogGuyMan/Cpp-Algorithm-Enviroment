#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
const ull INF = 1e9;

ull DP[111] = {0,};
int T;

void HandleInput(istream& ins) {
    DP[0] =1, DP[1] = 1, DP[2] = 1, DP[3] = 2; 
    DP[4] = 2;
    for(int i = 5; i <= 100; i++) { DP[i] = DP[i-5] + DP[i-1]; }
    ins >> T;
    while(T--) {
        int N; ins >> N;
        cout << DP[N-1] << '\n';
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