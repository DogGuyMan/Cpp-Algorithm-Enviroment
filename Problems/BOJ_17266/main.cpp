#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unistd.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;

ll N = 0, M = 0;
const ll MAX = 1e6+10;
vector<ll> lightPosList;

// 3 Len
// 0 position
// tail = 0, head = 0
// tail = 0, head = 0
// head 

bool Check(ll height) {
    ll tail = 0, head = 0; // 음수여도 되나? 예
    for(const auto& lightPos : lightPosList) {
        ll nxtTail = lightPos - height;
        if(head < nxtTail) return false;
        tail = lightPos - height;
        head = lightPos + height;
    }
    // // cout << "tail : " << tail << " head :" << head <<  '\n';
    if(head >= N) return true;
    return false;
}

void HandleInput(istream& ins) {
    ins >> N >> M;
    ll pos = 0;
    // cout << M << '\n';
    for(int i = 0; i < M; i++) {
        ins >> pos;
        // // cout << "i : " << i << " pos : "<< pos << ' ';
        lightPosList.push_back(pos);
    }

    ll lo = 0, hi = 1e18;
    ll mid = ((hi + lo) >> 1LL);
    // FFF/TTT hi가 답임.
    while(lo + 1 < hi) {
        assert(lo < hi);
        assert(Check(lo) == false && Check(hi) == true);
        mid = ((hi + lo) >> 1LL); 
        // cout << "lo : " << lo << " hi :" << hi << " mid : " << mid << '\n';
        if(Check(mid)) {hi = mid;}// true면 좀 줄여도 된다.
        else {lo = mid;} // mid + 1은 왜했어? 몰.. 루
    }
    cout << hi << '\n';
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


/***************************

1줄 : N 굴다리의 길이 1 1e5
2줄 : M 가로등의 개수
3줄 : X X X X X...
    설치할 수 있는 가로등의 위치
    X는 오름차순 중복 안됨 정수.

N 만큼 길이의 다리를 모두 비추기 위한 가로등의 최소 높이?
    파라메트릭 서치?
    2와 4사이 길이는..
    2가 2만큼 높고, 4는 1

X가 0에 닿으려면 곧 X가 높이

32번 반복하면 된다.
높이 = 어떤게 비춰지고 어떤게 안비춰지는지 확인하자.

// 최악 O(N) 1e5 번 파라메트릭 32
bool IsShineAll(int height) {
    int tail, int head; // 음수여도 되나? 예
    for(auto& lightPos : lightPosList) {
        int nxtTail = lightPos - height;
        if(head < nxtTail) return false;
        tail = lightPos - height;
        head = lightPos + head;
    }
    return true;
}

***************************/