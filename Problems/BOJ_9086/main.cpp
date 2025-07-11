#include <bits/stdc++.h>
using namespace std;

int N;
string strs[1010];
int main() {
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> strs[i];
		cout << *(strs[i].begin()) << *(--strs[i].end()) << '\n';
	}
	return 0;
}