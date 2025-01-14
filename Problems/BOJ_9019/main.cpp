#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define Y first
#define X second
#define DEBUG 0
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int MAX = 9999;
const int MOD = 10000;

struct Regi {
    int cacheVal;
    int opCnt = 0;
    char appliedOps[32];
};

void DOp(int& val) {
    val = (2*val) % MOD;
}
void SOp(int& val) {
    val = (val) <= 0 ? 9999 : (val - 1);
}
void LOp(int& val) {
    val = ((val % 1000) * 10) + (val / 1000);
}
void ROp(int& val) {
    val = ((val % 10) * 1000) + (val / 10);
}
void Op(Regi& regi, const char& op) {
    switch (op)
    {
    case 'D' : {DOp(regi.cacheVal); regi.appliedOps[regi.opCnt++] = 'D'; break;}
    case 'S' : {SOp(regi.cacheVal); regi.appliedOps[regi.opCnt++] = 'S'; break;}
    case 'L' : {LOp(regi.cacheVal); regi.appliedOps[regi.opCnt++] = 'L'; break;}
    case 'R' : {ROp(regi.cacheVal); regi.appliedOps[regi.opCnt++] = 'R'; break;}
    default:
        break;
    }
}
void PrintAppliedOps(const Regi& regi) {
    for(int i = 0; i < regi.opCnt; i++) {
        cout << regi.appliedOps[i];
    }cout << '\n';
}

int from, to;
bool IsVisit[10101];
const vector<char> opList = {'D' , 'S' , 'L' , 'R'};

void BFS(Regi& regi) {
    queue<Regi> q; q.push(regi);
    int depth = 0;
    IsVisit[regi.cacheVal] = true;
    
    while(!q.empty()) {
        Regi curVal = q.front(); q.pop();
        if(curVal.cacheVal == to) {PrintAppliedOps(curVal); return;}
        for(const auto& op : opList) {
            Regi nxtRegi = curVal; Op(nxtRegi, op);
            if(!IsVisit[nxtRegi.cacheVal]) {
                IsVisit[nxtRegi.cacheVal] = true;
                q.push(nxtRegi);
            }
        }
    }
}

void HandleInput(istream& ins) {
    int T; ins >> T;
    while(T--) {
#if DEBUG
        cout << T << '\n';
#endif
        ins >> from >> to;
        Regi regi; regi.cacheVal = from;
#if DEBUG
        char op = 'R';
        regi.Op(op);
        cout << " from : " << from << " regi value : " << regi.get_value() << " to : " << to << '\n';
#endif
        if(from == to) {
#if DEBUG
            cout << "SAME" << '\n';
#endif
            cout << '\n'; continue;
        }
        BFS(regi);
        memset(IsVisit, 0, 10101);
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