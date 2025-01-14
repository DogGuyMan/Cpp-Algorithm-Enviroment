#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
#define DEBUG 1
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int INF = 1e6;

int N, M;
string IOStr;


void HandleInput(istream& ins) {
    ins >> N >> M >> IOStr;
    int cnt = 0;
    for(int i = 0; i < M ;i++) {
        if(IOStr[i] != 'O') {
            int adder = 0;
            while(IOStr[i+1] == 'O' && IOStr[i+2] == 'I') {
                adder++;
                if(adder == N) {cnt++; adder--;}
                i+=2;
            }
        }
    }
    cout << cnt << '\n';
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