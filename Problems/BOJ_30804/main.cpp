#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DEBUG 0
using namespace std;

const int INF = (2e5)+1;

int UsedFCnt[10] {'-',};
int N;
vector<int> TANG;
int MXLen = 0;

int GetUsedTypeCount() {
    int cnt = 0;
    for(int i = 1; i <= 9; i++) {
        if(UsedFCnt[i] > 0) cnt++;
    }
    return cnt;
}

void CheckState(int start, int end) {
    cout << "탕후루 상태" << '\n';
    for(int i = start; i <= end; i++) {cout << TANG[i] << ' ';} cout << '\n';
    cout << "사용 과일 상태" << '\n';
    for(int i = 1; i <= 9; i++) {cout << i << ' ';} cout << '\n';
    for(int i = 1; i <= 9; i++) {cout << UsedFCnt[i] << ' ';} cout << '\n';
}

void HandleInput(istream& ins) {
    ins >> N;
    for(int i = 0; i < N; i++) {
        int tmp; ins >> tmp;
        TANG.push_back(tmp);
    }
    int start = -1, end = -1;
    if(N == 0) {cout << 0 << '\n'; return;}
#if DEBUG
    const int MAX_LOOP = 50; int LOOP_CNT = 0;
        if(MAX_LOOP <= LOOP_CNT++) {abort();}
#endif
    while(start < N && end < N) {
        while((end + 1 )< N && GetUsedTypeCount() <= 2) {
            end++; UsedFCnt[TANG[end]]++;
            if(GetUsedTypeCount() > 2) {
                UsedFCnt[TANG[end]]--;
                end--;
                break;
            }
        }
        MXLen = max(MXLen, end-(start+1));
        if(end + 1 >= N) break;
#if DEBUG
        CheckState(start+1, end);
#endif
        while((start+1) < N && (start+1) <= end && GetUsedTypeCount() <= 2) {
            start++; UsedFCnt[TANG[start]]--;
            if(GetUsedTypeCount() <= 2) {
                break;
            }
        }
#if DEBUG
        CheckState(start+1, end);
#endif
    }
    cout << MXLen+1 << '\n';
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