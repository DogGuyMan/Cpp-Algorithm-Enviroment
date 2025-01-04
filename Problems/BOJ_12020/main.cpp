#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#define FESTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
typedef long long ll;
typedef vector<vector<double>> matrix;
const double EPS = 1e-9;

int N;
matrix L;
matrix U;

void PrintMT(matrix &mt)
{
    cout << fixed;
    cout.precision(3);

    for (const auto &row : mt)
    {
        for (const double &col : row)
        {
            cout << setw(4) << col << ' ';
        }
        cout << '\n';
    }
}

matrix MatMul(matrix &a, matrix &b)
{
    matrix c = matrix(N, vector<double>(N));
    for (int row = 0; row < c.size(); row++)
    {
        for (int k = 0; k < b.size(); k++)
        {
            for (int col = 0; col < c[0].size(); col++)
            {
                c[row][col] += a[row][k] * b[k][col];
            }
        }
    }
    return c;
}

void RowMul(matrix &mt, int rowIdx, double x)
{
    if (fabs(x) < EPS)
        x = 0;
    for (int i = 0; i < N; i++)
    {
        mt[rowIdx][i] *= x;
    }
}

void RowSwap(matrix &mt, int aIdx, int bIdx)
{
    swap(mt[aIdx], mt[bIdx]);
}

void RowAdd(matrix &mt, int from, int to, double x)
{
    if (fabs(x) < EPS)
        x = 0;
    for (int i = 0; i < N; i++)
    {
        mt[to][i] += (mt[from][i] * x);
    }
}

matrix GenIdentity()
{
    matrix mt = matrix(N, vector<double>(N));
    for (int i = 0; i < N; i++)
    {
        mt[i][i] = 1;
    }
    return mt;
}

void HandleInput(istream &ins)
{
    while (!ins.eof())
    {
        ins >> N;
        if (ins.fail())
        {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
        if (N <= 1)
        {
            cout << -1 << '\n';
            return;
        }
        L = matrix(N, vector<double>(N));
        U = matrix(N, vector<double>(N));
        for (int i = 0; i < N; i++)
        {
            L[i][i] = 1;
            for (int j = 0; j < N; j++)
            {
                ins >> U[i][j];
            }
        }

        for (int leadingCol = 0; leadingCol < N - 1; leadingCol++)
        {
            if(fabs(U[leadingCol][leadingCol]) < EPS) // 분모가 0이 되면 안되니깐..
            {
                cout << -1 << '\n';
                return;
            }
            int LInvColSolve = leadingCol + 1;           // L 분해에 있어 해결해야하는 열을 차례로 row
            for (int row = LInvColSolve; row < N; row++)
            {
                double addAmt = (U[row][leadingCol] / U[leadingCol][leadingCol]);
                RowAdd(U, leadingCol, row, -addAmt);
                L[row][leadingCol] = addAmt;
            }
        }

        PrintMT(L);
        PrintMT(U);
    }
}
void HandleQuery(const char *FILE_PATH)
{
    fstream fs(FILE_PATH);
    if (fs.is_open())
    {
        HandleInput(fs);
    }
}

int main(int argc, char *args[])
{
    if (argc <= 1)
    {
        FESTIO;
        HandleInput(cin);
    }
    else
    {
        const char *FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}