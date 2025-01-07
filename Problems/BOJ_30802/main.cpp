#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <numeric>
using namespace std;
typedef long long ll;

ll N;
ll TSZ[6] = {0LL,};
ll T, P;

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        ins >> N;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        for(int i = 0; i < 6; i++) {ins >> TSZ[i];}
        ll sum = accumulate(TSZ, TSZ + 6, 0);
        assert(N == sum);
        ins >> T >> P;
        ll resT = 0, resPD = 0, resPR = 0;
        for(int i = 0 ; i < 6; i++) { 
            if((TSZ[i] % T) != 0)
                resT += (ll)(TSZ[i] / T) + 1; 
            else {
                resT += (ll)(TSZ[i] / T);
            }
        }
        resPD = (ll)((ll)N / (ll)P);
        resPR = N % P;

        cout << resT << '\n' << resPD << " " << resPR;

    }
}
void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) HandleInput(fs);
}

int main(int argc, char * args[]) {
    if(argc <= 1) {
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}