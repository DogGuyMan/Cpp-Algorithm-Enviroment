#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define X first
#define Y second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

// 외적 잘하는 법이 뭐지?
// 외적이랑 행렬식이라 뭔 관계더라..
int Det(pii a, pii b) {
    return a.X * b.Y - a.Y * b.X;
}

void HandleInput(istream& ins) {
    pii p[3];
    for(int i = 0; i < 3 ; i++) {
        ins >> p[i].X >> p[i].Y;
    }
    pii p1p2 = {p[1].X - p[0].X, p[1].Y - p[0].Y};
    pii p1p3 = {p[2].X - p[1].X, p[2].Y - p[1].Y};
    int det = Det(p1p2, p1p3);
    if(det > 0) {
        cout << 1 << '\n'; // 시계방향
    }
    else if(det < 0) {
        cout << -1 << '\n'; // 반시계방향
    }
    else {
        cout << 0 << '\n'; // 일직선
    }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

int main(int argc, const char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        HandleQuery(args[1]);
    }
}