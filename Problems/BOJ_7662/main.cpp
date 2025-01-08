#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
typedef long long ll;
const ll INF = (1L<<33);
int T, Q;
map<int, ll> m;

void HandleInput(istream &ins)
{
    ins >> T;
    while (T--)
    {
        ins >> Q;
        for (int i = 0; i < Q; i++)
        {
            char op; ll val; ins >> op >> val;
            switch (op)
            {
                case 'I' : {
                    m[val]++;
                    break;
                }
                case 'D' : {
                    if(val < 0) { 
                        if(m.empty()) continue;
                        map<int, ll>::iterator minIter = m.begin();
                        if(m[minIter->first] > 1) {m[minIter->first]--;}
                        else {m.erase(minIter->first);}
                    }
                    else { 
                        if(m.empty()) continue;
                        map<int, ll>::iterator maxIter = --m.end();
                        if(m[maxIter->first] > 1) {m[maxIter->first]--;}
                        else {m.erase(maxIter->first);}
                    }
                    break;
                }
            }
            // cout << " op : " << op << " val : " << val << '\n';
            // cout << "   current   " << '\n';
            // for(auto& e : m) {
            //     cout << "           key : " << e.first << " value : " << e.second << '\n';
            // }
        }
        if(m.empty() == true)
            cout << "EMPTY" << '\n';
        else {cout << (--m.end())->first << " " << m.begin()->first << '\n';}
        m.clear();
    }
}

void HandleQuery(char *FILE_PATH)
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
        char *FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}