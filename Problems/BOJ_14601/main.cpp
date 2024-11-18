#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

const int MAX_LOOP = 10;

int LOOP_CNT = 0;

struct BIndex {
    int xL, xR, yU, yD;
};

const int HOLE = -1;
const int MAX_TILE = (1 << 8) + 1;
vector<vector<int>> fT(MAX_TILE, vector<int>(MAX_TILE, 0));
int L;

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

bool IsOutofBound(const BIndex& bi) {
    bool flag = true;
    if(bi.xL <= 0) flag = false;
    if(L < bi.xR) flag = false;
    if(bi.yD <= 0) flag = false;
    if(L < bi.yU) flag = false;
    return flag;
}

bool IsColorable(const BIndex& bi) {
    if(abs(bi.xL - bi.xR) == 1) return true;
    if(abs(bi.yD - bi.yU) == 1) return true;
    return false;
}

bool IsTwoByColorable(const BIndex& bi) {
    if(abs(bi.xL - bi.xR) == 3) return true;
    if(abs(bi.yD - bi.yU) == 3) return true;
    return false;
}

void PRINT_BINDEX(const BIndex& bi) {
    cout << bi.xL  << " " << bi.xR  << " " << bi.yU  << " " << bi.yD  << endl;
}
void PRINT_VECTOR(const vector<vector<int>>& fT, const BIndex& bi) {
    cout << "START" << endl;
    PRINT_BINDEX(bi);
    for(int i = bi.yU; bi.yD <= i ; i--) {
        for(int j = bi.xL; j <= bi.xR; j++) {
            cout << fT[i][j] << ' ';
        } cout << '\n';
    }
    cout << "END" << endl;
}

// 3 4 4 3
// 3 3 3 3
// 3 3 4 4
// 4 4 3 3
// 4 4 4 4

void RECURSION_PRINT(vector<vector<int>>& fT, const BIndex& bi, int fourDiv, int& nextColor) {
    LOOP_CNT++;
    if(LOOP_CNT >= MAX_LOOP) return;
    PRINT_VECTOR(fT, bi);
    if(!IsOutofBound(bi)) return;
    if(IsColorable(bi)) {
        int NonColor; int NonColorIdxX, NonColorIdxY; 
        switch (fourDiv)
        {
            case 1 : {NonColorIdxX = bi.xL + 0; NonColorIdxY = bi.yD + 0; break;}
            case 2 : {NonColorIdxX = bi.xL + 1; NonColorIdxY = bi.yD + 0;break;}
            case 3 : {NonColorIdxX = bi.xL + 0; NonColorIdxY = bi.yD + 1; break;}
            case 4 : {NonColorIdxX = bi.xL + 1; NonColorIdxY = bi.yD + 1; break;}
        }
        NonColor = fT[NonColorIdxX][NonColorIdxY];
        fT[bi.xL][bi.yD] = nextColor;
        fT[bi.xL][bi.yU] = nextColor;
        fT[bi.xR][bi.yD] = nextColor;
        fT[bi.xR][bi.yU] = nextColor;
        fT[NonColorIdxX][NonColorIdxY] = NonColor;
        nextColor++;
    }
    RECURSION_PRINT(fT, {bi.xL, bi.xR / 2, bi.yU /2, bi.yD}, 3, nextColor);               // 3 ㄴ (2 2) (+1, +1)
    RECURSION_PRINT(fT, {(bi.xR / 2) + 1, bi.xR, bi.yU /2, bi.yD}, 4, nextColor);         // 4 ㅢ (1 2) (+0, +1)
    RECURSION_PRINT(fT, {bi.xL, bi.xR / 2, bi.yU, (bi.yU / 2) + 1}, 2, nextColor);        // 2 ㅏ (2 1) (+1, +0)
    RECURSION_PRINT(fT, {(bi.xR / 2) + 1, bi.xR, bi.yU, (bi.yU / 2) + 1}, 1, nextColor);  // 1 ㄱ (1 1) (+0, +0)
    if(IsTwoByColorable(bi)) {
        for(int i = bi.yU; bi.yD <= i ; i--) {
            for(int j = bi.xL; j <= bi.xR; j++) {
                if(fT[i][j] != -1 || fT[i][j] == 0) {
                    fT[i][j] = nextColor;
                }
            }
        }
        nextColor++;
    }
}

#endif

void InitLoop() { LOOP_CNT = 0; }


int GLOBAL_COLOR = 1;
void HandleInput(istream& ins) {
    int num;
    int hX, hY;
    InitLoop();
    for(LOOP_CNT = 0; (!ins.eof() && LOOP_CNT < MAX_LOOP); ++LOOP_CNT) {
        ins >> num;
        if(ins.fail()) {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
        L = 1 << num;
        ins >> hX >> hY;
        fT[hX][hY] = HOLE;

        #if DEBUG
        // PRINT_VECTOR(fT, {1, L, L, 1});
        InitLoop();
        RECURSION_PRINT(fT, {1, L, L, 1}, 0, GLOBAL_COLOR);
        #endif
    }
    if(LOOP_CNT >= MAX_LOOP) abort();

    PRINT_VECTOR(fT, {1, L, L, 1});
}


int main(int argc, char* argv[]) {
    ArgHandler(argc, argv);
    return 0;
}