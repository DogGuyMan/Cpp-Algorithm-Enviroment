#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DEBUG 0
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<vector<ld>> matrix;
const ld EPS = 1e-9;

matrix MatMul(matrix& A, matrix& B) {
    int ARow = A.size(), ACol = A[0].size();
    int BRow = B.size(), BCol = B[0].size();
    assert(ACol == BRow);
    matrix C = matrix(ARow, vector<ld>(BCol));
    for(int row = 0; row < ARow; row++) {
        for(int k = 0; k < ACol; k++) {
            for(int col = 0; col < BCol; col++) {
                C[row][col] += A[row][k] * B[k][col];
            }
        }
    }
    return C;
}

int N, M;
matrix MT;

void PrintMT(const matrix& mt) {
    for(const auto& row : mt) {
        for(const ld& col : row) {
            cout << setw(6) << col << ' ';
        }
        cout << '\n';
    }
}

void RowAdd (matrix& mt, int from, int to, ld x) {
    for(int i = 0; i < M; i++) {mt[to][i] += mt[from][i] * x;}
}

void RowMul (matrix& mt, int rowIdx, ld x) {
    for(int i = 0; i < M; i++) {mt[rowIdx][i] *= x;}
}
void RowSwap(matrix& mt, int a, int b) {
    swap(mt[a], mt[b]);
}

void RREF() {
    int unsolvedCol = 0;
    for(int i = unsolvedCol; i < N; i++) {
        // 행 교환
        int leading = i;
        if(fabs(MT[leading][leading]) < EPS) {
            for(int row = leading + 1; row < N; row++) {
                if(MT[row][unsolvedCol] != 0) {
                    RowSwap(MT, leading, row);
                    break;
                }
            }
        }
#if DEBUG
        cout << "행 교환" << '\n';
        PrintMT(MT);
#endif
        // lead to one
        if(fabs(MT[leading][leading]) >= EPS) {
            ld mulAmt = MT[leading][leading];
            RowMul(MT, leading, (1/mulAmt));
#if DEBUG
            cout << "lead to one" << '\n';
            PrintMT(MT);
#endif

            // 행 사다리 꼴 + Reduce 하기
            for(int row = 0; row < N; row++) {
                if(leading == row) {continue;}
                RowAdd(MT, leading, row, -(MT[row][unsolvedCol]));
            }
#if DEBUG
            cout << "행 사다리 꼴 + Reduce 하기" << '\n';
            PrintMT(MT);
#endif
            unsolvedCol++;
            if(unsolvedCol >= N) {break;}
        }
    }
}

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        ins >> N;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        M = N + 1;
        MT = matrix(N, vector<ld>(M));
        for(int i = 0 ; i < N; i++) {
            for(int j = 0 ; j < M; j++) {
                ins >> MT[i][j];
            }
        }
#if DEBUG
        cout << " N : " << N << " M : " <<  M << '\n';
        PrintMT(MT);
#endif  
        RREF();
        for(int i = 0; i < N; i++) {
            cout << MT[i][M-1] << ' ';
        } cout << '\n';
    }
}
void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[]) {
    if(argc <= 1) {
        FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}