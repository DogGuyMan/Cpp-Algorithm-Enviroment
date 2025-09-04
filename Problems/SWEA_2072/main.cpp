#include <iostream>
// #include <fstream>

using namespace std;
#define FASTIO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int T;
const int BUFF_CNT = 10;

void HandleInput(istream& ins) {
	ins >> T;
	for(int t = 1; t <= T; t++) {
		int inputs[BUFF_CNT];
		int sum = 0;
		for(int i = 0; i < BUFF_CNT; i++) {
			ins >> inputs[i];
			if(((inputs[i] - 1) % 2 ) == 0)
				sum += inputs[i];
		}
		cout << "#" << t << ' ' << sum << '\n';
	}
}

// void HandleQuery(const char* FILE_PATH) {
//     fstream fs(FILE_PATH);
//     if(fs.is_open()) {
//         HandleInput(fs);
//     }
// }

int main(int argc, const char* args[]) {
//     if(argc <= 1) {
//         FASTIO;
        HandleInput(cin);
//     }
//     else {
//         HandleQuery(args[1]);
//     }
}
