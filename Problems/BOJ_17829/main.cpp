#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define DEBUG 0
#define X first
#define Y second
using namespace std;
typedef pair<int, int> pii;
typedef vector<vector<int>> matrix;

int N;
matrix mt(1025, vector<int>(1025));

int GetSecond(pii pos){
	int seq[4] = {
		mt[pos.X][pos.Y], mt[pos.X	+1][pos.Y],
		mt[pos.X][pos.Y+1], mt[pos.X+1][pos.Y+1]	
	};
	sort(seq, seq + 4);
	return seq[2];
}

void PrintMt(int len)
{
	for(int i = 0;i<len;i++){
		for(int j = 0;j<len;j++){
			cout << setw(8) << mt[i][j] << ' ';
		}cout << '\n';
	}
}

void CNN(int depth, int len){
#if DEBUG
	PrintMt(len);
#endif
    if(len <= 0) {cout << mt[0][0] << '\n'; return;}
	
	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < len; j++){
			mt[i][j] = GetSecond({i<<1, j<<1});
		}
	}

	CNN(depth+1, (len>>1));
}

void HandleInput(istream& ins) {
    ins >> N;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j++){
			ins >> mt[i][j];
		}
	}
	CNN(0,N/2);
}
void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) { HandleInput(fs); }
}

int main(int argc, char* args[]){
    if(argc <= 1) {
	    FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
#if DEBUG
	const char* FILE_PATH = "./InputQuerys/input_003.txt";
	HandleQuery(FILE_PATH);
#endif
}
