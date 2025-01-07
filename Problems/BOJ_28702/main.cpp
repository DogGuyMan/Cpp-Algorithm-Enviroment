#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
using namespace std;
typedef long long ll;

int QUERY_CNT = 1;

void HandleInput(istream& ins) {
    while(!ins.eof() && QUERY_CNT-- > 0 ) {
        int input[3] = {0,};
        string trash;
        int intIdx = -1;
        for(int i = 0; i < 3; i++) {
            ins >> input[i];
            if(ins.fail()) { ins.clear();  ins >> trash; continue; }
            intIdx = i;
        }
        switch(intIdx) {
            case 0 : {input[0] = input[0];      input[1] = input[0] + 1;    input[2] = input[0] + 2;}
            case 1 : {input[0] = input[1]-1;    input[1] = input[1];        input[2] = input[1] + 1;}
            case 2 : {input[0] = input[2]-2;    input[1] = input[2] - 1;    input[2] = input[2];}
        }
        int nxt= input[2] + 1;
        if( (nxt % 3) == 0) {cout << "Fizz";}
        if( (nxt % 5) == 0) {cout << "Buzz";}
        if( (nxt % 3) != 0 && (nxt % 5) != 0 ) {cout << nxt;}
        cout << '\n';
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