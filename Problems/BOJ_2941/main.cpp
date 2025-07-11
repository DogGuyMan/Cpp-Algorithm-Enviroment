#include <bits/stdc++.h>

using namespace std;

unordered_set<string> croAlphas {"c=","c-","dz=","d-","lj","nj","s=","z="};

int ANS = 0;
void InputHandle(istream& ins) {

	string str; ins >> str;
	if(str.size() <= 0) {return;}
	for(int i = 0; i < str.size(); i++) {
		bool isFinded = false;
		string subStr;
		for(const auto& croAlpha : croAlphas) {
			int croAlphaSize = croAlpha.size();
			subStr = str.substr(i, croAlphaSize);
			if(subStr == croAlpha) {
				isFinded = true;
				i+=(croAlphaSize-1);
				break;
			}
		}
		ANS++;
	}
}

int main(int argc, const char* argv[]) {
	if(argc > 1) {
		fstream fs(argv[1]);
		InputHandle(fs);
	}
	else 
		InputHandle(cin);
	cout << ANS << '\n';
	return 0;
}