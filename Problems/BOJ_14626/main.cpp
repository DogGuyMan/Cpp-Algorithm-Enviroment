#include <bits/stdc++.h>
using namespace std;

// #define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

int HandleInput(istream& ins) {
    int num[13] = {0,};
    string str = "";
    ins >> str;
    int qnum = -1;
    for(int i = 0; i < 13; i++) {
        if(str[i] == '*') {
            qnum = i;
            // cout << '*' << '\n';
            num[i] = 0;
            continue;
        }
        num[i] = str[i] - 48;
        // cout << num[i] << '\n';
    }

    for(int i = 0; i <= 9; i++) {
        num[qnum] = i;
        int isbn    =       num[0]
                    +   3*  num[1]
                    +       num[2]
                    +   3*  num[3]
                    +       num[4]
                    +   3*  num[5]
                    +       num[6]
                    +   3*  num[7]
                    +       num[8]
                    +   3*  num[9]
                    +       num[10]
                    +   3*  num[11]
                    +       num[12];
        
        
        if(isbn % 10 == 0) {
            cout << i << '\n';
            break;
        }
    }
    return 0;
}

int HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) { return HandleInput(fs); }
    return 0;
}

int main(int argc, const char* argv[]) {
    if(argc <= 1) {
        // FASTIO;
        return HandleInput(cin);
    }
    return HandleQuery(argv[1]);
}