#include <bits/stdc++.h>

using namespace std;

int C; // 1~50
int N; // 1~1000
const int BUFF_SIZE = 20;
const int ALPHA_CNT = 'z' - 'a' + 1;

const char* FAIL_STR = "INVALID HYPOTHESIS";
vector<string> STRS;
vector<vector<int>> G;
vector<int> BACK_TRACK;
vector<int> RES;
bool IS_VISIT[ALPHA_CNT] = {0,};

bool ExistDegreeEdge(int cur) {
        for(int nxt =0; nxt < ALPHA_CNT; nxt++) {
                if(G[cur][nxt] == 1)
                        return true;
        }
        return false;
}

void DFS(int start) {
        IS_VISIT[start] = true;
        bool flag = false;
        for(int i = 0; i < ALPHA_CNT; i++) {
                if(G[start][i] == 0) continue;
                if(IS_VISIT[i] == true) continue;
                flag = true;
                DFS(i);
        }
        BACK_TRACK.push_back(start);
        if(ExistDegreeEdge(start)) 
                RES.push_back(start);
}

// O(N * L)
void MakeGraph(const vector<string>& strs) {
        for(int i =0; i < strs.size()-1; i++) {
                int j = i + 1;
                int len = min(strs[i].size(), strs[j].size());
                // SAME SUB STRING
                for(int k = 0; k < len; k++) {
                        if(strs[i][k] == strs[j][k]) continue;
                        G[strs[i][k]-'a'][strs[j][k]-'a'] = 1;
                        break;
                }
        }
}

// O(26 + E)
void TopoSort() {        

        for(int i = 0; i < ALPHA_CNT; i++) {
                if(!IS_VISIT[i])
                        DFS(i);
        }

        reverse(BACK_TRACK.begin(), BACK_TRACK.end());
        reverse(RES.begin(), RES.end());

        for(int i = 0; i < ALPHA_CNT; i++) {
                for(int j = i+1; j < ALPHA_CNT; j++) {
                        if(G[BACK_TRACK[j]][BACK_TRACK[i]] == 1) {
                                cout << FAIL_STR << '\n';
                                return;
                        }
                }
        }

        for(auto& e : RES) {
                cout << (char)(e + 'a');
        }

        for(int i = 0; i < ALPHA_CNT; i++) {
                if(find(RES.begin(), RES.end(), i) == RES.end()) {
                        cout << (char)(i + 'a');
                }
        } cout << '\n';

        return;
}

// O(N * L) + O(26 + E) 이므로 더 큰거 O(nL)이 정답
void HandleInput(istream& ins) {
        ins >> C;
        while(C--) {
                ins >> N;

                BACK_TRACK.clear();
                RES.clear();
                G = vector<vector<int>>(ALPHA_CNT, vector<int>(ALPHA_CNT, 0));
                STRS = vector<string>(N);
                fill(IS_VISIT + 0, IS_VISIT + ALPHA_CNT, 0);

                for(int i =0; i < N; ++i) {
                        ins >> STRS[i];
                }
                MakeGraph(STRS);
                TopoSort();
        }
}

void HandleQuery(const char* FILE_PATH) {
        fstream fs(FILE_PATH);
        if(fs.is_open()) {
                HandleInput(fs);
        }
}

int main(int argc, const char * argv[]) {
    if(argc > 1) {
        HandleQuery(argv[1]);
    }
    else {
        ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}
