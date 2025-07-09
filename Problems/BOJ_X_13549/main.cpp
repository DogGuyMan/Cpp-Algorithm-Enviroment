#include <bits/stdc++.h>

using namespace std;

const int MAX = 12346789;
int N = 0, K = 0;

int MIN = 123456789;
struct STATE {
    int pos; 
    int d;

    bool operator<(const STATE& a) const {
        return d > a.d;
    }
};

priority_queue<STATE, vector<STATE>> pq;
vector<int> DIST(101010, MAX);

bool IsBound(int curPos) {
    return 0 <= curPos && curPos <= 100000;
}

void DIJK() {
    pq.push({N, 0});
    while(!pq.empty()) {
        // K - abs(curPos + 1) // K - abs(curPos - 1)
        STATE curSt = pq.top(); pq.pop();
        if(curSt.pos == K) {MIN = min(MIN, curSt.d); return;} 
        if(curSt.d > DIST[curSt.pos]) continue;
        
        vector<STATE> nxtSts = {
            {curSt.pos * 2, curSt.d},
            {curSt.pos + 1, curSt.d + 1},
            {curSt.pos - 1, curSt.d + 1}
        };
        
        for(auto& nxtSt : nxtSts) {
            if(IsBound(nxtSt.pos)) {
                if(DIST[nxtSt.pos] > nxtSt.d) { 
                    DIST[nxtSt.pos] = nxtSt.d; 
                    pq.push(nxtSt);
                }
            }
        };
    }
}

void HandleInput(istream& ins) {
    ins >> N >> K;
    if(K <= N) {cout << abs(N - K) << '\n'; return;}
    MIN = K - N;
    DIST[N] = 0;
    DIST[K] = MIN;
    DIJK();
    cout << MIN << '\n';
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open())
        HandleInput(fs);
}

int main(int argc, const char* argv[]) {
    if(argc > 1) 
        HandleQuery(argv[1]);
    else {
        HandleInput(cin);
    }
    return 0;
}