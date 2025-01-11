#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define KEY first
#define VALUE second
using namespace std;

int T, N;
int endCnt = 1;

void HandleInput(istream& ins) {
    ins >> T;
    while(T--) {
        map<string, vector<string>> outfits;
        ins >> N;
        if(N == 0) {cout << 0 << '\n'; continue;}
        while(N--) {
            string eq, eqType;
            ins >> eq >> eqType;
            if(outfits.find(eqType) == outfits.end()) {
                outfits.emplace(eqType, vector<string>(0));
            }
            outfits[eqType].push_back(eq);
        }
        for(const auto& e : outfits) {
            endCnt *= (e.VALUE.size() + 1);
        }
        cout << endCnt -1 << '\n';
        endCnt = 1;
    }
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