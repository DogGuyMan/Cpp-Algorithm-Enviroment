#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>

#define DEBUG 1
using namespace std;
namespace fs = std::filesystem;

const int MAX_LOOP = 1e4;

int LOOP_CNT = 0;

void HandleInput(istream& ins);
void ArgHandler(int argc, char* argv[]);
void HandleQuery(const char* QueryDataPath);

void ArgHandler(int argc, char* argv[]) {
    if(argc == 1) {
        HandleInput(cin);
        return;
    }

    int QUERY_MODE = atoi(argv[1]);
    
    #if DEBUG
    cout << "QUERY_MODE : "<< QUERY_MODE << '\n';
    #endif
    
    if(QUERY_MODE == 1) {
        const char * FILE_PATH = argv[2];
        #if DEBUG
        cout << FILE_PATH << '\n';
        #endif
        HandleQuery(FILE_PATH);
    }
}

void HandleQuery(const char* QueryDataPath) {
    fstream fs;
    fs.open(QueryDataPath);
    
    #if DEBUG
        cout << boolalpha << "FileName : " << QueryDataPath << " Opened : " << fs.is_open() << endl;
    #endif

    if(fs.is_open()) {
        HandleInput(fs);
    }
    fs.clear();
    fs.close();
}

#if DEBUG
void PRINT_VECTOR(const vector<vector<int>>& fT, const int& Bound) {
    cout << "START" << endl;
    for(int i = 0; i < Bound; i++) {
        for(int j = 0; j < Bound; j++) {
            cout << fT[i][j] << ' ';
        } cout << '\n';
    }
    cout << "END" << endl;
}
#endif

const int HOLE = -1;
const int MAX_TILE = (1 << 7) + 1;
vector<vector<int>> fT(MAX_TILE, vector<int>(MAX_TILE, 0));
void InitLoop() { LOOP_CNT = 0; }

void HandleInput(istream& ins) {
    int num;
    int hX, hY;
    InitLoop();
    for(LOOP_CNT = 0; (!ins.eof() && LOOP_CNT < MAX_LOOP); ++LOOP_CNT){
        ins >> num;        
        if(ins.fail()) {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
        int l = 1 << num;
        ins >> hX >> hY;
        fT[hX][hY] = HOLE;
        #if DEBUG
        PRINT_VECTOR(fT, l);
        #endif
    }
    if(LOOP_CNT >= MAX_LOOP) abort();
}

int main(int argc, char* argv[]) {
    ArgHandler(argc, argv);
    // #if QUERY
    // HandleQuery();
    // #else
    // HandleInput(cin);
    // #endif
    return 0;
}