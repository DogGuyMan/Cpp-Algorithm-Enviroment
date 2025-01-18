#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;

ll A, B;
char deciType[40] = {0,};

void PrintDeci(ll val) {
    if(val > B-1)
        PrintDeci((val / B));
    cout << deciType[(val % B)];
}

void HandleInput(istream& ins) {
    ins >> A >> B;
    for(int i = 0; i < B; i++) { deciType[i] = i + 48; }
    if(B >= 10) {
        for(int i = 'A'; i <= 'Z'; i++) {
            deciType[(10 + i - 'A')] = i;
        }
    }
    PrintDeci(A);
    cout << '\n';
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