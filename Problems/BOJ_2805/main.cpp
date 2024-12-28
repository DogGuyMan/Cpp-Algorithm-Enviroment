#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define X first
#define Y second

typedef long long LL;

using namespace std;
const int MAX_LOOP = 10;
int LOOP_CNT = 0;

const LL INF = 1e9;

LL n, m;
int woods[1010101];
// 최소 M보단 크게 나무를 가져가기 위해 "최적화된 높이를 리턴 받아보자"
// 적어도 M미터의 나무를 집에 가져가기 위해서 절단기에 설정할 수 있는 높이의 최댓값을 출력한다.
// 나무의 높이의 합은 항상 M보다 크거나 같기 때문에, 상근이는 집에 필요한 나무를 항상 가져갈 수 있다.
// 나무의 개수 N

// 파라메트릭으로 넘어갈 수 있는 근거.
// 높이의 최댓값을 구해야 함 그리고 그걸 이분탐색 할 수 있다.
// Sum >= M 이 true냐 false로 나눌 수 있음.
// lo hi

// mid로 잘라보고 답이 m과 관계를 확인해보자.

bool Check(LL mid) {
    LL sum = 0; // 오버플로우 조심
    for(int i = 0; i < n; i++) {
        if(woods[i] - mid > 0) sum += (woods[i] - mid);
    }
    // sum이 m보다 작다면 mid의 높이가 너무 높다는 것이므로 낮게 땡겨오자.
    // sum이 m보다 크다면 mid의 높이가 너무 낮다는 것이므로 높게 떙겨오자.
    return sum >= m;
}

void HandleInput(istream& ins) { 
    while(!ins.eof() && LOOP_CNT++ < MAX_LOOP) {
        ins >> n >> m;
        if(ins.fail()) { ins.clear(); ins.ignore('\n'); continue; } // 인풋 실패 핸들링을 꼭 해줘야 한다 안그러면 계속 틀리다고 한다.
        LL mx = -INF;
        for(int i = 0; i < n; i++) {
            ins >> woods[i];
            if(mx < woods[i]) {mx = woods[i];}
        }
        LL lowH = 0, hiH = max(mx, INF);
        while(lowH + 1 < hiH) {
            assert(lowH < hiH);
            assert(Check(lowH) == true && Check(hiH) == false);
            LL mid = (lowH + hiH) / 2;
            if(Check(mid)) {lowH = mid;}
            else {hiH = mid;}
        }
        cout << lowH << '\n';

        n = 0, m = 0;
        memset(woods, 0, 1010101);
    }
    if(LOOP_CNT >= MAX_LOOP) abort();
}

void HandleQuery(const char* QueryDataPath) {
    fstream fs(QueryDataPath);
    if(fs.is_open()) HandleInput(fs);
}

int main(int argc, char* argv[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        const char * FILE_PATH = argv[1];
        HandleQuery(FILE_PATH);
    }
}