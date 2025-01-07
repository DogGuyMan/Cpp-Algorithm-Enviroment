#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int A, B, C;

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        ins >> A >> B >> C;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        cout << (A + B) - C << '\n';
        int muls = 10;
        for(int i = 0 ; i < (int)log10(B); i++) {muls*=10;}
        cout << ((A * muls) + B ) - C << '\n';
    }
}
void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) HandleInput(fs);
}

int main(int argc, char * args[]) {
    if(argc <= 1) {
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}