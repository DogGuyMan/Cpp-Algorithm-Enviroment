#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define DEBUG 0
typedef long long ll;
typedef vector<vector<ll>> matrix;
const ll INF = 123456789;

int Q = 0;
matrix DIST = matrix(505, vector<ll>(505, INF));

string FW(int n, int m, int w)
{
    // Node 1 부터
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (DIST[i][k] != INF && DIST[k][j] != INF)
                {
                    ll newDist = DIST[i][k] + DIST[k][j];
                    if (DIST[i][j] > newDist)
                    {
                        if (i == j && newDist < 0)
                            return "YES";
                        DIST[i][j] = newDist;
                    }
                }
            }
        }
    }
    return "NO";
}

void Clear(int sz)
{
    for (int i = 0; i <= sz; i++)
    {
        for (int j = 0; j <= sz; j++)
        {
            DIST[i][j] = INF;
        }
    }
}

void HandleInput(istream &ins)
{
    ins >> Q;
    while (Q--)
    {
        int N, M, W;
        ins >> N >> M >> W;
        for (int i = 1; i <= N; i++)
        {
            DIST[i][i] = 0;
        }
        for (int i = 0; i < M; i++)
        {
            int S, E, T;
            ins >> S >> E >> T;
            if(DIST[S][E] > T) {
                DIST[S][E] = T;
                DIST[E][S] = T;
            }
        }
        
        for (int i = 0; i < W; i++)
        {
            int S, E, T;
            ins >> S >> E >> T;
            if(DIST[S][E] > -T) {
                DIST[S][E] = -T;
            }
        }
        string res = FW(N, M, W);
        cout << res << '\n';
        Clear(N);

    }
}

void HandleQuery(const char *FILE_PATH)
{
    fstream fs(FILE_PATH);
    if (fs.is_open())
    {
        HandleInput(fs);
    }
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        HandleQuery(argv[1]);
    }
    else
    {
        ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}