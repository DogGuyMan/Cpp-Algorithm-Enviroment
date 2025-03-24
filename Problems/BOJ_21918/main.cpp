#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;
#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

int N, M;
bitset<4040> b(0);

void FirOp(int pos, bool state) { b[pos] = state; }
void SecOp(int l, int r) {
    for(int i = l; i <= r; i++) { b.flip(i); }
}
void ThrOp(int l, int r) {
    for(int i = l; i <= r; i++) { b.reset(i); }
}
void FourOp(int l, int r) {
    for(int i = l; i <= r; i++) {b.set(i);}
}

void PerformOps(istream& ins) {
    int a, b, c;
    for(int opCnt = 0;  opCnt < M; opCnt++) {
        ins >> a >> b >> c;
        switch (a)
        {
            case 1 : {FirOp(b, c);break;}
            case 2 : {SecOp(b, c);break;}
            case 3 : {ThrOp(b, c);break;}
            case 4 : {FourOp(b, c);break;}
            default: {break;}
        }
    }

}
void HandleInput(istream& ins){
    ins >> N >> M;
    for(int i = 1; i <= N; i++) {
        bool flg; ins >> flg;
        b[i] = flg;
    }
    PerformOps(ins);
    for(int i = 1; i <= N; i++) { 
        bool tmp = b[i];
        cout << b[i] << ' '; 
    }
}

void HandleQuery(const char* FILE_PATH){
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

int main(int argc, const char* args[]) {
    FASTIO;
    if(argc > 1) {
        HandleQuery(args[1]);
    }
    else {
        HandleInput(cin);
    }
}