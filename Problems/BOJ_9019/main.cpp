#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

void HandleInput(istream& ins) {

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
        char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}