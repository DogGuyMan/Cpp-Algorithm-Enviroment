#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define X second
#define Y first
typedef pair<int,int> Pii;
const int MINVAL = -1234567890;

int R = 0; int C = 0;

vector<Pii> Dir {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1},
};

struct Cell {
    int height = MINVAL;
    int flow = MINVAL;
    Pii nxt = {MINVAL, MINVAL};
    Pii dest = {MINVAL, MINVAL};
    int cnt = 0;
};

vector<vector<Cell>> Board = vector<vector<Cell>>(505, vector<Cell>(505));

Pii operator+(Pii& lhs, Pii rhs) {
    Pii res {lhs.first + rhs.Y, lhs.X + rhs.X};
    return res;
} 

Pii operator-(Pii& lhs, Pii rhs) {
    Pii res {lhs.first - rhs.Y, lhs.X - rhs.X};
    return res;
} 

bool IsOutOfBound(int y, int x) {
    if(0 > y || y >= R) return true;
    if(0 > x || x >= C) return true;
    return false;
}


// DFSPerNodeAndUnion(vector<Pii> Empty, initPar)
Pii DFSPerNodeAndUnion(vector<Pii>& prevs) {
    Pii prevPii = {prevs.back().Y, prevs.back().X};
    if(Board[prevPii.Y][prevPii.X].dest.Y >= 0 && Board[prevPii.Y][prevPii.X].dest.X >= 0) { 
        prevs.pop_back();
        return Board[prevPii.Y][prevPii.X].dest;
    }
    if(Board[prevPii.Y][prevPii.X].flow <= 0) return prevPii;
    Pii nxtPos = Board[prevPii.Y][prevPii.X].nxt;
    prevs.push_back(nxtPos);
    return DFSPerNodeAndUnion(prevs);
}

void HandleInput(istream& ins) {
    
    ins >> R >> C;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            int h; ins >> h;
            Board[i][j].height = h;

            // cout << Board[i][j].height << ' ';
        }   // cout << '\n';
    }
    
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            for(const auto& dir : Dir) {
                Pii nxt = {dir.Y + i, dir.X + j};
                if(IsOutOfBound(nxt.Y, nxt.X)) continue;
                int flow = Board[i][j].height - Board[nxt.Y][nxt.X].height;
                if(flow > Board[i][j].flow) {
                    Board[i][j].flow = flow;
                    Board[i][j].nxt = nxt;
                }
            }
            // cout << setw(12) << Board[i][j].nxt.Y << ',' << Board[i][j].nxt.X;
        }   // cout << '\n';
    }
    
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            vector<Pii> backTrack; backTrack.push_back({i,j});
            Pii dest = DFSPerNodeAndUnion(backTrack);
            // cout << dest.Y << ',' << dest.X << '\n';
            for(const auto& backPii : backTrack){
                // cout << setw(12) << backPii.Y << ',' << backPii.X << '/';
                Board[backPii.Y][backPii.X].dest = dest;
            } // cout << '\n';
            // cout << setw(12) << Board[i][j].dest.Y << ',' << Board[i][j].dest.X << ' ';
        }   // cout << '\n';
    }

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            Pii destPii = Board[i][j].dest;
            Board[destPii.Y][destPii.X].cnt++;
        }
    }

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << Board[i][j].cnt << ' ';
        } cout << '\n';
    }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) { HandleInput(fs); }
}

int main(int argc, const char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        HandleQuery(args[1]);
    }
}