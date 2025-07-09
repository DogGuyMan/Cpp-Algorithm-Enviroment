#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long ll;

string INPUT_FORMULA;
vector<char> ANS;
int GLOBAL_IDX = 0;

bool IsMulOperator(char c) {
    return c == '*' || c== '/';
}
bool IsSumOperator(char c) {
    return c == '+' || c == '-';
}

void PRINT_STR(vector<char>& str) {
    for(char& e : str) {
        if(e == ')' || e == '(') continue;
        cout << e;
    } cout << '\n';
}

void HandleStr(vector<char>& ans, queue<char>& op, vector<char>& curStr) {
    if(op.empty()) {
        for(auto& curChar : curStr) 
            ans.push_back(curChar);
    }
    else {
        for(auto& curChar : curStr)
            ans.push_back(curChar);
        while(!op.empty()) {
            ans.push_back(op.front()); op.pop();
        }
    }
}
void HandleChar(vector<char>& ans, queue<char>& op, char& curChar) {
    if(op.empty()) {
        ans.push_back(curChar);
    }
    else {
        ans.push_back(curChar);
        while(!op.empty()) {
            ans.push_back(op.front()); op.pop();
        }
    }
}

void SolveMidToPost(vector<char> & ans) {
    queue<char> op;
    for(GLOBAL_IDX; GLOBAL_IDX < INPUT_FORMULA.size(); GLOBAL_IDX++) {
        char curChar = INPUT_FORMULA[GLOBAL_IDX];
        if(curChar == ')') {ans.push_back(')'); return;}
        if(curChar == '(') {
            GLOBAL_IDX++;
            vector<char> newRes;
            ans.push_back('(');
            SolveMidToPost(newRes);
            HandleStr(ans, op, newRes);

            continue;
        }
        if(IsMulOperator(curChar)) {
            op.push(curChar);
            bool isOpPopLoop = (IsSumOperator(ans.back()));
            if(isOpPopLoop) {
                op.push(ans.back());
                ans.pop_back();
                isOpPopLoop = (IsSumOperator(ans.back()));
            }

            continue;
        }
        if(IsSumOperator(curChar)) {
            op.push(curChar);

            continue;
        }
        HandleChar(ans, op, curChar);

    }
    while(!op.empty()) {
        ans.push_back(op.front()); op.pop();
    }
}

void HandleInput(istream& ins) {
    ins >> INPUT_FORMULA;
    SolveMidToPost(ANS);
    PRINT_STR(ANS);
}

void HandleQuery(const char * FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}
int main(int argc, const char * argv[]) {
    if(argc > 1) {
        HandleQuery(argv[1]);
    }
    else {
        ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        HandleInput(cin);
    }
}
