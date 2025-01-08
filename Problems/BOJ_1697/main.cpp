#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define X first
#define Y second
#define DEBUG 0
#define TIMER 0
using namespace std;
typedef long long ll;
const int INF = 1e5+1;

int N, K;
bool IsVisit[101010] = {0,};

ostream& operator<<(ostream& os, pair<int,int> p) {
    cout << p.X << " " << p.Y;
    return os;
}

void BFS(int curPos, int depth) {
    queue<pair<int, int>> q;
    q.push({curPos, depth});

    while(!q.empty()) {
        auto nxt = q.front(); q.pop();
#if DEBUG 
        cout << nxt << '\n';
#endif
        if(IsVisit[nxt.X]) {continue;}
        IsVisit[nxt.X] = true;
        if(nxt.X == K) {cout << nxt.Y << '\n'; return;}

        if((nxt.X <<1) >= 0 && (nxt.X << 1) < INF)      {q.push({(nxt.X << 1),  nxt.Y+1});}
        if(nxt.X - 1 >= 0 && nxt.X - 1 < INF)           {q.push({nxt.X - 1,     nxt.Y+1});}
        if(nxt.X + 1 >= 0 && nxt.X + 1 < INF)           {q.push({nxt.X + 1,     nxt.Y+1});}
#if DEBUG
        cout << "candiPos : " << nxt.X << " K : " << K << '\n';
        cout << " q.size : " << q.size() << '\n';
#endif  
    }
#if DEBUG
    cout << "END" << '\n';
#endif
}

void HandleInput(istream &ins)
{
    ins >> N >> K;
    if( N == K ) {cout << 0 << '\n'; return;}
    BFS(N,0);
}

void HandleQuery(char *FILE_PATH)
{
    fstream fs(FILE_PATH);
    if (fs.is_open())
    {
        HandleInput(fs);
    }
}

int main(int argc, char *args[])
{
#if TIMER
    auto start =  chrono::high_resolution_clock::now();
#endif
    if (argc <= 1)
    {
        FASTIO;
        HandleInput(cin);
    }
    else
    {
        char *FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
#if TIMER
    auto end =  chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << setprecision(10) << duration.count() << endl;
#endif
    return 0;
}