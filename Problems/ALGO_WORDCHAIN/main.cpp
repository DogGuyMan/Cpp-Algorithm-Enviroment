#include <bits/stdc++.h>
using namespace std;

int C; // 1 ~ 50
int N; // 1~100 edge 수
const int ALPHA_CNT = 'z'-'a'+1;
const char* FAIL_STR = "IMPOSSIBLE";

vector<int> IN_DEG, OUT_DEG;
vector<string> G[ALPHA_CNT][ALPHA_CNT];

vector<int> BACK_TRACK;
int EDGE_CNT[ALPHA_CNT][ALPHA_CNT];

bool CheckEuler() {
        int sV = 0, eV = 0; // 트레일 일때 시작점, 끝점
        for(int i = 0; i < ALPHA_CNT; i++) {
                int degGap = OUT_DEG[i] - IN_DEG[i];
                if(degGap > 1 || degGap < -1) return false;
                if(degGap == 1) sV++;
                if(degGap == -1) eV++;
        }
        bool isTrail = (sV == 1 && eV == 1);
        bool isCircuit = (sV == 0 && eV == 0);
        return (isTrail || isCircuit);
}

void DFS(int cur) {
        for(int nxt = 0; nxt< ALPHA_CNT; nxt++) {
                while(EDGE_CNT[cur][nxt] > 0) {
                        EDGE_CNT[cur][nxt]--;
                        DFS(nxt);
                }
        }
        BACK_TRACK.push_back(cur);
}

void Solve(istream& ins) {
        for(int i = 0; i < ALPHA_CNT; i++){
                for(int j = 0; j < ALPHA_CNT; j++){
                        G[i][j].clear();
                        EDGE_CNT[i][j] = 0;
                }
        }
        IN_DEG = vector<int>(ALPHA_CNT, 0);
        OUT_DEG = vector<int>(ALPHA_CNT, 0);
        BACK_TRACK.clear();
        
        for(int i = 0; i < N; ++i) {
                string tmp; 
                ins >> tmp;
                int from = tmp[0] - 'a';
                int to = tmp.back() - 'a';
                G[from][to].push_back(tmp);
                EDGE_CNT[from][to]++;
                OUT_DEG[from]++;
                IN_DEG[to]++;
        }
        
        if(!CheckEuler()) {
                cout << FAIL_STR << '\n';
                return;
        }
        
        int trailPos = -1;
        for(int i = 0; i < ALPHA_CNT; i++) {
                if(IN_DEG[i] + 1 == OUT_DEG[i]){
                        trailPos = i;
                        break;
                }
        }

        if(trailPos == -1)
        {
                for(int i = 0; i < ALPHA_CNT; i++) {
                        if(OUT_DEG[i] > 0) {
                                DFS(i);
                                break;
                        }
                }
        }
        else {
                DFS(trailPos);
        }
        
        if(BACK_TRACK.size() != N + 1) {
                cout << FAIL_STR << '\n';
                return;
        }
        
        reverse(BACK_TRACK.begin(), BACK_TRACK.end());
        for(int i = 0; i < BACK_TRACK.size()-1; i++) {
                int from = BACK_TRACK[i];
                int to = BACK_TRACK[i+1]; 
                string poped = G[from][to].back();
                cout << poped << ' ';
                G[from][to].pop_back();
        } cout << '\n';
}

void HandleInput(istream& ins) {
        ins >> C;
        while(C--) {
                ins >> N;
                Solve(ins);
        }
}

void HandleQuery(const char* FILE_PATH) {
        fstream fs(FILE_PATH);
        if(fs.is_open()) {
                HandleInput(fs);
        }
}

int main(int argc, const char* argv[]) {
        if(argc <= 1) {
                ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
                HandleInput(cin);
        }
        else{
                HandleQuery(argv[1]);
        }
}