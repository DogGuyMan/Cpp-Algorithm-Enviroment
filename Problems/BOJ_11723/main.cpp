#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
using namespace std;

bitset<21> SET(0);
int N;

void add(int x){ SET[x] = 1; }
void remove(int x){ SET[x] = 0;	}
void check(int x){ cout << (SET[x] ? 1 : 0) << '\n'; }
void toggle(int x){ SET.flip(x); }
void all(){ SET.set(); }
void empty(){SET.reset();}

void HandleInput(istream& ins) {
	ins >> N; string op; int x; 
	for(int i = 0; i < N; i++){
		ins >> op;
		if      (op[0] == 'a' && op[1] == 'd')       {ins >> x; add(x); }
		else if (op[0] == 'r')  {ins >> x; remove(x); }
		else if (op[0] == 'c') 	{ins >> x; check(x); }
		else if (op[0] == 't')  {ins >> x; toggle(x); }
		else if (op[0] == 'a') 	{all();}
		else if (op[0] == 'e') 	{empty(); }
	}
}
void HandleQuery(char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {HandleInput(fs);}
}

int main(int argc, char* args[])
{
    if(argc <= 1) {FASTIO; HandleInput(cin);}
    else {char* FILE_PATH = args[1]; HandleQuery(FILE_PATH);}
}
