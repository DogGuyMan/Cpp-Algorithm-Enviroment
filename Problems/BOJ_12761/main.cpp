
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#define DEBUG 0
#define y first
#define x second
typedef pair<int,int> pii;
const int MAX = 1e5;

int N, M, A, B;
vector<bool> IsVisit(MAX+1);

void BFS(int start) {
    queue<pii> q;
    IsVisit[start] = true;
    q.push({start, 0});
    while(!q.empty()) {
        pii curPos = q.front(); q.pop();
        vector<int> v {curPos.y+1, curPos.y-1, curPos.y+A, curPos.y-A, curPos.y+B, curPos.y-B, curPos.y*A, curPos.y*B};
        for(const auto nxtPos : v) {
            if((0 <= nxtPos && nxtPos <= MAX) && !IsVisit[nxtPos]) {
                IsVisit[nxtPos] = true;
                q.push({nxtPos, curPos.x + 1});
                if(nxtPos == M) { cout << curPos.x + 1 << '\n'; return; }
            }
        }
    }
}

int main() {
    cin >> A >> B >> N >> M ;
    if(N == M) { cout << 0 << '\n'; return 0 ; }
    BFS(N);
    return 0;
}