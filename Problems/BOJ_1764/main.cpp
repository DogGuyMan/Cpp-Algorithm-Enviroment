#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
typedef long long ll;

int N, M;
int cnt = 0;
map<string, int> m;

void HandleInput(istream& ins) {
    ins >> N; ins >> M;
    string tmp;
    for(int i = 0 ; i < N; i++) { ins >> tmp; m[tmp] = 1; }
    for(int i = 0 ; i < M; i++) { ins >> tmp; m[tmp]++; 
        if(m[tmp] >= 2) cnt++;
    }
    cout << cnt << '\n';
    for(const auto& e : m) {
        if(e.second >= 2) {cout << e.first << '\n';}
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
        char * FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}