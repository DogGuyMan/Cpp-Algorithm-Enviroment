#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DEBUG 1
#define Y first
#define X second
using namespace std;
typedef pair<int,int> pii ;

int N, M;
char G[606][606];
bool IsVisit[606][606] = {0,};
int res = 0;

template <typename T>
void PrintG(T (&arr)[606][606]) {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++) {
            cout << arr[i][j] << ' ';
        } cout << '\n';
    }
}

pii operator+(const pii& lhs, const pii& rhs) {
    return {lhs.Y + rhs.Y, lhs.X + rhs.X};
}

vector<pii> moves { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void HandleInput(istream& ins) {
    queue<pii> q; 
    ins >> N >> M;
    for(int i =0; i < N; i++)
        for(int j =0; j < M; j++) {
            ins >> G[i][j];
            if(G[i][j] == 'I') {
                q.push({i,j});
            }
        }
    while(!q.empty()) {
        int qSz = q.size();
        for(int i = 0; i < qSz; i++) {
            pii curPos = q.front(); q.pop();
            if(IsVisit[curPos.Y][curPos.X]) { continue; }
            IsVisit[curPos.Y][curPos.X] = true;
            if(G[curPos.Y][curPos.X] == 'P') {res++;}
            for(const auto& move : moves) {
                pii nxtPos = curPos + move;
                if(
                    (0<= nxtPos.Y && nxtPos.Y < N) && (0<= nxtPos.X && nxtPos.X < M) &&
                    G[nxtPos.Y][nxtPos.X] != 'X'
                ) {
                    q.push(nxtPos);
                }
            }
        }
        // cout << '\n';
        // PrintG<bool>(IsVisit);
    }
    res == 0 
        ? cout << "TT" << '\n'
        : cout << res << '\n';
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