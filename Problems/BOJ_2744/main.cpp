#include <bits/stdc++.h>
using namespace std;

int main() {
	string str; cin >> str;
	int utol = 'a' - 'A';
	int ltou = 'A' - 'a';
	for(auto& c : str) {
		if('A' <= c && c <= 'Z') {
			c += utol;
		}
		else if('a' <= c && c <= 'z') {
			c += ltou;
		}
	}
	cout << str << '\n';
}