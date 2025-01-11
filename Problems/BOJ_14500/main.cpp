#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#define DEBUG 0
#define X first
#define Y second
using namespace std;
typedef vector<vector<int>> matrix;
typedef pair<int,int> pii;

// N : 세로, M : 가로
int N, M;
matrix MT;
vector<vector<pii>> Shapes = {
    {
        {0,0},{1,0},{2,0},{3,0}
    },
    {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3}
    },
    {
        {0, 0}, {1, 0},
        {0, 1}, {1, 1} 
    },
    {//T
        {0,0},{1,0},{2,0}
             ,{1,1}
    },
    {
              {1,0},
        {0,1},{1,1},{2,1}
    },
    {
              {1, 0},
        {0,1},{1, 1},
              {1, 2},
    },
    {
        {0, 0},
        {0, 1},{1, 1},
        {0, 2},
    },
    {//S
                {1,0},{2,0},
        {0, 1},{1,1} 
    },
    {
        {0,0},{1,0},
              {1,1}, {2,1}
    },
    {
        {0, 0},
        {0, 1},{1, 1},
               {1, 2},
    },
    {
               {1, 0},
        {0, 1},{1, 1},
        {0, 2},
    },
    {//L
                    {2,0},
        {0,1},{1,1},{2,1}
    },
    {
        {0,0},{1,0},{2,0},
                    {2,1},
    },
    {
        {0,0},{1,0},{2,0},
        {0,1},
    },
    {
        {0,0},
        {0,1},{1,1},{2,1},
    },
    {
        {0, 0},
        {0, 1},
        {0, 2},{1, 2}
    },
    {
               {1, 0},
               {1, 1},
        {0, 2},{1, 2},
    },
    {
        {0, 0},{1, 0},
        {0, 1},
        {0, 2}
    },
    {
        {0, 0},{1, 0},
               {1, 1},
               {1, 2}
    },
};

void ShapeTest() {
    for(auto& prs : Shapes) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                bool displayFlag = false;
                for(auto& pr : prs) {
                    if(i == pr.Y && j == pr.X) {
                        displayFlag = true;
                        break;
                    }
                }
                displayFlag
                    ? cout << setw(2) << 1
                    : cout << setw(2) << 0;
            }
            cout << '\n';
        }
        cout << "\n\n";
    }
}

void PrintMT(const matrix& mt) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++)  {
            cout << setw(4) << mt[i][j];
        }
        cout << '\n';
    }
}

bool IsInBound(const vector<pii>& shape, const pii& pos) {
    for(const auto& pr : shape) {
        if(!(0 <= (pos.X + pr.X) && (pos.X + pr.X) < M)) {return false;}
        if(!(0 <= (pos.Y + pr.Y) && (pos.Y + pr.Y) < N)) {return false;}
    }
    return true;
}

int AccumulateShape(const matrix& mt, const vector<pii>& shape, const pii& pos) {
    int sum = 0;
    for(const auto& pr : shape) {
        sum += mt[pos.Y + pr.Y][pos.X + pr.X];
    }
    return sum;
}

void HandleInput(istream& ins) {
    ins >> N >> M;
    MT = matrix(N, vector<int>(M));
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < M; j++)  {
            ins >> MT[i][j];
        }
    int mx = -1234567890;
    for(const auto& shape : Shapes){
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++)  {
                pii startPos = {j,i};
                if(IsInBound(shape, startPos)) {
                    mx = max(mx, AccumulateShape(MT, shape, startPos));
                }
            }
        }
    }
    cout << mx << '\n';
    // PrintMT(MT);
    // ShapeTest();
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
