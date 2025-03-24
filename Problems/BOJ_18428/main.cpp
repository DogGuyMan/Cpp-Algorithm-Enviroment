#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#define Y first
#define X second
#define DEBUG 0
#define FS_DEBUG 0
using namespace std;
typedef pair<int, int> pii;
pii operator* (pii& lhs, const int mul) {
    pii res {lhs.Y * mul, lhs.X * mul};
    return res;
}
pii operator+ (pii& lhs, pii& rhs) {
    pii res {lhs.Y + rhs.Y, lhs.X + rhs.X};
    return res;
}
pii operator- (pii& lhs, pii& rhs) {
    pii res {lhs.Y - rhs.Y, lhs.X - rhs.X};
    return res;
}
ostream& operator << (ostream& os, pii& rhs) {
    os << rhs.Y << ' ' << rhs.X;
    return os;
}

pii dir[4] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int N;
string RES_FLAG = "YES";
char mt[8][8] = {0,};

void PRINT_MATRIX(int rM, int cM) {
    for(int i = 0; i < rM; i++) {
        for(int j = 0; j < cM; j++) {
            cout << mt[i][j] << ' ';
        } 
        cout << '\n';
    }
}

bool IsInBound(pii pos) {
    if(0 <= pos.Y&& pos.Y  <= N && 0 <= pos.X && pos.X <= N) {
        return true;
    }
    return false;
}

map<pii, vector<pii>> uniquePoints;
vector<pair<pii, pii>> FindedPoints;
vector<pii> TPoints;
vector<pii> SPoints;

void FindStudent(pii from) {
#if FS_DEBUG
        cout << "CurPos" << '\n';
        cout << from << '\n';
#endif
    for(int i = 0; i < 4; i++) {
#if FS_DEBUG
        cout << "Look Dir" << '\n';
        cout << dir[i] << '\n';
#endif
        for(int dis = 1; dis <= N; dis++) {
            pii forwardPoint = dir[i] * dis;
            pii curPoint = forwardPoint + from;
            if(!IsInBound(curPoint)) continue;
#if FS_DEBUG
            cout << curPoint << '\n';
#endif
            if(mt[curPoint.Y][curPoint.X] == 'S') {
                pii findPoint = curPoint - dir[i];
#if FS_DEBUG
                cout << "Find Point" << '\n';
                cout << "["<< findPoint << "]"<< '\n';
#endif
                uniquePoints[findPoint].push_back(dir[i]);
                FindedPoints.push_back({from, findPoint});
                break;
            }
        }
    }
}

/*
만약 발견 포인트가 선생 그 자기 자신이면 바로 리턴
*/

void HandleInput(istream& ins) {
    ins >> N;
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++)  {
            ins >> mt[i][j];
            if(mt[i][j] == 'T') TPoints.push_back({i, j});
            if(mt[i][j] == 'S') SPoints.push_back({i, j});
        }
    for(const auto& tPos : TPoints) {
        FindStudent(tPos);
    }

    #if DEBUG
    PRINT_MATRIX(N, N);
    cout << "T" << '\n';
    for(const auto& t : TPoints) {
        cout << t.Y << ' ' << t.X << '\n';
    } cout << '\n';
    cout << "S" << '\n';
    for(const auto& s : SPoints) {
        cout << s.Y << ' ' << s.X << '\n';
    } cout << '\n';

    cout << "FindedPoints" << '\n';
    for(const auto& fPos : FindedPoints) {
        pii from = fPos.first;
        pii findedAt = fPos.second;
        if(from.X == findedAt.X && from.Y == findedAt.Y) {
            RES_FLAG = "NO";
            return;
        }
    } cout << '\n';
#endif

    for(const auto& fPos : FindedPoints) {
        pii from = fPos.first;
        pii findedAt = fPos.second;
        #if DEBUG
        cout << "["<< from << "->" << findedAt << "]" << '\n';
        #endif
        if(from.X == findedAt.X && from.Y == findedAt.Y) {
            cout << "NO" << '\n';
            return;
        }
    }
    
    for(const auto& uPos : uniquePoints) {
        auto dirs = uPos.second;
        pii startPoint = uPos.first;
        for(auto dir : dirs) {
            for(int dis = 1; dis <= N; dis++) {
                pii forwardPoint = dir * dis;
                pii curPoint = forwardPoint + startPoint;
                if(mt[curPoint.Y][curPoint.X] == 'T' || mt[curPoint.Y][curPoint.X] == 'S') break;
                if(!IsInBound(curPoint)) continue;
                map<pii, vector<pii>>::iterator dupli = uniquePoints.find(curPoint);
                if(dupli != uniquePoints.end()) {
                    for(vector<pii>::iterator dupliDirIt = uniquePoints[curPoint].begin(); dupliDirIt != uniquePoints[curPoint].end(); dupliDirIt++){
                        if((*dupliDirIt).X == dir.X && (*dupliDirIt).Y == dir.Y) {
                            uniquePoints[curPoint].erase(dupliDirIt);
                        }
                    }
                }
            }
        }
    }
//
    for(const auto& uPos : uniquePoints) {
        auto dirs = uPos.second;
        if(dirs.size() > 0){
            mt[uPos.first.Y][uPos.first.X] = 'O';
        }
    }
    PRINT_MATRIX(N, N);
//
    if(uniquePoints.size() > 3) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
}

vector<pii> findNearPoint;

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}
int main(int argc, const char* args[]) {
    if(argc > 1) {
        HandleQuery(args[1]);
    }
    else {
        HandleInput(cin);
    }
}