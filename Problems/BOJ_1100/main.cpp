#include <iostream>
#include <fstream>
#include <algorithm>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
typedef long long ll;

void HandleInput(istream& ins) {
    int N = 8, cnt = 0;
    for(int i = 0 ; i < N; i++) {
        string rowBoard;
        ins >> rowBoard;
        // 하얀거 0
        for(int j = (i % 2); j < 8; j+=2) {
            if(rowBoard[j] == 'F') cnt++;
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
        char * FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}