#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

// M 정렬하기 그리고 N개의 카드 이분탐색 진행
// N : 1 ≤ N ≤ 500,000
// Deck[N] +-1e7
// M : 1 ≤ M ≤ 500,000
// Isin[M] +-1e7

int N, M;
vector<int> OwnDeck, InputDeck;

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        ins >> N;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        OwnDeck.reserve(N+1);
        for(int i = 0 ; i < N; i++) {
            int tmp; ins >> tmp;
            OwnDeck.push_back(tmp); 
        }
        
        sort(OwnDeck.begin(), OwnDeck.end());

        ins >> M;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        InputDeck.reserve(M+1);
        for(int i = 0 ; i < M; i++) {
            int tmp; ins >> tmp;
            InputDeck.push_back(tmp);
        }
        
        for(const auto& ic : InputDeck) {
            if(binary_search(OwnDeck.begin(), OwnDeck.end(), ic)) {
                cout << 1 << ' ';
            }
            else {
                cout << 0 << ' ';
            }
        }cout << '\n';
    }
}

void HandleQuery(const char* queryDataPath) {
    fstream fs(queryDataPath);
    if(fs.is_open()) HandleInput(fs);
}

int main(int argc, char* args[]) {
    if(argc <= 1){
        FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}