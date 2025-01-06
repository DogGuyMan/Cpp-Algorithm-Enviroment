#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DEBUG 0
using namespace std;
typedef long long ll;
typedef long double ld;
const ld EPS = 1e-9;

class Bunsu
{
public:
    const char delimiter = '/';
    __int128 Mo = 0;
    __int128 Ja = 0;
    Bunsu() : Mo(0), Ja(0) {}
    Bunsu(__int128 ja, __int128 mo) : Mo(mo), Ja(ja) {}
    // 이부분이 c_string 하면서 문제가 있었던것 같은데/
    Bunsu(string bunsu)
    {
        if (bunsu.find(delimiter) == string::npos)
        {
            Ja = stoi(bunsu.c_str());
            Mo = 1;
            return;
        }
        // cout << num[0] << ", " << num[1] << '\n';
        Ja = stoi(bunsu.substr(0, bunsu.find(delimiter)));
        Mo = stoi(bunsu.substr(bunsu.find(delimiter) + 1, string::npos));
        YackBun();
    }

    __int128 GCD(__int128 a, __int128 b) { return (((b) == 0) ? ((a)) : GCD((b), ((a) % (b)))); }
    __int128 LCM(__int128 a, __int128 b) { return ((a) * (b)*GCD((a), (b))); }
    void YackBun()
    {
        __int128 gcd = GCD(Ja, Mo);
        Mo /= gcd;
        Ja /= gcd;
        if (Mo < 0)
        {
            Mo = -Mo;
            Ja = -Ja;
        }
    }

    Bunsu & Invert() {
        __int128 tmp = Mo;
        Mo = Ja;
        Ja = tmp;
        return *this;
    }

    Bunsu &operator=(const Bunsu &rhs)
    {
        Mo = rhs.Mo;
        Ja = rhs.Ja;
        return *this;
    }

    Bunsu operator+(const Bunsu &rhs)
    {
        Bunsu res;
        __int128 prvMo = Mo, prvJa = Ja;
        res.Mo = rhs.Mo * prvMo;
        res.Ja = (rhs.Ja * prvMo) + (prvJa * rhs.Mo);
        res.YackBun();
        return res;
    }
    Bunsu operator-(const Bunsu &rhs)
    {
        Bunsu res;
        __int128 prvMo = Mo, prvJa = Ja;
        res.Mo = rhs.Mo * prvMo;
        res.Ja = (prvJa * rhs.Mo) - (rhs.Ja * prvMo);
        res.YackBun();
        return res;
    }
    Bunsu operator/(const Bunsu &rhs)
    {
        Bunsu res;
        res.Mo = rhs.Ja * Mo;
        res.Ja = rhs.Mo * Ja;
        res.YackBun();
        return res;
    }
    Bunsu operator*(const Bunsu &rhs)
    {
        Bunsu res;
        res.Mo = rhs.Mo * Mo;
        res.Ja = rhs.Ja * Ja;
        res.YackBun();
        return res;
    }
    friend ostream &operator<<(ostream &os, Bunsu bunsu);
};

typedef vector<vector<Bunsu>> matrix;

ostream &operator<<(ostream &os, __int128 bigInt)
{
    if (bigInt < 0)
    {
        cout << '-';
        bigInt = -bigInt;
    }
    if (bigInt > 9) cout << (bigInt / 10);
    cout << (int)(bigInt % 10);
    return os;
}

ostream &operator<<(ostream &os, Bunsu bunsu)
{
    if (bunsu.Mo != 1)
    {
        cout << bunsu.Ja << '/' << bunsu.Mo;
    }
    else
    {
        cout << bunsu.Ja;
    }
    return os;
}

int N, M;
matrix MT;

void PrintMT(const matrix &mt)
{
    for (const auto &row : mt)
    {
        for (const Bunsu &col : row)
        {
            cout << col << ' ';
        }
        cout << '\n';
    }
}

void RowAdd(matrix &mt, int from, int to, Bunsu &x)
{
    for (int i = 0; i < M; i++)
    {
        auto tmp = (mt[to][i] + (mt[from][i] * x));
        mt[to][i] = tmp;
    }
}

void RowMul(matrix &mt, int rowIdx, Bunsu &x)
{
    for (int i = 0; i < M; i++)
    {
        mt[rowIdx][i] = mt[rowIdx][i] * x;
    }
}

void RowSwap(matrix &mt, int a, int b)
{
    swap(mt[a], mt[b]);
}

void RREF()
{
    int unsolvedCol = 0;
    for (int i = unsolvedCol; i < N; i++)
    {
        // 행 교환
        int leading = i;
        if (MT[leading][leading].Ja == 0)
        {
            for (int row = leading + 1; row < N; row++)
            {
                if (MT[row][unsolvedCol].Ja != EPS)
                {
                    RowSwap(MT, leading, row);
                    break;
                }
            }
        }
        // lead to one
        if (MT[leading][leading].Ja != 0)
        {
            Bunsu mulAmt = MT[leading][leading];
            Bunsu mulInv = mulAmt.Invert();
            if(mulInv.Mo == 0) return;
            RowMul(MT, leading, mulInv);
            // 행 사다리 꼴 + Reduce 하기
            for (int row = 0; row < N; row++)
            {
                if (leading == row)
                {
                    continue;
                }
                if (MT[row][unsolvedCol].Ja == 0)
                {
                    continue;
                }
                Bunsu reducer = MT[row][unsolvedCol];
                reducer.Ja *= -1;
                RowAdd(MT, leading, row, reducer);
            }
            unsolvedCol++;
            if (unsolvedCol >= N)
            {
                break;
            }
        }
    }
}

void HandleInput(istream &ins)
{
    while (!ins.eof())
    {
        ins >> N >> M;
        if (ins.fail())
        {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
        MT = matrix(N, vector<Bunsu>(M));

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                string strTmp;
                ins >> strTmp;
                // cout << i << ", "<< j << " : " << strTmp << '\n';
                MT[i][j] = Bunsu(strTmp);
            }
        }
        RREF();
        PrintMT(MT);
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
        FASTIO;
        HandleInput(cin);
    }
    else
    {
        const char *FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}