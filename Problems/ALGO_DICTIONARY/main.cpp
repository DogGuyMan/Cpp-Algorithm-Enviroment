#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 

using namespace std;

int C;
int N;

const int ALPHA_CNT = 'z' - 'a' + 1;
const char* FAIL_STR = "INVALID HYPOTHESIS";

int G[ALPHA_CNT][ALPHA_CNT] = {0,};
bool IS_VISIT[ALPHA_CNT] = {0,};
vector<int> BACK_TRACK;

void ResetState() {
	for(int i = 0; i < ALPHA_CNT; i++)
		for(int j = 0; j < ALPHA_CNT; j++)
			G[i][j] = 0;
	BACK_TRACK.clear();
	for(int i = 0; i < ALPHA_CNT; i++)
		IS_VISIT[i] = false;
}

void DFS(int cur) {
	IS_VISIT[cur] = true;
	for(int nxt = 0; nxt < ALPHA_CNT; nxt++) {
		if(G[cur][nxt] == 0) continue;;
		if(IS_VISIT[nxt]) continue;
		DFS(nxt);
	}
	BACK_TRACK.push_back(cur);
}

string TopoSort() {
	string res = "";
	// DAG 검사

	for(int i = 0; i < ALPHA_CNT; i++) {
		if(!IS_VISIT[i])
			DFS(i);
	}

	reverse(BACK_TRACK.begin(), BACK_TRACK.end());
	
	// DAG 검사
	for(int i = 0; i < ALPHA_CNT; i++) {
		for(int j = i+1; j < ALPHA_CNT; j++) {
			if(G[BACK_TRACK[j]][BACK_TRACK[i]] == 1)
				return res = FAIL_STR;
		}
	}

	for(auto& e : BACK_TRACK) {
		res += (char)(e + 'a');
	} 
	return res;
}

void HandleInput(istream &ins)
{
	ins >> C;
	while (C--)
	{
		ins >> N;
		ResetState();
		vector<string> strs(N);
		for (int i = 0; i < N; i++)
		{
			ins >> strs[i];
		}

		for(int j = 1; j < strs.size(); j++) {
			int i = j -1;
			int from = 0; int to = 0;
			string& fstr = strs[i]; 
			string& sstr = strs[j];
			int minLen = min(fstr.size(), sstr.size());
			for(int l = 0; l < minLen; l++) {
				if(fstr[l] == sstr[l]) continue;
				from = fstr[l] - 'a'; to = sstr[l] - 'a';
				break;
			}
			G[from][to] = 1;
		}
		cout << TopoSort() << '\n';
	}
}

void HandleQuery(const char *filePath)
{
	fstream fs(filePath);
	if (fs.is_open())
	{
		HandleInput(fs);
	}
}

int main(int argc, const char *argv[])
{
	if (argc <= 1)
	{
		HandleInput(cin);
	}
	else
	{
		HandleQuery(argv[1]);
	}
}
