#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#define DEBUG 0
using namespace std;

ostream& operator<<(ostream& os, const vector<char>& resStr) {
    for(const auto& c : resStr) {os << c;}
    return os;
}

bool isPop(const string& flagStr, const vector<char>& resStr) {
    int curResSize = resStr.size();
    int flagSize = flagStr.size();
    for(int i = 0; i < flagStr.size(); i++) {
        if(flagStr[i] != resStr[(curResSize-flagSize) + i]) 
            return false;
    }
    return true;
}

void HandleInput(istream& ins) {
	
    string str, flagStr;
	ins >> str >> flagStr;

	stringstream ss(str);
	
    vector<char> resStr;
	while(!ss.eof()){
		char c; ss >> c;
        if(ss.fail()) {ss.clear(); ss.ignore('\n'); continue;}
        resStr.push_back(c);
        if(isPop(flagStr, resStr)) {
            int popCnt = flagStr.size();
            while(popCnt--) {resStr.pop_back();}
        }
		
#if DEBUG 
        cout << resStr << '\n';
#endif
	}
	(resStr.size() != 0)
        ? cout << resStr << '\n'
        : cout << "FRULA" << '\n';
}

void HandleQuery(char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}


int main(int argc, char* args[]){
    if(argc <= 1) {
        cin.tie(0)->sync_with_stdio(0);
        HandleInput(cin);
    }
    else {
        char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}
