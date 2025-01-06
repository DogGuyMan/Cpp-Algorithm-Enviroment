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
class Bunsu {
public :
    const string delimiter = "/";
    int Mo = 0;
    int Ja = 0;
    Bunsu() : Mo(0), Ja(0) {}
    Bunsu(int ja, int mo) : Mo(mo), Ja(ja) {}
    Bunsu(string bunsu) {
        if(bunsu.find(delimiter) == string::npos) {
            Ja = atoi(bunsu.c_str());
            Mo = 1;
            return;
        }
        string num[2];
        int idx = 0;
        num[0] = bunsu.substr(0, bunsu.find(delimiter));
        num[1] = bunsu.substr(bunsu.find(delimiter)+1, string::npos);
        // cout << num[0] << ", " << num[1] << '\n';
        Ja = atoi(num[0].c_str());
        Mo = atoi(num[1].c_str());
    }
    static Bunsu One()  {Bunsu tmp(1, 1); return tmp;}
    static Bunsu Zero() {Bunsu tmp(0, 1); return tmp;}


    ll GCD(ll a, ll b) { return (((b) == 0) ? ((a)) : GCD((b), ((a) % (b))));}
    ll LCM(ll a, ll b) { return ( (a) * (b) * GCD((a), (b)) );}
    void YackBun() {
        cout << " prev : "<< ToString() << '\n';
        ll gcd = GCD(Ja, Mo);
        cout << " gcd : " << gcd << '\n';
        Mo /= gcd;
        Ja /= gcd;
        if(Mo < 0) {Mo = -Mo; Ja = -Ja;}
        cout << " after : "<< ToString() << '\n';
    }
    
    Bunsu& operator=(const Bunsu& rhs) {
        Ja = rhs.Ja;
        Mo = rhs.Mo;
        return *this;
    }
    Bunsu& operator+(const Bunsu& rhs) {
        int prvMo = Mo, prvJa = Ja;
        Mo = rhs.Mo * prvMo;
        Ja = (rhs.Ja * prvMo) + (prvJa * rhs.Mo);
        YackBun();
        return *this;
    }
    Bunsu& operator-(const Bunsu& rhs) {
        int prvMo = Mo, prvJa = Ja;
        Mo = rhs.Mo * prvMo;
        Ja = (prvJa * rhs.Mo) - (rhs.Ja * prvMo);
        YackBun();
        return *this;
    }
    Bunsu& operator/(const Bunsu& rhs) {
        Mo = rhs.Ja * Mo;
        Ja = rhs.Mo * Ja;
        YackBun();
        return *this;
    }
    Bunsu& operator*(const Bunsu& rhs) {
        Mo = rhs.Mo * Mo;
        Ja = rhs.Ja * Ja;
        YackBun();
        return *this;
    }
    Bunsu& operator/(const ld& rhs) {
        Mo = rhs * Mo;
        YackBun();
        return *this;
    }
    Bunsu& operator*(const ld& rhs) {
        Ja = rhs * Ja;
        YackBun();
        return *this;
    }
    ld ToLD() const {if(fabs(Mo) < EPS) {return ((ld)(1 << 31));} return (ld)((ld)Ja / (ld)Mo);}
    string ToString() const {
        string res ="";
        if(Mo == 1) return to_string(Ja);
        res += to_string(Ja);
        res += "/";
        res += to_string(Mo);
        return res;
    }
};

void HandleInput(istream& ins) {
    while(!ins.eof()) {
        int op; ins >> op;
        if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
        string lhs, rhs;
        switch (op)
        {
        case 1 : {
            ins >> lhs >> rhs;
            auto l = Bunsu(lhs);
            auto r = Bunsu(rhs);
            auto newBunsu = l + r;
            cout    << " newBunsu : " << newBunsu.ToString() << '\n'
                    << " newBunsu real num : " << newBunsu.ToLD() << '\n';
            break;
        }
        case 2 : {
            ins >> lhs >> rhs;
            auto l = Bunsu(lhs);
            auto r = Bunsu(rhs);
            auto newBunsu = l - r;
            cout    << " newBunsu : " << newBunsu.ToString() << '\n'
                    << " newBunsu real num : " << newBunsu.ToLD() << '\n';
            break;
        }
        case 3 : {
            ins >> lhs >> rhs;
            auto l = Bunsu(lhs);
            auto r = Bunsu(rhs);
            auto newBunsu = l * r;
            cout    << " newBunsu : " << newBunsu.ToString() << '\n'
                    << " newBunsu real num : " << newBunsu.ToLD() << '\n';
            break;
        }
        case 4 : {
            ins >> lhs >> rhs;
            auto l = Bunsu(lhs);
            auto r = Bunsu(rhs);
            auto newBunsu = l / r;
            cout    << " newBunsu : " << newBunsu.ToString() << '\n'
                    << " newBunsu real num : " << newBunsu.ToLD() << '\n';
            break;

        }
        default: { cout << "FINISHED" << '\n'; return; }
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