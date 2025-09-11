### 첫 시도는 
#### 1. input->을 해시화 시키는것. "자릿수 해시화"
```cpp
int GetSubHash(const string& sub) {
	if(sub == "kor") return 100;
	if(sub == "eng") return 200;
	if(sub == "math" ) return 300;
	return 0;
}

int GetFruHash(const string& fru) {
	if(fru == "apple") return 10;
	if(fru == "pear") return 20;
	if(fru == "orange"  ) return 30;
	return 0;
}

int GetColHash(const string& col) {
	if(col == "red") return 1;
	if(col == "blue") return 2;
	if(col == "green" ) return 3;
	return 0;
}

int GetHash(const string& str, int idx) {
	if(idx == 0) return GetSubHash(str);
	if(idx == 1) return GetFruHash(str);
	return GetColHash(str);
}
```
#### 2. 해시코드를 마스킹하면서 상태공간 트리 완전탐색
```cpp
void WriteCnt(string (&strs)[3], int curIdx, int curHash) {
	if(curIdx > 2) {
		CNT[curHash]++;
		return;
	}
	int hCode = GetHash(strs[curIdx], curIdx);
	if(hCode == 0) {
		for(int i = 1; i <= 3; i++) {
			int hMask = pow(10, 3-curIdx-1);
			WriteCnt(strs, curIdx+1, curHash + (hMask * i));
		}
		return;
	}
	WriteCnt(strs, curIdx+1, curHash+hCode);
}

void LoadCnt(string (&strs)[3], int curIdx, int curHash, int& ans) {
	if(curIdx > 2) {
		ans += CNT[curHash];
		return;
	}
	if(strs[curIdx] == "-") {
		for(int i = 1; i <= 3; i++) {
			int hMask = pow(10, 3-curIdx-1);
			LoadCnt(strs, curIdx+1, curHash + (hMask * i), ans);
		}
		return;
	}
	LoadCnt(strs, curIdx+1, curHash+GetHash(strs[curIdx], curIdx), ans);
}
```

문제는 코드가 너무 길어..

---

### 인풋 최적화
#### 1. 인풋 해시화 최적화
##### 1. 일단 스트링을 굳이 다 가져와야만 하는걸까?
string이 아닌 char로 식별하는것을 시도해 보자.
```cpp
char STR_IDEN[3][4] = {
    {'-', 'k', 'e', 'm'},
    {'-', 'a', 'p', 'o'},
    {'-', 'r', 'g', 'b'}
}
```
단 알맞는 인덱스를 찾아야 하므로 
```cpp
indexedIden[j] = (find(STR_IDEN[j], STR_IDEN[j] + 4, inStr[0]) - STR_IDEN[j]);
```

##### 2. 해싱은 굳이 하나의 int값이 Key가 될 필요는 없다
```cpp
// int CNT[505] ={0,} 
int CNT[4][4][4] = {0,}
```

#### 2. 굳이 완탐을 해야 할까?
사실 '-' 으로 한다면 1,2,3 각각을 카운트 하면서 0도 동시에 카운트 하면 된다.
```cpp
for (int mask = 0; mask < 8; ++mask)
{
    int x = (mask & 1) ? 0 : indexedIden[0];
    int y = (mask & 2) ? 0 : indexedIden[1];
    int z = (mask & 4) ? 0 : indexedIden[2];
    CNT[x][y][z]++;
}
```