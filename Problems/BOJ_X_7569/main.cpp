#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#define DEBUG 1
using namespace std;
#define X first
#define Y second.first
#define Z second.second
typedef pair<int,pair<int,int>> Vector3;
typedef vector<vector<int>> matrix;
typedef vector<vector<vector<int>>> cube;

int M, N, H;
int MxDepth = 0;

cube CB(111, matrix(111, vector<int>(111)));

ostream& operator<<(ostream& os, const Vector3& vec){
    cout << vec.X << " " << vec.Y << " " << vec.Z;
    return os;
}
ostream& operator<<(ostream& os, const cube& cb){
    for(int k = 0; k < H; k++) {
        for(int i = 0; i < N; i++) {
            for(int g = 0; g < i; g++) { cout << "   "; }
            for(int j = 0; j < M; j++) {
                os << setw(6) << "\033[1;" << (30+i) << "m" << cb[k][i][j] << "\033[0m" <<  ' ';
            } cout << '\n';
        }
    }
    return os;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
    Vector3 res;
    res = {lhs.X + rhs.X, {lhs.Y + rhs.Y, lhs.Z + rhs.Z}};
    return res;
}

int& IndexingCubeByVector(cube& lhs, const Vector3& idx) {
    return lhs[idx.Z][idx.Y][idx.X];
}

Vector3 moves[6] = {
    {1, {0, 0}},
    {-1, {0, 0}},
    {0, {0, 1}},
    {0, {0, -1}},
    {0, {1, 0}},
    {0, {-1, 0}},
};


bool IsInBound(Vector3 vec) {
    if(!(0 <= vec.X && vec.X < M)) return false;
    if(!(0 <= vec.Y && vec.Y < N)) return false;
    if(!(0 <= vec.Z && vec.Z < H)) return false;
    return true;
}

bool IsFilled(const cube& cb) {
    for(int k = 0; k < H; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(cb[k][i][j] == 0)
                    return false;
            }
        }
    }
    return true;
}


void HandleInput(istream& ins) {
    ins >> M >> N >> H;
    queue<Vector3> nxtVecs;

    bool filledByZero = true;
    for(int k = 0; k < H; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                int tmp; ins >> tmp;
                if(tmp == 1) { nxtVecs.push({ j, {i, k}} ); }
                if(tmp == 0) {filledByZero = false;}
                CB[k][i][j] = tmp;
            }
        }
    }
#if DEBUG
        cout << CB << '\n';
#endif
    if(filledByZero) {
        cout << 0 << '\n'; return;
    }

    while(!nxtVecs.empty()) {
        int phaseSize = nxtVecs.size();
        for(int i = 0; i < phaseSize; i++) {
            Vector3 curPos = nxtVecs.front(); nxtVecs.pop();
            for(int i = 0; i < 6; i++) {
                Vector3 nxtPos = curPos + moves[i];
                if(IsInBound(nxtPos) && IndexingCubeByVector(CB, nxtPos) == 0) {
                    IndexingCubeByVector(CB, nxtPos) = MxDepth + 1;
                    nxtVecs.push(nxtPos);
                }
            }
        }
            
        if(!nxtVecs.empty()) {
            MxDepth++;
    #if DEBUG
            cout << " Phase : " << MxDepth << '\n';
            cout << CB << '\n';
    #endif
        }

    }

    IsFilled(CB) 
        ? cout << MxDepth << '\n'
        : cout << -1 << '\n';
}

void HandleQuery(char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}


int main(int argc, char* args[]){
    if(argc <= 1) {
        cin.tie(0)->sync_with_stdio(0);
        HandleInput(cin);
    }
    else {
        char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}
