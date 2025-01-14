#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define Y first
#define X second
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DEBUG 0
using namespace std;
typedef pair<int,int> pii;

// 그래프 탐색 문제.
// 6*6*6*6*6*6*6...
// DP 문제.
// 1로가기 위해 최소 무브, 2로 가기위해 최소 무브... 

    
// #if DEBUG
//     for(int i = 1; i <= 10; i++){
//         for(int j = 1; j <= 10; j++) {
//             cout << setw(3) << G[i][j] << ' ';
//         }
//         cout << '\n';
//     }
//     for(int i = 1; i <= 10; i++){
//         for(int j = 1; j <= 10; j++) {
//             cout << setw(3) << GetValByPair(i, j) << ' ';
//         }
//         cout << '\n';
//     }
// #endif

int N, M;

int GetValByPair(int y, int x) {
    return ((y-1) * 10) + x;
}
pii GetPairByVal(int val) {
    return {((val-1) / 10)+1, ((val-1) % 10)+1};
}

int Portal[111] = {0,};
int G[22][22] = {0,};
bool IsVisit[22][22] = {false,};

void HandleInput(istream& ins) {
    ins >> N >> M;
    int from, to;
    for(int i = 0; i < N; i++) {
        ins >> from >> to;
        Portal[from] = to;
    }
    for(int j = 0; j < M; j++) {
        ins >> from >> to;
        Portal[from] = to;
    }
    int cnt = 1;
    for(int i = 1; i <= 100; i++) {
        G[(i/10)+1][(i%10)+1] = cnt;
        if((i)%6 == 0) {cnt++;}
    }

    G[1][1] = 0;
    if(Portal[1] == 100) {cout << 0 << '\n'; return;}
    queue<int> q; q.push(1);

    int depth = 0; bool breakFlag = false;
    while(!q.empty()) {
        int qSz = q.size();
        for(int i = 0; i < qSz; i++) {
            int curIdx = q.front(); q.pop();
            pii curPos = GetPairByVal(curIdx);
            if(curIdx == 100) {
                cout << depth << '\n'; breakFlag = true; break;
            }
            if(IsVisit[curPos.Y][curPos.X]) {continue;}
            IsVisit[curPos.Y][curPos.X] = true;
#if DEBUG
            cout << depth << '\n';
            cout << " idx : " << curIdx << " pos : " << curPos.Y << " " << curPos.X << '\n';
#endif
            for(int j = 1; j <=6; j++) {
                int nxtIdx = curIdx + j;
                pii nxtPos = GetPairByVal(nxtIdx);
                if(1 <= nxtIdx && nxtIdx <= 100 && !IsVisit[nxtPos.Y][nxtPos.X] ) {
                    if(Portal[nxtIdx] != 0) { q.push(Portal[nxtIdx]); }
                    else { q.push(nxtIdx); }
                }
            }
        }
        if(breakFlag) break;
        depth++;
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