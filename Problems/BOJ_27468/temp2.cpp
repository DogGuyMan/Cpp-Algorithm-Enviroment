#include <iostream>
#include <list>
#include <fstream>
using namespace std;

list<int> seq;
int N;

bool CheckCondition(int ai, int ai1, int ai2) {
    bool flag1 = (abs(ai1 - ai) == (2 * abs(ai1 - ai2)));
    bool flag2 = ((2 * abs(ai1 - ai)) == abs(ai1 - ai2));
#if DEBUG
    cout << "MUL2 : " << flag1 << " DIV2 : " << flag2 << '\n';
#endif
    return (flag1 || flag2);
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

void HandleInput(istream& ins){
    ins >> N;
    
    // 결과 수열을 저장할 벡터
    
    
    // 첫 원소와 두번째 원소 고정: 1, 2
    seq.push_back(1);
    seq.push_back(2);
    
    // 1,2,4는 이미 사용되었으므로 3부터 N까지 중 4는 제외하고 넣기
    for (int i = 3; i <= N; i++) {
        if(i == 4) continue;
        seq.push_back(i);
    }
    
    // 마지막 원소로 4 추가
    seq.push_back(4);
    IS_ANSWER_ITERATE_RIGHT();
    // 출력: 공백으로 구분하여 출력
    for(const auto& i : seq ) {
        cout << i << ' ';
    } cout << '\n';
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