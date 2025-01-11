#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <sstream>
#include <string>
#include <chrono>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define DEBUG 1
#define TIMER 1
typedef long long ll;

int T;
deque<int> dq;
string arrStr, opStr;

void HandleInput(istream& ins) {
    ins >> T; 
#if DEBUG
    cout << T << '\n';
#endif
    while(T--) {
        int N;
        ins >> opStr >> N >> arrStr;
        stringstream ss(arrStr);
        while(!ss.eof()) {
            int tmp; ss >> tmp;
            if(ss.fail()) { ss.clear(); char c; ss >> c; continue; }
            dq.push_back(tmp);
        }
        // ll pos = 0, start = 0;
        // arrStr = arrStr.substr(1, arrStr.length()-2);
        // while((pos = arrStr.find_first_of(',', start)) && pos != string::npos ) {
        //     string num = arrStr.substr(start, pos - start);
        //     if(!num.empty()) { dq.push_back(stoi(num)); }
        //     start = pos + 1;
        // }
        // string num = arrStr.substr(start, string::npos);
        // if(!num.empty()) { dq.push_back(stoi(num)); }
        for(const auto& e : dq) {cout << e << ' ';} cout << '\n';

        
        // bool errFlag = false;
        // bool isFront = true;
        // for(int i = 0; i < opStr.size(); i++) {
        //     if(opStr[i] == 'R') {isFront ^= 1;}
        //     else if(opStr[i] == 'D') {
        //         if(!dq.empty()) {
        //             isFront ? dq.pop_front() : dq.pop_back();
        //         } 
        //         else {errFlag = true; break;}
        //     }
        // }
        // if(errFlag) { cout << "error" << '\n'; }
        // else {
        //     cout << '[';
        //     if(isFront) {
        //         while(!dq.empty()) {
        //             cout << dq.front();
        //             if(dq.size() > 1) {cout << ',';}
        //             dq.pop_front();
        //         }
        //     }
        //     else {
        //         while(!dq.empty()) {
        //             cout << dq.back();
        //             if(dq.size() > 1) {cout << ',';}
        //             dq.pop_back();
        //         }
        //     }
        //     cout << ']' << '\n';
        // }
        dq.clear();
    }
}

void HandleQuery(char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[]) {
    #if TIMER
    auto start =  chrono::high_resolution_clock::now();
    #endif
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
    #if TIMER
    auto end =  chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << setprecision(10) << duration.count() << endl;
    #endif
}