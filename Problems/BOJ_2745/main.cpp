#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;

string A; int B;
int charToDeci[333] = {0,};

void HandleInput(istream& ins) {
    ins >> A >> B;
    for(int i = '0'; i <= '9'; i++) {
        charToDeci[i] = i - '0';
    }
    if(B > 10) {
        for(int i = 'A'; i <= 'Z'; i++) {
            charToDeci[i] = (10 + i - 'A');
        }
    }
    ll sum = 0; int muls = 1;
    for(int i = A.size()-1; i >= 0; i--) {
        sum += muls * charToDeci[A[i]];
        muls *= B;
    }
    cout << sum << '\n';
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