#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define DEBUG 1
using namespace std;

const int MAX_LOOP = 10;
int LOOP_CNT = 0;

const int MAX_TILE_SZ = (1 << 8) + 1;
int K; int TS;
int FT[MAX_TILE_SZ][MAX_TILE_SZ] = {0,};

void HandleQuery(const char* QueryDataPath) {
    fstream fs(QueryDataPath);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

void HandleInput(istream& ins) { LOOP_CNT = 0;
    int x, y; // 0, 0 으로 맞추기
    while(!ins.eof() && LOOP_CNT++ < MAX_LOOP) {
        ins >> K; // 1 << K
        if(ins.fail()) {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
        // 
        TS = 1 << K;
        ins >> x >> y;
        FT[--x][--y] = -1;
        // 
        for(int i = TS -1; i >= 0; i--) {
            for(int j = 0; j < TS; j++) {
                cout << FT[i][j] << " ";
            } cout << '\n';
        }

    }
    if(LOOP_CNT >= MAX_LOOP) abort();
}


int main(int argc, char* argv[]) {
    if(argc <= 1) { 
        ios_base::sync_with_stdio(NULL); cin.tie(0);
        HandleInput(cin); 
    }
    else {
        const char * FILE_PATH = argv[1];
        HandleQuery(FILE_PATH);
    }
    return 0;
}