#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> strs(1010);
int CNT = 0;

int recursion(const char *s, int l, int r){
	CNT++;
    	if(l >= r) {return 1;}
    	else if(s[l] != s[r]) {return 0;}
    	else return recursion(s, l+1, r-1);
}

int isPalindrome(const char *s){
    	return recursion(s, 0, strlen(s)-1);
}


int main(int argc, const char* argv[]){
	if(argc > 1) {
		fstream fs(argv[1]);
		fs >> N; 
		for(int i = 0; i < N; i++)
			fs >> strs[i];
	}
	else {
		cin >> N; 
		for(int i = 0; i < N; i++)
			cin >> strs[i];
	}
	for(int i = 0; i < N; i++) {
		CNT = 0;
		const char * cstr = strs[i].c_str();
		cout << isPalindrome(cstr) << " " << CNT << '\n';
	}
}
