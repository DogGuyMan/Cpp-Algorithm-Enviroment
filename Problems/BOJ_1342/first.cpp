#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
typedef long long ll;

const char startIdx= 'a', endIdx= 'z';
int alphaCnt[255] = {0,};
int resCount = 0;
string inputStr; 

void DFSBF(vector<char>& combi) {
    if(combi.size() == inputStr.size()) {
        resCount++;
        return;
    }

    bool isEveryFlagZero = true;
    for(int i = startIdx; i <= endIdx; i++) {
        if(combi.back() == i) continue;
        if(alphaCnt[i] !=0) {
            isEveryFlagZero = false;
            break;
        }
    }
    if(isEveryFlagZero) return;

    for(char i = startIdx; i <= endIdx; i++) {
        if(alphaCnt[i] <= 0 || combi.back() == i) continue;
        char useChar = i;
        combi.push_back(useChar);
        alphaCnt[i]--;
        DFSBF(combi);
        alphaCnt[i]++;
        combi.pop_back();
    }
}

void HandleInput(istream& ins) {
    ins >> inputStr;
    for(int i = 0; i < inputStr.size(); i++) {
        alphaCnt[inputStr[i]]++;
    }
    
    vector<char> combi;
    combi.reserve(inputStr.size()+1);
    DFSBF(combi);
    cout << resCount << '\n';
}
void HandleQuery(const char* queryDataPath) {
    fstream fs(queryDataPath);
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
