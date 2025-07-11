#include <bits/stdc++.h>
#include <cctype>
using namespace std;

string inputStr;
int main(int argc, const char* argv[]) {
	if(argc > 1)
	{
		fstream fs(argv[1]);
		fs >> inputStr;
	}
	else 
	{
		cin >> inputStr;
	}

	// cout << inputStr[0];
	// size_t idx = 0;
	// idx = inputStr.find('-', idx);
	// while(idx != string::npos) {
	// 	cout << inputStr[++idx];
	// 	idx = inputStr.find('-', idx);
	// }
	cout << inputStr[0];
	for(int i = 1; i < inputStr.size(); i++) {
		if(inputStr[i-1] == '-') 
			cout << inputStr[i];
	}
	cout << '\n';
	return 0;
}

