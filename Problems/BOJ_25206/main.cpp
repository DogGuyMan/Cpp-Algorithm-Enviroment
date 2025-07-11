#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <limits>
using namespace std;

struct GRADE {
	double w;
	double s;
};

vector<GRADE> gv;

double AConv(const char* cstr){
	double res = 0.0f;
	if(strlen(cstr) <= 1) return res;
	switch(*(cstr + 0))
	{
		case 'A' : { res += 4.0; break;}
		case 'B' : { res += 3.0; break;}
		case 'C' : { res += 2.0; break;}
		case 'D' : { res += 1.0; break;}
		default: break;
	}
	switch(*(cstr + 1))
	{
		case '+' : { res += 0.5; break;}
		default:break;
	}
	return res;
}



int main(){
	string name;
	double w;
	string al;
	while(true){
		cin >> name >> w >> al;
		if(cin.eof()) break;
		if(cin.fail()){
			cin.clear();
			cin.ignore((1<<31), '\n');
			continue;
		}
		if(al == "P") continue;
		gv.push_back({w, AConv(al.c_str())});
		
	}
	
	cin.clear();

		double ans = 0.0;
		double wsum = 0.0;
		for(const auto& e : gv){
			ans += (e.w * e.s);
			wsum += e.w;
		}
		cout << fixed;
		cout.precision(6);
		cout << (ans / wsum) << '\n';
}
