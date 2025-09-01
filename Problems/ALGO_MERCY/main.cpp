#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define X first
#define Y second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const char * HELLO_ALGOSPOT = "Hello Algospot!";

void HandleInput(istream& ins) {
        int N; 
        ins >> N;
        for(int i =0 ;i < N ;i++ )
                cout << HELLO_ALGOSPOT << '\n';
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

int main(int argc, const char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        HandleQuery(args[1]);
    }
}
