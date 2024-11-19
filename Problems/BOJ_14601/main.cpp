#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iomanip>
#define DEBUG 0
#define TIMER 0
using namespace std;

const int MAX_LOOP = 10;
int LOOP_CNT = 0;

const int MAX_TILE_SZ = (1 << 8) + 1;
int K; int TS;
int FT[MAX_TILE_SZ][MAX_TILE_SZ] = {0,};

struct Vector2 {
    int x, y;
};

bool IsCenterFillable(const Vector2& pos, int nextLen) {
    for(int i = pos.y; i < pos.y + nextLen; i++) {
        for(int j = pos.x; j < pos.x + nextLen; j++) {
            if(FT[i][j] != 0) return false; 
        }
    }
    return true;
}

Vector2 GetNextPartPos(const int part, const Vector2& pos, const int nextLen) {
    Vector2 nextPos;
    switch (part)
    {
    case 2 : { nextPos = {pos.x, pos.y}; break;}
    case 1 : { nextPos = {pos.x + nextLen, pos.y}; break;}
    case 3 : { nextPos = {pos.x, pos.y + nextLen}; break;}
    case 4 : { nextPos = {pos.x + nextLen, pos.y + nextLen}; break;}
    }
    return nextPos;
}

void Recursion(const Vector2 pos, int len, int& color) {
    int midLen = len / 2;
    #if DEBUG
    cout << "midLen: " << midLen << '\n';
    #endif
    Vector2 part2 = GetNextPartPos(2, pos, midLen);
    #if DEBUG
    cout << "part2: " << part2.x << " " << part2.y << '\n';
    #endif
    Vector2 part1 = GetNextPartPos(1, pos, midLen);
    #if DEBUG
    cout << "part1: " << part1.x << " " << part1.y << '\n';
    #endif
    Vector2 part3 = GetNextPartPos(3, pos, midLen);
    #if DEBUG
    cout << "part3: " << part3.x << " " << part3.y << '\n';
    #endif
    Vector2 part4 = GetNextPartPos(4, pos, midLen);
    #if DEBUG
    cout << "part4: " << part4.x << " " << part4.y << '\n';
    #endif

    if(IsCenterFillable(part2, midLen)) FT[part2.y + midLen -1][part2.x + midLen -1] = color;
    if(IsCenterFillable(part1, midLen)) FT[part1.y + midLen -1][part1.x] = color;
    if(IsCenterFillable(part3, midLen)) FT[part3.y][part3.x + midLen -1] = color;
    if(IsCenterFillable(part4, midLen)) FT[part4.y][part4.x] = color;
    color++;

    #if DEBUG
        for(int i = TS - 1; i >= 0; i--) {
            for(int j = 0; j < TS; j++) {
                cout << FT[i][j] << ' ';
            } cout << '\n';
        }
    #endif
    if(len == 2) return;
    Recursion(part2, midLen, color);
    Recursion(part1, midLen, color);
    Recursion(part3, midLen, color);
    Recursion(part4, midLen, color);
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
        FT[--y][--x] = -1;
        int color = 1;
        #if DEBUG
        for(int i = TS - 1; i >= 0; i--) {
            for(int j = 0; j < TS; j++) {
                cout << FT[i][j] << ' ';
            } cout << '\n';
        }
        #endif
        Recursion({0,0}, TS, color);
        for(int i = TS - 1; i >= 0; i--) {
            for(int j = 0; j < TS; j++) {
                cout << FT[i][j] << ' ';
            } cout << '\n';
        }
    }
    if(LOOP_CNT >= MAX_LOOP) abort();
}


void HandleQuery(const char* QueryDataPath) {
    fstream fs(QueryDataPath);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}


int main(int argc, char* argv[]) {
    #ifdef TIMER
    auto start =  chrono::high_resolution_clock::now();
    #endif
    if(argc <= 1) { 
        ios_base::sync_with_stdio(false); 
        cin.tie(0);
        HandleInput(cin); 
    }
    else {
        const char * FILE_PATH = argv[1];
        HandleQuery(FILE_PATH);
    }
    #ifdef TIMER
    auto end =  chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << setprecision(10) << duration.count() << endl;
    #endif
    return 0;
}