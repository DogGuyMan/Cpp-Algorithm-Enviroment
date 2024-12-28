#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define X first
#define Y second
typedef long long LL;
using namespace std;

int N, M;
vector<LL> T;
// 상근 + 친구 = M 명 1e9
// 입국 심사대 N개 1    1e5
    // 각 심사관의 시간 T_k
// 한 심사대에서 한번에 한사람 걸림
    // 이동하기 : 심사시간이 가장 적은곳이 나서 심사 받기
    // 이동하지 않기 : 대기시간 + 심사시간이 제일 짧은곳을 위해 대기

// 시간 최솟값 구하기 문제
// 결정문제로 바꿀 수 있을까? 잘 모르겠어.
// hi lo를 설정항 수 있나?
// check(lo)  check(hi)

bool Check(LL mid) {
    LL sum = 0;
    for(int i = 0; i < N ; i++) {
        sum += mid / T[i]; // T[i]가 0이 되는일은 없으니 안심
        if(sum >= M) return true; // 이거 안하면 LL도 충분하지 않아 오버플로우 터질 수 있었다.
    }
    // sum이 M을 충족하고도 남는다면 mid를 줄여봐야 한다.
    // sum이 M을 충족하지 못한다면 mid를 키워봐야한다..
    // cout << " sum : " << sum << " M : " << M << '\n';
    return false;
}

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        ins >> N >> M;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        T.reserve(N+1); T.resize(N);

        // cout << '\n';
        // cout << " N : " << N << " M : " << M << '\n';
        // cout << " T.capacity() : " << T.capacity() << " T.size() : " << T.size() << '\n';
        // cout << '\n';
        for(int i = 0; i < N; i++) {
            ins >> T[i];
        } 

        // cout << '\n';
        LL lo = 0, hi = 1e18;
        while(lo + 1 < hi) {
            // assert(lo < hi);
            // assert(Check(lo) == true && Check(hi) == false);
            LL mid = ((lo + hi) >> 1LL);

            // cout << setw(30) << "-------------" << '\n';
            // cout << setw(30) << " lo : " << lo << '\n';
            // cout << setw(30) << " hi : " << hi << '\n';
            // cout << setw(30) << " mid : " << mid << '\n';

            if(!Check(mid)) {lo = mid;}
            else {hi = mid;}
        }
        cout << hi << '\n';
    }
}

void HandleQuery(const char* queryDataPath) {
    fstream fs(queryDataPath);
    if(fs.is_open()) {HandleInput(fs);}
}


int main(int argc, char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}