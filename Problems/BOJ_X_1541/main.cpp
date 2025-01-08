#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
typedef long long ll;

ll minAns = 0;

void HandleInput(istream& ins) {
    string form; ins >> form;
    ll start = 0, pos = 0;
    ll tmpAns = 0;
    bool isNeg = false;
    if(form.find_first_of("+-", start) == string::npos) {
        cout << form << '\n'; return;
    }
    while (start < form.size()) {
        ll pos = form.find_first_of("+-", start);
        if(start - 1 > 0) {
            if(form[start-1] == '-') {
                if(!isNeg) minAns += tmpAns;
                else {minAns -= tmpAns;}
                tmpAns = 0;
                isNeg = true;
            }
            tmpAns += stoll(form.substr(start, start - pos));
        }
        else {
            minAns += stoll(form.substr(start, start - pos));
        }
        if (pos == string::npos) break;
        start = pos + 1;
    }
    cout << minAns + (isNeg ? -tmpAns : tmpAns) << '\n';
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
        char * FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}