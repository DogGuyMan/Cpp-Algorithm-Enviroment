#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
const int MAX = 1e5+10;
#define DEBUG 0

int N, M, A, B;
vector<int> DP(MAX+1);

#if DEBUG
void PRINT_ARR(int sz) {
    for(int i = 1; i <= sz; i++) {
        if(i == N) {
            cout << 'C' << ' '; continue;
        }
        cout << DP[i] << ' ';
    } cout << '\n';
}
#endif

bool IsPromising(int, int);
int TryNextState(int, vector<int>&);

int TryNextState(int curPos, vector<int>& nextStatesRes) {
    #if DEBUG
    if(DEBUG) {
        if(IsPromising(curPos, curPos+1)){if(curPos+1 == M) return -1; nextStatesRes.push_back(curPos+1); cout << curPos+1 << ' ';}
        if(IsPromising(curPos, curPos-1)){if(curPos-1 == M) return -1; nextStatesRes.push_back(curPos-1); cout << curPos-1 << ' ';}
        if(IsPromising(curPos, curPos+A)){if(curPos+A == M) return -1; nextStatesRes.push_back(curPos+A); cout << curPos+A << ' ';}
        if(IsPromising(curPos, curPos-A)){if(curPos-A == M) return -1; nextStatesRes.push_back(curPos-A); cout << curPos-A << ' ';}
        if(IsPromising(curPos, curPos+B)){if(curPos+B == M) return -1; nextStatesRes.push_back(curPos+B); cout << curPos+B << ' ';}
        if(IsPromising(curPos, curPos-B)){if(curPos-B == M) return -1; nextStatesRes.push_back(curPos-B); cout << curPos-B << ' ';}
        if(IsPromising(curPos, curPos*A)){if(curPos*A == M) return -1; nextStatesRes.push_back(curPos*A); cout << curPos*A << ' ';}
        if(IsPromising(curPos, curPos*B)){if(curPos*B == M) return -1; nextStatesRes.push_back(curPos*B); cout << curPos*B << ' ';}
        cout << '\n';
        return 1;
    }
    #endif
    if(IsPromising(curPos, curPos+1)){if(curPos+1 == M) return -1; nextStatesRes.push_back(curPos+1);}
    if(IsPromising(curPos, curPos-1)){if(curPos-1 == M) return -1; nextStatesRes.push_back(curPos-1);}
    if(IsPromising(curPos, curPos+A)){if(curPos+A == M) return -1; nextStatesRes.push_back(curPos+A);}
    if(IsPromising(curPos, curPos-A)){if(curPos-A == M) return -1; nextStatesRes.push_back(curPos-A);}
    if(IsPromising(curPos, curPos+B)){if(curPos+B == M) return -1; nextStatesRes.push_back(curPos+B);}
    if(IsPromising(curPos, curPos-B)){if(curPos-B == M) return -1; nextStatesRes.push_back(curPos-B);}
    if(IsPromising(curPos, curPos*A)){if(curPos*A == M) return -1; nextStatesRes.push_back(curPos*A);}
    if(IsPromising(curPos, curPos*B)){if(curPos*B == M) return -1; nextStatesRes.push_back(curPos*B);}
    return 1;
}

bool IsPromising(int curPos, int nxtPos) {
    if(nxtPos < 0 || nxtPos > M) {return false;}
    if(DP[nxtPos] != -1) {return false;}
    return true;
}

void StateTree(int curPos) {
#if DEBUG
    cout << curPos << " : State" << '\n';
#endif
    queue<int> q;
    q.push(curPos);
#if DEBUG
    cout << "Before NextStates" << '\n';
#endif
    while(!q.empty()) {
        int curPos = q.front(); q.pop();
#if DEBUG
        cout << "Enter " << curPos << " NextStates" << '\n';
#endif
        vector<int> v; v.reserve(8);
        int nxtStateFlag = TryNextState(curPos, v);
#if DEBUG
        cout << "Print NextValues" << '\n';
        for(const auto& nxtPos : v) { cout << nxtPos << ' ';}
        cout << '\n';
#endif
        if(nxtStateFlag == -1)  {DP[M] = DP[curPos] + 1; return;}
        for(const auto& nxtPos : v) {
            if(DP[nxtPos] == -1) {
                DP[nxtPos] = DP[curPos] + 1;
            }
            q.push(nxtPos);
        }
    }
#if DEBUG
    cout << "After Get NextStates" << '\n';
    PRINT_ARR(M);
#endif
    return;
}



void HandleInput(istream& ins) {
    ins >> A >> B >> N >> M ;
    for(int i = 0; i <= M; i++) {
        DP[i] = -1;
    }
    DP[N]=0;

#if DEBUG
    PRINT_ARR(M);
#endif

    StateTree(N);

    cout << DP[M] << '\n';
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open())
        HandleInput(fs);
}

int main(int argc, const char* args[]) {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if(argc >= 1) {
        HandleQuery(args[1]);
    }
    else {
        HandleInput(cin);
    }
}