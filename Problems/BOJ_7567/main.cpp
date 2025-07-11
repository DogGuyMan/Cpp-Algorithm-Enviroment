#include <bits/stdc++.h>
using namespace std;

int ANS = 0;

int main(int argc, const char * argv[]) {
	char bowl[55] = {0,};
	if(argc > 1) {
		fstream fs(argv[1]);
		fs >> bowl;
	}
	else {
		cin >> bowl;
	}
	const int strLen = strlen(bowl);
	if(strLen == 0) {cout << 0 << '\n'; return 0;}
	ANS+=10;
	bool isChanged = false;
	for(int i = 1; i < strLen; i++) {
		if(bowl[i-1] != bowl[i]) isChanged = true;
		if(isChanged){
			ANS+=5;
			isChanged = false;
		}
		ANS+=5;
	}
	cout << ANS << '\n';
	return 0;
}