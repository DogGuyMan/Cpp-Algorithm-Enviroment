#include <iostream>
#include <fstream>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0) 
const int MAX = 1e5;

struct DSetEl {
    int par = 0;
    int rank = 0;
    int chung = 0;
    int go = 0;
};

ostream& operator<<(ostream& os, const DSetEl& set) {
    os  << " par : " << set.par
        << " rank : " << set.rank
        << " chung : " << set.chung
        << " go : " << set.go;
    return os;
}

int N , M , Q;
DSetEl DSet[101010] {0, };

void MakeSet(int cnt) {
    for(int i = 1; i <= cnt; i++) {
        DSet[i].par = i;
        DSet[i].rank = 1;
    }
}

int FindSetPar(int x) {
    if(x == DSet[x].par) return x;
    return DSet[x].par = FindSetPar(DSet[x].par);
}

void Unite(int x, int y) {
    x = FindSetPar(x), y = FindSetPar(y);
    if(x == y) return;
    if(DSet[x].rank < DSet[y].rank) { swap(x, y); }

    DSet[y].par = x;
    int updateChung = DSet[y].chung + DSet[x].chung;
    int updateGo = DSet[x].go + DSet[y].go;
    DSet[x].chung = updateChung;
    DSet[x].go = updateGo;
    if(DSet[x].rank == DSet[y].rank)
        DSet[x].rank++;
}

void HandleInput(istream& ins) {
    ins >> N >> M >> Q;
    MakeSet(N);
    for(int i = 1; i <= N; i++) {
        int water; ins >> water;
        water ? DSet[i].chung++ : DSet[i].go++;
        
        // cout <<DSet[i] << '\n';
    }

    for(int i = 1; i <= M; i++) {
        int from = 0, to = 0; 
        ins >> from >> to;
        Unite(from, to);
    }

    for(int i = 1; i <= Q; i++) {
        int t; ins >> t;
        int par = FindSetPar(t); 

        if(DSet[par].go < DSet[par].chung)
            {cout << 1 << '\n'; continue;}
        cout << 0 << '\n';
    }
    // cout << '\n';
    // for(int i = 1; i <= N; i++) {
    //     cout << DSet[i] << '\n';
    // }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}