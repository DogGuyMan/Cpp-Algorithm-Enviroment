#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int MAX = 1e5+10;
#define DEBUG 1

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
bool TryNextState(int, vector<int>&);

bool TryNextState(int curPos, vector<int>& nextStatesRes) {
    if(IsPromising(curPos, curPos+1)){nextStatesRes.push_back(curPos+1);}
    if(IsPromising(curPos, curPos-1)){nextStatesRes.push_back(curPos-1);}
    if(IsPromising(curPos, curPos+A)){nextStatesRes.push_back(curPos+A);}
    if(IsPromising(curPos, curPos-A)){nextStatesRes.push_back(curPos-A);}
    if(IsPromising(curPos, curPos+B)){nextStatesRes.push_back(curPos+B);}
    if(IsPromising(curPos, curPos-B)){nextStatesRes.push_back(curPos-B);}
    if(IsPromising(curPos, curPos*A)){nextStatesRes.push_back(curPos*A);}
    if(IsPromising(curPos, curPos*B)){nextStatesRes.push_back(curPos*B);}
    if(nextStatesRes.size() > 1) return true;
    return false;
}

bool IsPromising(int curPos, int nxtPos) {
    if(nxtPos < 0 || nxtPos > M) {return false;}
    if((DP[curPos] +  1) >= DP[nxtPos]) {return false;}
    return true;
}

void StateTree(int curPos) {
#if DEBUG
    cout << curPos << " : State" << '\n';
#endif
    vector<int> nxtStates; // 큐로 바꾸기
    nxtStates.reserve(8);
#if DEBUG
    cout << "Before NextStates" << '\n';
#endif
    if(TryNextState(curPos, nxtStates)) {
#if DEBUG
        for(const auto& i :  nxtStates){ 
            cout << i << ' ';
        } cout << '\n';
        cout << "After Get NextStates" << '\n';
#endif
        for(const auto& i :  nxtStates){
            if(DP[i] > DP[curPos] + 1)   
                DP[i] = DP[curPos] + 1;
            if(i == M) return;
            StateTree(i);
        }
#if DEBUG
    cout << "After Get NextStates" << '\n';
        PRINT_ARR(M);
#endif
    }
    return;
}



void HandleInput(istream& ins) {
    ins >> A >> B >> N >> M ;
    for(int i = 1; i <= M; i++) {
        DP[i] = abs(N-i);
    }

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