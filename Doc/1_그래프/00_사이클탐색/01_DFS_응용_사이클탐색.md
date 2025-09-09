### 📄 1. 무방향 그래프 : DFS + 부모 체크**
### 📄 2. 방향 그래프 : DFS 색칠(Back Edge)

#### 색 배열 사이클 검출

즉 색 배열이란 
IS_VISIT에 방분 여부 "YES", "NO"에 더해 
"처리중"이라는 상태를 더 추가한 느낌이라 보면 된다.

```cpp
constexpr char YET = 0;
constexpr char ENTERING = 1;
constexpr char VISITED = 2;

vector<char> COLOR(N+1, YET);
```

그리고 "처리 중"에 대해 DFS를 어떻게 처리하면 되냐.
바로 `ENTERING`을 만나면 사이클이 있다는것으로 하자.
```cpp
vector<vector<int>> G;
vector<int> BACK_TRACK;
bool IS_CYCLE;
vector<char> COLOR(N+1, YET);

void DFS(int cur) 
{
	COLOR[cur] = ENTERING;

	for(auto& nxt : G[cur]) {
		if(IS_CYCLE) return;
		if(COLOR[nxt] == YET) DFS(nxt);
		else if(COLOR[nxt] == ENTERING) {
            isCycle = true; 
            return;
        }
	}
	COLOR[cur] = VISITED;
	BACK_TRACK.push_back(cur);
}
```