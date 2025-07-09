#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e5;
int N = 0; 
int TRI[MAX] = {0,};
int DP[MAX];
int ANS = -MAX;
int INPUT_MOST_MAX = -MAX;

void PRINT_TRI();
int  leftIdx(int curIdx, int depth);
int  rightIdx(int curIdx, int depth);
bool IsPromising(int curMax, int curVal, int curIdx, int curDepth);
void Solve(int * mx, int curVal, int curIdx, int curDepth);
void HandleInput(istream& ins);
void HandleQuery(const char* FILE_PATH);
int depthStart(int d);
int depthEnd(int d);

void PRINT_TRI(int tree[]) {
    int totalCnt = 0;
    for(int d = 1; d <= N; d++) {
        cout << '\n';
        for(int j = 1; j <= d; j++) {
            cout << tree[totalCnt++] << ' ';
        }
    }
}

int leftIdx(int curIdx, int depth) {
    return curIdx + depth;
}

int rightIdx(int curIdx, int depth) {
    return curIdx + depth + 1;
}

bool IsPromising(int curMax, int curVal, int curIdx, int curDepth) {
    return curMax < (curVal + (N - curDepth) * INPUT_MOST_MAX);
}

int depthStart(int d) {
    return depthEnd(d-1);
}
int depthEnd(int d) {
    return ((d+1) * d) / 2;
}

void Solve(int * mx, int curVal, int curIdx, int curDepth) {
    *mx = max(curVal, *mx); 
    if(curDepth >= N) return;
    if(!IsPromising(*mx, curVal, curIdx, curDepth)) {
        return;
    }
    int lft = leftIdx(curIdx, curDepth);
    int rt = rightIdx(curIdx, curDepth);
    Solve(mx, curVal + TRI[lft], lft, curDepth+1);
    Solve(mx, curVal + TRI[rt], rt, curDepth+1);
}
// 24
// 15

void HandleInput(istream& ins) {
    ins >> N;
    int totalCnt = 0;
    for(int i = 1; i <= N; i++) {
        // depth
        for(int j = 1; j <= i; j++) {
            ins >> TRI[totalCnt];
            INPUT_MOST_MAX = max(INPUT_MOST_MAX, TRI[totalCnt]);
            totalCnt++;
        }
    }
    for(int d = N; d>=1; --d) {
        int ds = depthStart(d);
        int de = depthEnd(d);
        for(int i = ds; i < de; ++i) {
            DP[i] = max(DP[leftIdx(i, d)] + TRI[i], DP[rightIdx(i, d)] + TRI[i]);
        }
        // PRINT_TRI(DP);
    }
    // ANS = max(ANS, TRI[0]);
    // Solve(&ANS, ANS, 0, 1);
    // PRINT_TRI();
    cout << DP[0] << '\n';
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, const char* argv[]) {
    if(argc > 1) {
        HandleQuery(argv[1]);
    }
    else {
        ios::sync_with_stdio(true), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}