#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <bitset>
#include <assert.h>
#define FESTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MP make_pair
#define X first
#define Y second
using namespace std;
const double ESP = 1e-6;

/*
46	28	10
118	73	28
190	118	46

    B1	    B2	    B3
1	1/4	    -1/2	0
2	1/2	    1/2	    -1/2
3	-1/4    1/6	    1/3
*/

#pragma region Matrix Class

class Matrix
{
private:
    int n, m;
    vector<vector<double>> entry;

public:
    static Matrix CreateIdentityMatrix(int n_)
    {
        Matrix I(n_);
        for (int i = 0; i < n_; i++)
            I[{i, i}] = 1;
        return I;
    }
    Matrix() {}
    Matrix(int n_, int m_) : n(n_), m(m_), entry(n_, vector<double>(m_)) {}
    Matrix(int n_) : Matrix(n_, n_) {}
    double &operator[](const pair<int, int> &p)
    {
        return entry[p.X][p.Y];
    }
    const double &operator[](const pair<int, int> &p) const
    {
        return entry[p.X][p.Y];
    }
    void RowSwap(int lhsIdx, int rhsIdx)
    {
        swap(entry[lhsIdx], entry[rhsIdx]);
    }
    void RowMultiplication(int idx, double x)
    {
        for (int j = 0; j < m; j++)
        {
            entry[idx][j] *= x;
            if (abs(entry[idx][j]) < ESP)
            {
                entry[idx][j] = 0;
            }
        }
    }
    void RowAddition(int r1, int r2, double x)
    {
        for (int j = 0; j < m; j++)
        {
            entry[r1][j] += entry[r2][j] * x;
            if (abs(entry[r1][j]) < ESP)
            {
                entry[r1][j] = 0;
            }
        }
    }
    friend int REF(Matrix &mt);
    friend int RREF(Matrix &mt);
    friend int Determinant(Matrix &mt);
    friend Matrix MatInv(Matrix &mt);
    friend void LU(Matrix &mt, Matrix *Lout, Matrix *Uout);
    friend void LU2(Matrix *Lout, Matrix *Uout);
    friend ostream &operator<<(ostream &os, const Matrix &rhs);
    friend Matrix operator*(const Matrix &A, const Matrix &B);
};

Matrix operator*(const Matrix &A, const Matrix &B)
{
    assert(A.m == B.n);
    Matrix C(A.n, B.m);
    for (int i = 0; i < C.n; i++)
    {
        for (int k = 0; k < A.m; k++)
        {
            for (int j = 0; j < C.m; j++)
            {
                C[{i, j}] += A[{i, k}] * B[{k, j}];
            }
        }
    }
    return C;
}

ostream &operator<<(ostream &os, const Matrix &rhs)
{
    cout.precision(3);
    for (const auto &row : rhs.entry)
    {
        for (const auto &col : row)
        {
            cout << setw(6) << ((abs(col - ESP) < 0) ? 0 : col) << ' ';
        }
        cout << '\n';
    }
    return os;
}

int REF(Matrix &mt)
{
    int unsolvedRow = 0;
    for (int col = 0; col < mt.m; col++)
    {
        for (int row = unsolvedRow; row < mt.n; row++)
        {
            if (mt[{row, col}] != 0)
            {
                mt.RowSwap(unsolvedRow, row);
                break;
            }
        }
        if (mt[{unsolvedRow, col}] != 0)
        {
            mt.RowMultiplication(unsolvedRow, (1 / mt[{unsolvedRow, col}]));
            for (int i = unsolvedRow + 1; i < mt.n; i++) // REF는 정대각 행렬때문에 열 = 열 & 행 = 열
            {
                mt.RowAddition(i, unsolvedRow, -mt[{i, col}]);
            }
            unsolvedRow++;
            if (unsolvedRow >= mt.n)
                return -1;
        }
    }
    return unsolvedRow;
}

int RREF(Matrix &mt)
{
    int unsolvedRow = 0;
    for (int col = 0; col < mt.m; col++)
    {
        for (int row = unsolvedRow; row < mt.n; row++)
        {
            if (mt[{row, col}] != 0)
            {
                mt.RowSwap(unsolvedRow, row);
                // cout << "row swap " << unsolvedRow << " to " << row << '\n' << mt << '\n';
                break;
            }
        }
        if (mt[{unsolvedRow, col}] != 0)
        {
            double mulAmount = (1 / mt[{unsolvedRow, col}]);
            mt.RowMultiplication(unsolvedRow, mulAmount);
            // cout << "mt.RowMultiplication : " << mulAmount << '\n' << mt << '\n';
            for (int i = 0; i < mt.n; i++) // 얘는 상관없이 걍 쫙 현재 열에 해당하는 모든 행을 클리어한다.
            {
                if (i != unsolvedRow)
                {
                    mt.RowAddition(i, unsolvedRow, -mt[{i, col}]);
                    // cout << "mt.RowAddition unsolvedRow : " << unsolvedRow << " i : " << i << '\n' << mt << '\n';
                }
            }
            unsolvedRow++;
            if (unsolvedRow >= mt.n)
                return -1;
        }
    }
    return unsolvedRow;
}

