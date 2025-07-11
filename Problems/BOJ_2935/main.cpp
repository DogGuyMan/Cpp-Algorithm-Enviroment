#include <bits/stdc++.h>
using namespace std;

void TENMUL(string& lhs, string& rhs) {
	string res = "1";
	for(int i = 1; i <= (lhs.size() + rhs.size() - 2); i++) {
		res.push_back('0');
	}
	cout << res << '\n';
}

void TENADD(string& lhs, string& rhs) {
    if(lhs.size() > rhs.size()) {
        swap(lhs, rhs);
    }
    
    int pos = rhs.size() - lhs.size();
    
    if(rhs[pos] == '1') {
        rhs[pos] = '2';
    }
    else {
        rhs[pos] = '1';
    }
    
    cout << rhs << '\n';
}

int main(int argc, const char* argv[]) {
	string lhs, rhs; char op;
	if(argc > 1) {
		fstream fs(argv[1]);
		fs >> lhs >> op >> rhs;
	}
	else {
		cin >> lhs >> op >> rhs;
	}
	(op == '+') ?  TENADD(lhs, rhs): TENMUL(lhs, rhs);
	return 0;
}