#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define KEY first
#define VALUE second
using namespace std;

int N;
vector<vector<int>> G;
int IsVisit[101010] = {0,};

void BFS() {
    queue<int> q;
    q.push(1); IsVisit[1] = 1;
    while(!q.empty()) {
        int frt = q.front(); q.pop();
        for(auto& e : G[frt]) {
            if(IsVisit[e] == 0) {
                q.push(e);
                IsVisit[e] = frt;
            }
        }
    }
}

void HandleInput(istream& ins) {
    ins >> N;
    int a, b;
    G = vector<vector<int>>(N+101, vector<int>());
    for(int i = 0; i < N; i++) {
        ins >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    BFS();
    for(int i = 2; i <= N; i++) {
        cout << IsVisit[i] << '\n';
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