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
const int INF = 1e9+1;

int N;
void HandleInput(istream &ins)
{
    ins >> N;
    vector<int> v(N);
    for(int i = 0; i < N; i++) {
        ins >> v[i];
    }
    vector<int> sotredV(v);
    sort(sotredV.begin(), sotredV.end());
    auto it = unique(sotredV.begin(), sotredV.end());
    sotredV.resize( distance(sotredV.begin(),it) );
    // cout << "unique" << '\n';
    // for(const auto& e : sotredV) cout << e << ' ';
    // cout << '\n';
    for(const auto& key : v) {
        auto start = sotredV.begin();
        auto lb = lower_bound(sotredV.begin(), sotredV.end(), key);
        cout << lb - start << ' ';
    }
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