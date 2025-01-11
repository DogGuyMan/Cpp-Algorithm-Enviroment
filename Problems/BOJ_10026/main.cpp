#include <iostream>
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <bitset>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> matrix;
#define DEBUG 0

const ll INF = 1e9;
int N;
ll Area = -1;
ll AreaNorm = -1;

matrix IsVisitNorm(101, vector<ll>(101));
matrix IsVisit(101, vector<ll>(101));
matrix MT(101, vector<ll>(101));

enum RGB{
    R = 82, G = 71, B = 66
};

// 시계 방향
const pii moves[4] = {
    {0, 1},
    {1,  0},
    {0, -1},
    {-1, 0}
};

ostream& operator<<(ostream& os, const pii& pr) {
    cout << pr.X << " " << pr.Y;
    return os;
}

ostream& operator<<(ostream& os, const matrix& mt) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << setw(4) << mt[i][j] << ' ';
        } cout << '\n';
    }
    return os;
}

bool IsInBound(pii nxtPos) {
    if(!(0 <= nxtPos.X && nxtPos.X < N)) return false;
    if(!(0 <= nxtPos.Y && nxtPos.Y < N)) return false;
    return true;
}

bool IsMovable(const RGB& curTileColor, ll nxt, const bool& isNorm) {
#if DEBUG
    cout << " Cur : " << curTileColor << " Nxt : " << (RGB)nxt << '\n';
#endif
    if(isNorm) return curTileColor == nxt;
    if(curTileColor == RGB::B && nxt == RGB::B) {return true;}
    if(curTileColor == RGB::R || curTileColor == RGB::G) {
        if(nxt != RGB::B) {return true;}
    } 
    return false;
}

// 검증은 MT나 Visit
// 채워지는것은 Visit
void DFS(pii pos, const RGB& c, matrix& vmt, const bool& isNorm) {
    if(vmt[pos.X][pos.Y] < 0) return;

    isNorm 
        ? (vmt[pos.X][pos.Y] = AreaNorm)
        : (vmt[pos.X][pos.Y] = Area);

    for(int i = 0; i < 4; i++) {
        pii nxtPos = {pos.X + moves[i].X, pos.Y + moves[i].Y};
        if((IsInBound(nxtPos) && vmt[nxtPos.X][nxtPos.Y] >= 0) && IsMovable(c, MT[nxtPos.X][nxtPos.Y], isNorm)) {
#if DEBUG
            cout << " nxtPos : " << nxtPos << '\n';
#endif
            DFS(nxtPos, c, vmt, isNorm);
        }
    }
}


void HandleInput(istream& ins) {
    ins >> N; 
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char c; ins >> c;
            MT[i][j] = (int)c;
        }
    }
#if DEBUG
    cout << MT << '\n';
    cout << IsVisit << '\n';
#endif
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(IsVisit[i][j] >= 0) {
                DFS({i, j}, (RGB)MT[i][j], IsVisit, false);
                Area--;
#if DEBUG
                cout << IsVisit << '\n';
#endif
            }
            if(IsVisitNorm[i][j] >= 0) {
                DFS({i, j}, (RGB)MT[i][j], IsVisitNorm, true);
                AreaNorm--;
#if DEBUG
                cout << IsVisitNorm << '\n';
#endif
            }
        }
    }
    cout << -(AreaNorm+1) << " " << -(Area+1) << '\n';
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