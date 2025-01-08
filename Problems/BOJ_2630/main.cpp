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
typedef pair<int,int> pii;
typedef vector<vector<int>> matrix;
const int INF = 1e5+1;

int N;
bool IsVisit[101010] = {0,};
matrix PaperM;
int Blue = 0, Wihte = 0;
enum COLOR {
    W = 0,
    B = 1
};

ostream& operator<<(ostream& os, pair<int,int> p) {
    cout << p.X << " " << p.Y;
    return os;
}

void PRINT_MT(const matrix& mt, pii initPos, int Len) {
    cout << " initPos : " << initPos.X << " initPos : " <<  initPos.Y << '\n';
    for(int i = initPos.X; i < initPos.X + Len; i++)
        {for(int j = initPos.Y; j < initPos.Y + Len; j++) {
            cout << mt[i][j] << ' ';
        } cout << '\n';}
}

bool IsFilled(const matrix& mt, pii initPos, int Len) {
    COLOR color = (COLOR)mt[initPos.X][initPos.Y];
    for(int i = initPos.X; i < initPos.X + Len; i++)
        for(int j = initPos.Y; j < initPos.Y + Len; j++) {
            if(mt[i][j] != color) {return false;}
        }
    if(color == COLOR::W) {Wihte++;}
    else {Blue++;}
    return true;
}

void DivCq(pii initPos, int curLen, int depth) {
    // PRINT_MT(PaperM, initPos, curLen);
    if(IsFilled(PaperM, initPos, curLen)) { return; }
    int nxtLen = curLen / 2;
    DivCq({initPos.X, initPos.Y}, nxtLen,           depth+1); // 2
    DivCq({initPos.X + nxtLen, initPos.Y}, nxtLen,  depth+1); // 1
    DivCq({initPos.X, initPos.Y + nxtLen}, nxtLen,  depth+1); // 3
    DivCq({initPos.X + nxtLen, initPos.Y + nxtLen}, nxtLen, depth+1); // 4
}

void HandleInput(istream &ins)
{
    ins >> N;
    PaperM = matrix(N, vector<int>(N));
    for(int i = 0; i< N; i++)
        for(int j = 0; j< N; j++)
            ins >> PaperM[i][j];
    DivCq({0,0}, N, 0);
    cout << Wihte << '\n';
    cout << Blue << '\n';
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