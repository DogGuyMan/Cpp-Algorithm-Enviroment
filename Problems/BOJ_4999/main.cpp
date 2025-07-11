#include <bits/stdc++.h>
using namespace std;

char ME[1010] = {0,};
char DOC[1010] = {0,};

int main(int argc, const char* argv[]) {
	if(argc > 1) {
		fstream fs(argv[1]);
		fs >> ME >> DOC;
	}
	else {
		cin >> ME >> DOC;
	}

	if(strlen(ME) >= strlen(DOC))
		cout << "go" << '\n';
	else 
		cout << "no" << '\n';
	return 0;
}