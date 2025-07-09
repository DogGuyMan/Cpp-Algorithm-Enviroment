#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> v;
set<vector<int>> hset;

void Solve(int start, vector<int> & sqState) {

    if(sqState.size() == M) {
        do {
            if(hset.find(sqState) == hset.end()) {
                hset.insert(sqState);
            }
        } while(next_permutation(sqState.begin(),sqState.end()));
        return;
    }

    if(sqState.size() > M)
        return;

    if(start >= N || sqState.size() + (N - start) < M) {
        return;
    }
    
    Solve(start + 1, sqState);
    sqState.push_back(v[start]);
    Solve(start + 1, sqState);
    sqState.pop_back();
}

void HandleInput(istream& ins) {
    ins >> N >> M;
    for(int i = 0; i < N; i++) {
        int val; ins >> val;
        v.push_back(val);
    }
    vector<int> sqState;
    sort(v.begin(), v.end());
    Solve(0, sqState);
    auto hsetBegin = hset.begin();
    auto hsetEnd = hset.end();

    for(const auto& seq : hset) {
        for(int i = 0; i < seq.size(); i++) {
            cout << seq[i];
            if(i < seq.size() - 1) cout << " ";
        }
        cout << '\n';
    }
}
void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open())
        HandleInput(fs);
}
int main(int argc, const char* argv[]) {
    if(argc > 1) {
        HandleQuery(argv[1]);
    }
    else {
        HandleInput(cin);
    }
}