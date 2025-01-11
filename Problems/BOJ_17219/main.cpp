#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <unordered_map>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define Y first
#define X second
#define DEBUG 0
using namespace std;

int N, M;
unordered_map<string, string> hm;

void HandleInput(istream& ins) {
    ins >> N >> M;
    for(int i = 0; i < N; i++) {
        string key, value;
        ins >> key >> value;
        hm.insert({key, value});
#if DEBUG 
        cout << " key : " << key << " value : " << hm[key] << '\n';
#endif
    }

    for(int i = 0; i < M; i++) {
        string key; ins >> key;
        if(hm.find(key) != hm.end()){
            cout << hm[key] << '\n';
        }
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