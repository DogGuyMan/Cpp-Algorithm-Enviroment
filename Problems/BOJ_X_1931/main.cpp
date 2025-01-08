#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <vector>

#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define X first
#define Y second
#define DEBUG 0
#define TIMER 0
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int N;

ostream& operator<<(ostream& os, pair<int,int> p) {
    os << p.X << " " << p.Y;
    return os;
}

bool COMP(const pii& a, const pii& b) {
    if(a.Y == b.Y) return a.X < b.X;
    return a.Y < b.Y;
}

void HandleInput(istream &ins)
{
    ins >> N;
    vector<pii> v; v.reserve(N + 1);
    int start = 0, end = 0;
    for(int i = 0; i < N; i++){
        ins >> start >> end;
        v.push_back({start, end});
    }
    sort(v.begin(), v.end(), COMP);

#if DEBUG
    for(int i = 0; i < N; i++) { cout << v[i] << '\n'; }
#endif

    pii last = v[0];
    int cnt = 1;
    for(int i = 1; i < v.size(); i++) {
        if(last.Y <= v[i].X) {
            last = v[i];
            cnt++;
        }
    }
    cout << cnt << '\n';
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