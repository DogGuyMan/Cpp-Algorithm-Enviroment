#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#define DEBUG 0
#define RREF_DEBUG 0
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<vector<ld>> matrix;
const ld EPS = 1e-9;

int QUERY_CNT = 1;
char *FILE_PATH;
int T;

bool RREF(matrix &mt)
{
    int unsolvedCol = 0;
    int MXRow = mt.size();
    int MXCol = 4;
    for(int col = 0; col < MXCol; col++) {
        int pivotRow = col;
        long double mx = fabsl(mt[col][col]);
        for(int r = col + 1; r < MXRow; r++) {
            if(fabsl(mt[r][col]) > mx) {
                mx = fabsl(mt[r][col]);
                pivotRow = r;
            }
        }

        if(pivotRow != col) {
            swap(mt[col], mt[pivotRow]);
        }

        if(fabsl(mt[col][col]) < 1e-15) {
            continue;
        }

        long double pivotVal = mt[col][col];
        for(int c = col; c <= MXCol; c++) {
            mt[col][c] /= pivotVal;
        }

        for(int row = col + 1; row < MXRow; row++) {
            long double factor = mt[row][col];
            for(int c = col; c <= MXCol; c++) {
                mt[row][c] -= factor * mt[col][c];
            }
        }
    }

    for(int row = 0; row < MXRow; row++) {
        if(fabsl(mt[row][0]) < EPS &&
           fabsl(mt[row][1]) < EPS &&
           fabsl(mt[row][2]) < EPS &&
           fabsl(mt[row][3]) < EPS) 
        {
            if(fabsl(mt[row][4]) > EPS) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *args[])
{
    FASTIO;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        matrix linearMt = matrix(N, vector<ld>(5));
        ll seq[505] = { 0, };
        for (int i = 0; i < N; i++)
        {
            cin >> seq[i];
            int powNum = i + 1;
            linearMt[i][0] = (ld) powNum*powNum*powNum;
            linearMt[i][1] = (ld) powNum*powNum;
            linearMt[i][2] = (ld) powNum;
            linearMt[i][3] = 1.0L;
            linearMt[i][4] = (ld) seq[i];
        }

        if(N < 4) {cout << "YES" << '\n'; continue;}

        bool ansFlag = RREF(linearMt);
        (ansFlag == true)
            ? cout << "YES" << '\n'
            : cout << "NO" << '\n';
    }
}