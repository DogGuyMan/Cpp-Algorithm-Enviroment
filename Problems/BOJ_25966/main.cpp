#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>
using namespace std;

typedef vector<vector<int>> Mat;
Mat mat(10101, vector<int>(10101));
int N, M ,Q;

ostream & operator<<(ostream& os, const Mat& matRef){
	for(int i = 0 ; i< N;i++){
		for(int j  = 0; j < M; j++){
			os << matRef[i][j] << ' ';
		}
		os << '\n';
	}
	return os;
}

void opOne(int (&query)[4]){ mat[query[1]][query[2]] = query[3]; }
void opTwo(int (&query)[4]){ swap(mat[query[1]], mat[query[2]]); }

void HandleInput(istream& ins) {
	ins >> N >> M >> Q;

    for(int r =0; r < N; r++){
        for(int c =0; c < M; c++){
            ins >> mat[r][c];
        }
    }
    
	while(Q--){
        int qIn[4] = {0,};
        ins >> qIn[0];
        qIn[0] == 0 ? 
        ins >> qIn[1] >> qIn[2] >> qIn[3] :
            ins >> qIn[1] >> qIn[2];
			
		if(qIn[0] == 0)
			opOne(qIn);
		else if(qIn[0] == 1)
			opTwo(qIn);
	}
	
    cout << mat << '\n';
}

void HandleQuery(const char* FILE_NAME) {
    fstream fs(FILE_NAME);
    if(fs.is_open()) HandleInput(fs);
}

int main(int argc, const char* args[]){
    if(argc <= 1) {
        ios::sync_with_stdio(0); cin.tie(0);
        HandleInput(cin);
    }
    else {
        HandleQuery(args[1]);
    }
}
