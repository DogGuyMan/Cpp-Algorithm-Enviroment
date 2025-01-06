#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<vector<ll>> matrix;

matrix MatMul(matrix& A, matrix& B) {
    int ARow = A.size(), ACol = A[0].size();
    int BRow = B.size(), BCol = B[0].size();
    assert(ACol == BRow);
    matrix C = matrix(ARow, vector<ll>(BCol));
    for(int row = 0; row < ARow; row++) {
        for(int k = 0; k < ACol; k++) {
            for(int col = 0; col < BCol; col++) {
                C[row][col] += A[row][k] * B[k][col];
            }
        }
    }
    return C;
}

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        int AN, AM;
        ins >> AN >> AM;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        // cout << " AN : "  << AN << " AM : " << AM << '\n';
        matrix A = matrix(AN, vector<ll>(AM));
        for(int i = 0; i < AN; i++) {
            for(int j = 0; j < AM; j++) {
                ins >> A[i][j];
            }
        }

        int BM, BK;
        ins >> BM >> BK;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        // cout << " BM : "  << BM << " BK : " << BK << '\n';
        matrix B = matrix(BM, vector<ll>(BK));
        for(int i = 0; i < BM; i++) {
            for(int j = 0; j < BK; j++) {
                ins >> B[i][j];
            }
        }

        matrix C = MatMul(A, B);
        for(auto& row : C) {
            for(ll& col : row) {
                cout << col << ' ';
            }
            cout << '\n';
        }
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