#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int T, C;
void HandleInput(istream& ins) {
    ins >> T;
    while(T--) {
        ins >> C;
        int divs[4] = {25,10,5,1};
        int coinDivs[4] = {0,};
        for(int i = 0; i < 4; i++) {
            coinDivs[i] = C / divs[i]; C%=divs[i];
            cout << coinDivs[i] << ' ';
        }
        cout << '\n';
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