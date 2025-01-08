#include <iostream>
#include <fstream>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
typedef long long ll;
const ll INF = 1e9+1;

ll A, B;

bool DFS(ll val, int depth) {
    if(val >= INF)  {return false;}
    if(val == B)    {cout << depth << '\n'; return true;}
    return DFS((val << 1), depth+1) || DFS((val*10 + 1), depth+1);
}

void HandleInput(istream& ins) {
    ins >> A >> B;
    ll opCnt = 1;
    if(!DFS(A, opCnt))
        cout << -1 << '\n';
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
        char * FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}