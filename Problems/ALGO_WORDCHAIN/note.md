> ### 📄 문제.

#### 문제
참가자 (정점) 원을 그리고 있음
Degree가 2임

시계 방향.

사용할 수 있는 단어의 종류가 미리 정해져 있음,
한단어를 두번 사용할 수는 없음.

만약 끝날 수 있는지 없는지를 판단하고, 만약 가능하면 어떤 단어로 해야 하는지 말해라.

#### 입력
```cpp
int C; // 1 ~ 50
int N; // 1~100 edge 수
const int ALPHA_CNT = 'z'-'a'+1;
const int BUFF_MAX = 10;
const char* FAIL_STR = "IMPOSSIBLE";
```

#### 생각
```
G['알파벳'].size();
그니깐 '알파벳'으로 시작하는 단어를 모아 넣는다.
```

```
dragon->need
god->dragon
dog->god
ab->bb
aa->ab
aa->aa
dragon->need
god->dragon
dog->god
```

#### 생각2

오일러 트레일을 찾는것이다.
서킷이든 상관 없다.

서킷이 되는가 안되는가 먼저 검증.
한 컴포넌트에 있는가 없는가.

#### 회고

##### 1. 오일러 서킷, 트레일 모두! 백트래킹시 리버스는 필수!
```cpp
reverse(BACK_TRACK.begin(), BACK_TRACK.end());
```

##### 2. 백트래킹 된 결과물을 from -> to로 써야 했다

```cpp
for(int i = 0; i < BACK_TRACK.size()-1; i++) {
	// ❌ int from = i;
	int from = BACK_TRACK[i];
	// ❌ int to = i + 1;
	int to = BACK_TRACK[i+1];
	// cout << from << "->" << to << '\n'; // DEBUG 
	string poped = G[from][to].back();
	cout << poped << ' ';
	G[from][to].pop_back();
} cout << '\n';
```

##### 3. `ADJ[from][to]` 배열이 필요한 이유

```cpp
void DFS(int cur) {
	for(int nxt = 0;nxt < ALPHA_CNT; nxt++) {
		// cur -> nxt로 갈때, 경로의 카운트를 세야 할 수 있어야 하는데
		// out_deg 만으로 는 할 수 없다 ADJ가 꼭 필요한 이유다.
		// while(OUT_DEG[i] > 0) 
		while (ADJ[cur][nxt] > 0)
		{
			ADJ[cur][nxt]--;
			DFS(nxt);
		}
		
	}
	// cout << (char)(cur+'a') << '\n'; // DEBUG
	BACK_TRACK.push_back(cur);
}
```