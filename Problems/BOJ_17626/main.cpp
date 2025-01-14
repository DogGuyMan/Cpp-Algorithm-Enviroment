#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#define Y first 
#define X second 
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int INF = 50505;

int N;
int DP[INF] = {0,};

void HandleInput(istream& ins) {
    ins >> N; 
    int tmpN = N;
    for(int i = 0; i < INF; i++) {DP[i] = INF;}
    DP[0] = INF; DP[1] = 1; DP[2] = 2;
    DP[3] = 3; DP[4] = 1; DP[5] = 2;
    for(int i = 6; i <= N; i++) {
        for(int j = 1; j*j <= i; j++) {
            if(j*j == i) {DP[i] = 1; break;}
            else DP[i] = min(DP[i-(j*j)]+1, DP[i]);
        }
    }
    cout << DP[N] << '\n';
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