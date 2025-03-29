#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
typedef long long ll;
string inputStr; 

void HandleInput(istream& ins) {
    ins >> inputStr;
    sort(inputStr.begin(), inputStr.end());
    int ans = 0;
    do {
        bool flag = true;
        for(int i = 1; i < inputStr.size(); i++) {
            if(inputStr[i-1] == inputStr[i]) {flag = false; break;}
        }
        if(flag) ans++;
    }while(next_permutation(inputStr.begin(), inputStr.end()));
    cout << ans << '\n';
}
void HandleQuery(const char* queryDataPath) {
    fstream fs(queryDataPath);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[]) {
    if(argc <= 1) {     
        FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}
