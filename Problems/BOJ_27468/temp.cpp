#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <iomanip>
using namespace std;
#define DEBUG 1
const int MAX = 1e6*2;
int N;

enum IterPos {
    None = 1 << 0,
    Left = 1 << 1,
    Right = 1 << 2,
};

list<int> seq;

bool CheckCondition(int ai, int ai1, int ai2) {
    bool flag1 = (abs(ai1 - ai) == (2 * abs(ai1 - ai2)));
    bool flag2 = ((2 * abs(ai1 - ai)) == abs(ai1 - ai2));
#if DEBUG
    cout << "MUL2 : " << flag1 << " DIV2 : " << flag2 << '\n';
#endif
    return (flag1 || flag2);
}

IterPos GetValidPos(int nxt) {
    list<int>::iterator lft,  lft1,  lft2;
    // Check Left
    lft1 = seq.begin(); lft2 = next(lft1, 1);
#if DEBUG
    cout << "ai : "<< nxt << " " << "ai1 : "<< *lft1 << " " << "ai2 : "<< *lft2 << '\n';
#endif

    if(CheckCondition(nxt, *lft1, *lft2)) {
#if DEBUG
        cout << "push Left" << '\n';
#endif
        return IterPos::Left;
    }
    // Check Right
    lft1 = seq.end(); --lft1; lft = prev(lft1, 1);
#if DEBUG
    cout << "ai : "<< *lft << " " << "ai1 : "<< *lft1 << " " << "ai2 : "<< nxt << '\n';
#endif

    if(CheckCondition(*lft, *lft1, nxt)) {
#if DEBUG
        cout << "push right" << '\n';
#endif
        return IterPos::Right;
    }
#if DEBUG
        cout << "No Push" << '\n';
#endif
    return IterPos::None;
}

#if DEBUG

void DEBUG_COPY_AND_ITER() {
    for(int i = 0; i < N; i++) {
        seq.push_back(i*2);
        cout << seq.back() << ' ';
    }cout << '\n';
    list<int>::iterator lft,  lft1,  lft2;
    lft1 = seq.begin(); 
    lft2 = next(lft1, 1);
    cout << "lft1 : " << *lft1 << " lft2 : " << *lft2 << '\n';

    lft1 = seq.end(); 
    --lft1;
    lft = prev(lft1, 1);
    cout << "lft : " << *lft << " lft1 : " << *lft1 << '\n';
}

void IS_ANSWER_ITERATE_RIGHT() {
    bool flag = true;
    cout << seq.front() << ' ';
    for(auto it = seq.begin(); it != seq.end(); it++) {
        if(*it == seq.front() || *it == seq.back()) continue;
        list<int>::iterator lft,  lft1,  lft2;
        lft = prev(it, 1);
        lft1 = it;
        lft2 = next(it, 1);
        if(CheckCondition(*lft, *lft1, *lft2)) {
            cout << *lft1 << ' ';
        }
        else {
            flag = false;
            break;
        }
    }
    cout << seq.back() << '\n';
    if(!flag)
        cout << "맹목적인 규칙이 안맞음" << '\n';
}

#endif

void HandleInput(istream& ins) {
    int N; ins >> N;
#if DEBUG
    cout << "Set N " << '\n';
#endif
    bool backFlag = true, frontFlag = true;
    seq.push_back(1); seq.push_back(2);
#if DEBUG
    cout << "insert Tview " << '\n';
#endif
    for(int i = 3 ; i <= N; i++) {
        IterPos nxtPos = GetValidPos(i);
        if(nxtPos == IterPos::None) {backFlag = false; break;}
        if(nxtPos == IterPos::Left) {  seq.push_front(i);  }
        else if(nxtPos == IterPos::Right) {  seq.push_back(i); }
        for(const auto& i : seq ) {
            cout << i << ' ';
        } cout << '\n';
    }
    if(backFlag == true) {
        for(const auto& i : seq ) {
            cout << i << ' ';
        } cout << '\n';
        cout << "YES" << '\n';
        return; 
    }
#if DEBUG
    IS_ANSWER_ITERATE_RIGHT();
#endif
    seq.clear();
    seq.push_front(1); seq.push_front(2);
    #if DEBUG
        cout << "insert Tview " << '\n';
    #endif
    for(int i = 3 ; i <= N; i++) {
        IterPos nxtPos = GetValidPos(i);
        if(nxtPos == IterPos::None) {backFlag = false; break;}
        if(nxtPos == IterPos::Left) {  seq.push_front(i);  }
        else if(nxtPos == IterPos::Right) {  seq.push_back(i); }
        for(const auto& i : seq ) {
            cout << i << ' ';
        } cout << '\n';
    }
    if(frontFlag == true) {
        for(const auto& i : seq ) {
            cout << i << ' ';
        } cout << '\n';
        cout << "YES" << '\n';
        return; 
    }
    cout << "NO" << '\n';
}

void HandleQuery(const char* FILE_PATH){
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

int main(int argc, const char* args[]) {
    cout << boolalpha;
    if(argc > 1) {
        HandleQuery(args[1]);
    }    
    else {
        HandleInput(cin);
    }
}