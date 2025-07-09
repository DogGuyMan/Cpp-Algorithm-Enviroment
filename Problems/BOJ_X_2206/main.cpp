#include <bits/stdc++.h>

using namespace std;
#define X first
#define Y second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
const int MAX = 123456789;
int N = 0, M = 0;
bool MAP[1010][1010] = {0,};
bool IsVisit[2][1010][1010] = {0,};
int ANS = MAX;

pii MV[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

pii operator+(pii lhs, pii rhs) {
    pii newPair = {lhs.X + rhs.X, lhs.Y + rhs.Y};
    return newPair;
}

ostream& operator << (ostream& os, pii& rhs) {
    os << "Y : " << rhs.Y << " X : " << rhs.X << '\n';
    return os;
}

struct BFS_STATE {
    pii node;
    int brk;
    int d;
};

void HandleInput(istream &);
void HandleQuery(const char*);
void PRINT_MT(bool (&arr)[2][1010][1010]) {
    cout << "PRINT START : " << '\n';

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << arr[0][i][j] << ' ';
        } cout << '\n';
    }
    
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << arr[1][i][j] << ' ';
        } cout << '\n';
    }
    cout << "PRINT END: " << '\n';
}

int main(int argc, const char* argv[]) {
    if(argc > 1)
        HandleQuery(argv[1]);
    else {
        ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open())
        HandleInput(fs);
}

bool IsBound(pii pos) {
    bool isYBound = 1 <= pos.Y && pos.Y <= N;
    bool isXBound = 1 <= pos.X && pos.X <= M;
    return isXBound && isYBound;
}

int BFS(bool (&isVisit)[2][1010][1010], BFS_STATE state)
{
    queue<BFS_STATE> q;
    q.push(state);
    while(!q.empty()) {
        BFS_STATE cur = q.front(); q.pop();
        if(isVisit[cur.brk][cur.node.Y][cur.node.X] == true) continue;
        if(cur.brk == 0) isVisit[0][cur.node.Y][cur.node.X] = true;
        isVisit[1][cur.node.Y][cur.node.X] = true;
        // PRINT_MT(isVisit);
        
        if(cur.node.Y == N && cur.node.X == M) return cur.d;
        if(ANS <= state.d) return MAX;

        for(int i = 0; i < 4; i++) {
            BFS_STATE nxt = {cur.node + MV[i], cur.brk, cur.d+1};
            if(!IsBound(nxt.node)) continue;
            if(isVisit[nxt.brk][nxt.node.Y][nxt.node.X]) continue;
            if(MAP[nxt.node.Y][nxt.node.X] == 1 && nxt.brk == 0) 
            {
                nxt.brk = 1;
                q.push(nxt);
            }
            else if (MAP[nxt.node.Y][nxt.node.X] == 0) {
                q.push(nxt);
            }
        }
    }
    return MAX;
}

void HandleInput(istream& ins) {
    ins >> N >> M;
    string str;
    for(int i = 1; i <= N; i++) {
        ins >> str;
        for(int j = 1; j <= M; j++) {
            MAP[i][j] = str[j-1] - '0';
        }
    }

    if(MAP[1][1] == 1 || MAP[N][M] == 1) {cout << -1 << '\n'; return;}
    ANS = min(ANS, BFS(IsVisit, {{1,1}, 0, 1}));
    cout << ((ANS == MAX) ? -1 : ANS) << '\n';
}