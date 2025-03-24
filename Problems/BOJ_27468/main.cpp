#include <iostream>
#include <deque>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
#define DEBUG 1
using namespace std;
const int MAX = 2e6;
int N;
vector<int> seq;

bool CheckCondition(int ai, int ai1, int ai2) {
    bool flag1 = (abs(ai1 - ai) == (2 * abs(ai1 - ai2)));
    bool flag2 = ((2 * abs(ai1 - ai)) == abs(ai1 - ai2));
    return (flag1 || flag2);
}

bool IS_ANSWER_ITERATE_RIGHT(vector<int>& v) {
    for(auto it = v.begin(); it != v.end(); it++) {
        if(*it == v.front() || *it == v.back()) continue;
        vector<int>::iterator lft,  lft1,  lft2;
        lft = prev(it, 1);
        lft1 = it;
        lft2 = next(it, 1);
        if(!CheckCondition(*lft, *lft1, *lft2)) {
            return false;
        }
    }
    return true;
}

void HandleInput(istream& ins) {
    ins >> N;
    seq.push_back(-1);
    for(int i = 1; i <= N; i++) { seq.push_back(i); }

    bool isRevStart = false;
    if((N % 4 == 0) || (N % 4 == 3)) 
        isRevStart = true;
    
    for(int i = 1; i <= N; i+=2) {
        if(((i / 2) % 2 != 0) ^ isRevStart) {
            swap(seq[i], seq[i+1]);
        }
    }
    seq.erase(seq.begin());

    if(!IS_ANSWER_ITERATE_RIGHT(seq)) {
        cout << "NO" << '\n';
    }
    else {
        cout << "YES" << '\n';
        for(const auto& e : seq) {
            if(e == -1) continue;
            cout << e << ' ';
        } cout << '\n';
    }
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}
int main(int argc, const char* args[]) {
    if(argc > 1) {
        HandleQuery(args[1]);
    }
    else {
        HandleInput(cin);
    }
}