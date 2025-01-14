#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstring>
#define DEBUG 0
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int MAX = 1e9+1;

int N, M;
int minLen = MAX;
const int MAX_LOOP = 1e2; int LOOP_CNT = 0;
int Vals[111111] = {0,};

void HandleInput(istream& ins) {
    ins >> N >> M;
    for(int i =0; i < N; i++) {ins >> Vals[i];}
    int start = 0, end = 0;
    int sum = 0;

    while(start <= end && end < N) {
        if(sum < M) { sum += Vals[end++]; }
        if(sum >= M) {
            minLen = min(minLen, (end - start));
#if DEBUG
            cout << " UPDATE : " << minLen << '\n';
#endif
            sum -= Vals[start++];
            if(sum < 0) {cout << 0 << '\n'; return;}
        }
#if DEBUG
        cout << '['<<start << ", " << end << ')' << sum << '\n';
        for(int i = start; i < end; i++) {cout << setw(3) << Vals[i] << ' ';} 
        cout << '\n';
#endif
    }
    while(start < N) {
        if(sum >= M) {
            minLen = min(minLen, (end - start));
        }
        sum -= Vals[start++];
        if(sum < 0) {cout << 0 << '\n'; return;}
#if DEBUG
        cout << '['<<start << ", " << end << ')' << sum << '\n';
        for(int i = start; i < end; i++) {cout << setw(3) << Vals[i] << ' ';} 
        cout << '\n';
#endif
    }
    minLen == MAX 
        ?  cout << 0 << '\n'
        :  cout << minLen << '\n';
}

void HandleQuery(char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}