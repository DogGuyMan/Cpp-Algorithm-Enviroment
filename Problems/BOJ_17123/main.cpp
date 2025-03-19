#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int Q;
int rowSum[1010] = {0,};
int colSum[1010] = {0,};

void HandleInput(istream& ins) {
    ins >> Q;
    while(Q--){
		int N, M; ins >> N >> M;
		for(int i = 0;i < N; i++){
			for(int j = 0; j < N; j++){
				int rE; ins >> rE;
				rowSum[i] += rE;
				colSum[j] += rE;
			}
		}
		for(int j = 0;j < M;j++){
            int r1, r2, c1, c2, v;
			ins >> r1 >> c1 >> r2 >> c2 >> v;
			for(int w = c1; w <= c2; w++){
                colSum[w-1] += v * (r2 - r1 + 1);
            }
            for(int h = r1; h <= r2; h++){
                rowSum[h-1] += v * (c2 - r1 + 1);
            }
		}
        
        for(int i = 0;i< N;i++){ cout << rowSum[i] << ' '; }
        cout << '\n';
        for(int i = 0; i<N;i++){ cout << colSum[i] << ' '; }
        cout << '\n';
		memset(rowSum, 0, (N+1) * sizeof(int));
		memset(colSum, 0, (N+1) * sizeof(int));
	}
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}

int main(int argc, const char* args[]){
	ios::sync_with_stdio(false); cin.tie(0);
    if(argc <= 1) {
        HandleInput(cin);
    }
    else {
        HandleQuery(args[1]);
    }
}
