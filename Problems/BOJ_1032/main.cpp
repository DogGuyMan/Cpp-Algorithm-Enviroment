#include <bits/stdc++.h>
using namespace std;

int N;
char ans[55] = {0,};
char strs[55] = {0,};
int main(int argc, const char* argv[]) {
	if(argc > 1) {
		fstream fs(argv[1]);
		fs >> N;
	}
	else {
		cin >> N;
	}
	cin >> strs[0];
	if(N == 1) {
		cout << strs[0] << '\n';
		return 0;
	}
	strcpy(ans, strs);
	size_t strLen = strlen(ans);
	for(int i = 1; i < N; i++) {
		cin >> strs;
		for(int j = 0; j < strLen; j++) {
			if(strs[j] != ans[j])
				ans[j] = '?';
		}
	}

	cout << ans << '\n';
}