int Determinant(Matrix &mt)
{
    double res = 1;
    assert(mt.n == mt.m);
    REF(mt);
    for (int i = 0; i < mt.n; i++)
    {
        res *= mt[{i, i}];
    }
    return res;
}

Matrix MatInv(Matrix &mt)
{
    int row = mt.n;
    int col = mt.m;
    Matrix Aug(col, row + row);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            Aug[{i, j}] = mt[{i, j}];
        }
        Aug[{i, i + col}] = 1;
    }
    cout << Aug << '\n';
    RREF(Aug);
    cout << Aug << '\n';
    Matrix Inv(row);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            Inv[{i, j}] = Aug[{i, j + col}];
        }
    }
    cout << Inv << '\n';
    return Inv;
}

void LU2(Matrix *Lout, Matrix *Uout)
{
    int n = Lout->n;

    cout << "L\n"
         << (*Lout) << '\n';
    cout << "U\n"
         << (*Uout) << '\n';

    for (int leading = 0; leading < n - 1; leading++) // ↓ ↓ ↓
    {                                                 // LU 분해
        for (int row = leading + 1; row < n; row++)   // L에 역행렬 곱하기 역행렬 곱할때, 그냥 순서대로 하나하나씩 해도 행렬곱을 싸그리 할 필요 없구나.
        {
            double mulInv = (*Uout)[{row, leading}] / (*Uout)[{leading, leading}];
            double &unsolvedLadingCol = (*Lout)[{row, leading}];
            unsolvedLadingCol = mulInv;
        }

        for (int row = leading + 1; row < n; row++) // U REF 만들기
        {
            double rowAddAmountForZero = -(*Lout)[{row, leading}];
            (*Uout).RowAddition(row, leading, rowAddAmountForZero);

            // for (int col = leading; col < n; col++)
            // {
            //     (*Uout)[{row, col}] = (*Uout)[{row, col}] - (*Lout)[{row, leading}] * (*Uout)[{leading, col}];
            // }
        }

        cout << "L\n"
             << (*Lout) << '\n';
        cout << "U\n"
             << (*Uout) << '\n';
    }
}

#pragma endregion

int N;
unordered_map<char, Matrix> MT;

void TEST_MATRIX(istream &ins)
{
    ins >> N;
    for (int i = 0; i < N; i++)
    {
        char ch = '-';
        int row, col;
        ins >> row >> col >> ch;
        Matrix mt(row, col);
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                int mtval;
                ins >> mtval;
                mt[MP(r, c)] = mtval;
            }
        }
        MT[ch] = mt;
        // cout << "MT[" << ch << "]\n" << MT[ch] << '\n';
        // MatInv(MT[ch]);
        // REF(MT[ch]);
        // cout << "RREF[" << ch << "]\n" << MT[ch] << '\n';
        // int detRes = Determinant(MT[ch]);
        // cout << "Determinant[" << ch << "] : " << Determinant(MT[ch]) << '\n';
        // if(detRes > 0) MatInv(MT[ch]);
        // MatInv(MT[ch]);
        auto LRes = Matrix::CreateIdentityMatrix(row);
        auto URes = MT[ch];
        LU2(&LRes, &URes);
        // auto URes = Matrix::CreateIdentityMatrix(row);
        // LU(MT[ch], &LRes, &URes);
        // cout << "REF \n" << MT[ch] << '\n';
        cout << "L Matrix \n"
             << LRes << '\n';
        cout << "U Matrix \n"
             << URes << '\n';
    }
    // MT['C'] = (MT['A'] * MT['B']);
    // cout << MT['C'];
    // REF(MT['A']);
    // cout << "REF(MT[A])\n" << MT['A'] << '\n';
}

void HandleInput(istream &ins)
{
    while (!ins.eof())
    {
        TEST_MATRIX(ins);
        if (ins.fail())
        {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
    }
}

void HandleQuery(const char *queryFilePath)
{
    fstream fs(queryFilePath);
    if (fs.is_open())
    {
        HandleInput(fs);
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "HandleInput(cin)" << endl;
        FESTIO;
        HandleInput(cin);
    }
    else
    {
        cout << "HandleQuery(FILE_NAME)" << endl;
        const char *FILE_NAME = argv[1];
        HandleQuery(FILE_NAME);
    }
}