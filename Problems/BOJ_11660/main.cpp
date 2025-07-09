#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, int> pll;

int N = 0, M = 0;
ll MT[2020][2020] = {0,};
ll INTEGRALS_MT[2020][2020] = {0,};

void HandleInput(istream& ins);
void HandleQuery(const char* FILE_PATH);


void PRINT_MT(ll arr[][2020], int n) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            cout << arr[i][j] << ' ';
        } cout << '\n';
    }
}

void HandleInput(istream& ins) {
    ins >> N >> M;
    for(int i = 1 ; i <= N; i++) {
        for(int j = 1 ; j <= N; j++) {
            ins >> MT[j][i];
            INTEGRALS_MT[j][i] = MT[j][i] + (INTEGRALS_MT[j-1][i] + INTEGRALS_MT[j][i-1]) - (INTEGRALS_MT[j-1][i-1]);
        }
    }
    
    // cout << "MT :" << '\n';
    // PRINT_MT(MT, N);
    // cout << '\n';

    // cout << "INTEGRALS_MT :" << '\n';
    // PRINT_MT(INTEGRALS_MT, N);

    pii p1, p2; 
    for(int i = 0; i < M; i++) {
        ins >> p1.X >> p1.Y >> p2.X >> p2.Y;
        // cout << "p1 : " << p1.X << " " << p1.Y << "| p2 : " << p2.X << " " << p2.Y << '\n';
        if(p2.X < p1.X) swap(p2.X, p1.X);
        if(p2.Y < p1.Y) swap(p2.Y, p1.Y);
        // cout << "p1 : " << p1.X << " " << p1.Y << "| p2 : " << p2.X << " " << p2.Y << '\n';
        p1.X--; p1.Y--;
        cout << (INTEGRALS_MT[p2.Y][p2.X] + INTEGRALS_MT[p1.Y][p1.X]) - (INTEGRALS_MT[p2.Y][p1.X] + INTEGRALS_MT[p1.Y][p2.X]) << '\n';
    }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) 
        HandleInput(fs);
}

int main(int argc, const char* argv[]) {
    if(argc > 1) HandleQuery(argv[1]);
    else {
        ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}