#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)

int tierWeight[255];
const int baseWeight = 1e6;

struct Tier {
	char symbol = 0;
	int num = 0;
};

Tier tierArr[1010] = {0,};
Tier sortedTierArr[1010] = {0,};

ostream& operator<<(ostream& os, Tier a) {
	os << a.symbol << a.num;
	return os;
}

int TierToInt(Tier& t){ return tierWeight[t.symbol] + (10000 - t.num);}

bool Comp(Tier& a, Tier& b){
	int aval = TierToInt(a);
	int bval = TierToInt(b);
	
	return aval <= bval;
}

void HandleInput(istream& ins) {
	tierWeight['B'] = baseWeight * 1;
	tierWeight['S'] = baseWeight * 2;
	tierWeight['G'] = baseWeight * 3;
	tierWeight['P'] = baseWeight * 4;
	tierWeight['D'] = baseWeight * 5;
	
	int N; ins >>N;
	for(int i = 0; i < N; i++){
		char inputSymbol; int inputNum;
		ins >> inputSymbol >> inputNum;
		tierArr[i].symbol = inputSymbol;
		tierArr[i].num = inputNum;
		sortedTierArr[i].symbol = inputSymbol;
		sortedTierArr[i].num = inputNum;
	}
	sort(sortedTierArr + 0, sortedTierArr + N, Comp);
	vector<Tier> worngOrderTier;
	for(int i = 0; i < N; i++){
		if(TierToInt(sortedTierArr[i]) != TierToInt(tierArr[i])) 
			worngOrderTier.push_back(tierArr[i]);
	}
	if(worngOrderTier.size() > 0){
		cout << "KO" << '\n';
		if(TierToInt(worngOrderTier[0]) > TierToInt(worngOrderTier[1]))
			cout << worngOrderTier[1] << ' ' << worngOrderTier[0] << '\n';
		else
			cout << worngOrderTier[0] << ' ' << worngOrderTier[1] << '\n';
		return;
	}
	else {
		cout << "OK" << '\n';
	}
}

void HandleQuery(const char* FILE_PATH) {
	fstream fs(FILE_PATH);
	if(fs.is_open()) {
		HandleInput(fs);
	}
}

int main(int argc, const char* args[]){
	if(argc <= 1) {
		FASTIO;
		HandleInput(cin);
	}
	else {
		HandleQuery(args[1]);
	}
}
