#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int MAX_BUCKET = 1e3+9;
const int BUFF_CNT = 20 + 1;
const int MAGIC_PRIME = 31;
int N;
struct HTVALUE
{
	char key[BUFF_CNT] = {0,};
	int cnt = 0;
	bool isUsed = false;
};
HTVALUE BUCKET[MAX_BUCKET + 1] = {{{0,},0},};
vector<char *> SORTED_STR_ELEMENTS;

unsigned int HashFunc(char *const str)
{
	unsigned int hCode = 0;
	char *charHead = str;
	while (*charHead)
	{
		hCode = (((hCode * MAGIC_PRIME) % MAX_BUCKET) + *charHead++) % MAX_BUCKET;
	}
	return hCode % MAX_BUCKET;
}

unsigned int FindUnused(unsigned int hash_code, const char* str) {
	if(BUCKET[hash_code].isUsed) {
		unsigned int step = 1;
		while(BUCKET[hash_code].isUsed && strcmp(BUCKET[hash_code].key, str) != 0) {
			hash_code = (hash_code + ((step * step) % MAX_BUCKET)) % MAX_BUCKET;
		}
	}
	return hash_code;
}

void HandleInput(istream &ins)
{
	ins >> N;
	char buff[BUFF_CNT] = {
	    0,
	};
	int mx = 0;
	for (int i = 0; i < N; i++)
	{
		ins >> buff;
		unsigned int hashKey = FindUnused(HashFunc(buff), buff);
		BUCKET[hashKey].isUsed = true;
		strcpy(BUCKET[hashKey].key, buff);
		mx = max(mx, ++BUCKET[hashKey].cnt);
	}
	for (int i = 0; i < MAX_BUCKET; i++)
	{
		if(BUCKET[i].cnt == mx) {
			SORTED_STR_ELEMENTS.push_back(BUCKET[i].key);
		}
	}
	SORTED_STR_ELEMENTS.reserve(1010);
	sort(SORTED_STR_ELEMENTS.begin(), SORTED_STR_ELEMENTS.end(), 
		[] (const char* lhs, const char* rhs) {
			return strcmp(lhs, rhs) < 0;
		}
	);

	for(const auto& str : SORTED_STR_ELEMENTS) {
		cout << str << '\n';
	}
}

void HandleQuery(const char *FILE_PATH)
{
	fstream fs(FILE_PATH);
	if (fs.is_open())
	{
		HandleInput(fs);
	}
}

int main(int argc, const char *args[])
{
	if (argc <= 1)
	{
		FASTIO;
		HandleInput(cin);
	}
	else
	{
		HandleQuery(args[1]);
	}
}