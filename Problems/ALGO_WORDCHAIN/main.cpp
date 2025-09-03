#include <bits/stdc++.h>

using namespace std;

int C;
int N;
const int ALPHA_CNT = 'z' - 'a' + 1;
const int BUFF_CNT = 10;
const string FAIL_STR = "IMPOSSIBLE";

int ADJ[ALPHA_CNT][ALPHA_CNT] = {{0},};
vector<string> G[ALPHA_CNT][ALPHA_CNT];
int IN_DEG[ALPHA_CNT] = {0,};
int OUT_DEG[ALPHA_CNT] = {0,}; 
vector<int> BACK_TRACK;

void ResetState() {
	for(int i = 0; i < ALPHA_CNT; i++) {
		for(int j = 0; j < ALPHA_CNT; j++) {
			ADJ[i][j] = 0;
			G[i][j].clear();
		}
	}

	for(int i = 0; i < ALPHA_CNT; i++) {
		IN_DEG[i] = 0;
		OUT_DEG[i] = 0;
	}
}

bool CheckEuler() {
	int sVCandiCnt = 0; int eVCnadiCnt = 0;
	for(int i = 0; i < ALPHA_CNT; i++) {
		int degGap = OUT_DEG[i] - IN_DEG[i];
		if(degGap > 1 || degGap < -1)	return false;
		if(degGap == 1) sVCandiCnt++;
		if(degGap == -1) eVCnadiCnt++;
	}
	bool isCircuit = (sVCandiCnt == 0) && (eVCnadiCnt == 0);
	bool isTrail = (sVCandiCnt == 1) && (eVCnadiCnt == 1);
	return isCircuit || isTrail;
}

void DFS(int cur) {
	for(int nxt = 0;nxt < ALPHA_CNT; nxt++) {
		// cur -> nxt로 갈때, 경로의 카운트를 세야 할 수 있어야 하는데
		// out_deg 만으로 는 할 수 없다 ADJ가 꼭 필요한 이유다.
		// while(OUT_DEG[i] > 0) 
		while (ADJ[cur][nxt] > 0)
		{
			ADJ[cur][nxt]--;
			DFS(nxt);
		}
		
	}
	// cout << (char)(cur+'a') << '\n'; // DEBUG
	BACK_TRACK.push_back(cur);
}

void TopoSort() {
	// If Trail
	for(int i = 0; i < ALPHA_CNT; i++) {
		if(IN_DEG[i] + 1 == OUT_DEG[i]) {
			DFS(i);
			return;
		}
	}
	
	for(int i = 0; i < ALPHA_CNT; i++) {
		if(OUT_DEG[i] > 0) {
			DFS(i);
			return;
		}
	}

	return;
}

string Solve() {
	string res = "";
	if(!CheckEuler()){
		return res = FAIL_STR;
	}
	
	TopoSort();

	if(BACK_TRACK.size() < N + 1)
		return res = FAIL_STR;
	
	reverse(BACK_TRACK.begin(), BACK_TRACK.end());

	for(int j = 1; j < BACK_TRACK.size(); j++) {
		int i = j - 1;
		if(G[BACK_TRACK[i]][BACK_TRACK[j]].size() > 0) {
			string poped = G[BACK_TRACK[i]][BACK_TRACK[j]].back(); 
			G[BACK_TRACK[i]][BACK_TRACK[j]].pop_back();
			res += poped;
			res += ' ';
		}
	}
	return res;
}

void HandleInput(istream& ins) {
	ins >> C;
	while(C--) {
		ins >> N;
		ResetState();
		vector<string> inputStrs(N);
		// unordered_set<char> usedAlpha; // DEBUG
		for(int i = 0; i < N; i++) {
			ins >> inputStrs[i];
			string& curStr = inputStrs[i];
			
			// usedAlpha.insert(curStr[0]);// DEBUG
			// usedAlpha.insert(curStr.back());// DEBUG

			int from = curStr[0] - 'a';
			int to = curStr.back() - 'a';
			ADJ[from][to]++;
			G[from][to].push_back(curStr);
			IN_DEG[to]++;
			OUT_DEG[from]++;
		}

		// for(auto& e1 : usedAlpha) { // DEBUG
			// for(auto& e2 : usedAlpha) { // DEBUG
				// if(e1 != e2) { // DEBUG
					// for(auto& str : G[e1-'a'][e2-'a']) { // DEBUG
						// cout << e1 << "->" << str << "->" << e2 << '\n'; // DEBUG
					// } // DEBUG
				// } // DEBUG
			// } // DEBUG
		// } // DEBUG

		cout << Solve() << '\n';
	}
}

void HandleQuery(const char* filePath) {
	fstream fs(filePath);
	if(fs.is_open())
		HandleInput(fs);
}

int main(int argc, const char* argv[]) {
	if(argc <= 1)
		HandleInput(cin);
	else 
		HandleQuery(argv[1]);
}