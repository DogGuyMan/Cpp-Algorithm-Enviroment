#include <bits/stdc++.h>
using namespace std;

int N;
string XSTR;
string YSTR;

int MatchCount(string& lhs, string& rhs, int s) {
	int res = 0;
	assert(s + lhs.size() <= rhs.size());
	for(int i = 0; i < lhs.size(); i++) {
		if(rhs[i+s] == lhs[i]){
			// cout << " rhs[i+s] : "<<  rhs[i+s] << " lhs[i] : " << lhs[i] << '\n';
			res++;
		}
	}
	return res;
}


// 시작점 array[MostMatchIndex] 
pair<int, int> MostMatchIndex(string& lhs, string& rhs) {
	int most_cnt = 0;
	int res = 0;
	int index = 0;
	while(index + lhs.size() <= rhs.size()) {
		int temp_cnt = MatchCount(lhs, rhs, index);
		// cout << "temp_cnt : " << temp_cnt << " at index : " << index << '\n';
		if(temp_cnt > most_cnt) {
			most_cnt = temp_cnt;
			res = index;
		}
		index++;
	}
	// cout << most_cnt << " " << res <<'\n';
	return {most_cnt, res};
}

int main(int argc, const char* argv[]) {
	if(argc > 1) {
		fstream fs(argv[1]);
		fs >> XSTR >> YSTR;
		N = YSTR.size();
	}
	else {
		cin >> XSTR >> YSTR;
		N = YSTR.size();
	}
	pair<int, int> matchCnt = MostMatchIndex(XSTR, YSTR);
	cout << XSTR.size() - matchCnt.first << '\n';
}