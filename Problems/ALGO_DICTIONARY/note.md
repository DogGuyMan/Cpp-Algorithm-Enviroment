> ### 📄 첫 흐름

소문자 알파벳 
1. 알파벳의 정렬 순서가 다른 방식 -> 단어 정렬에 기준이 있는건지
2. 아니면 abcd가 아닌 qwert인지

#### 가정 아니면 abcd가 아닌 qwert임

사전순으로 배치됨.

예를 들어 다섯 개의 단어 gg, kia, lotte, lg, hanhwa 가 사전에 순서대로 적혀 있다고 합시다.

1. gg가 kia보다 앞에 오려면 이 언어에서는 g가 k보다 앞에 와야 합니다.
2. 같은 원리로 k는 l앞에, l은 h앞에 와야 한다는 것을 알 수 있지요.
3. lotte 가 lg 보다 앞에 오려면 o가 g 보다 앞에 와야 한다는 것도 알 수 있습니다.
4. 이들을 종합하면 다섯 개의 알파벳 o, g, k, l, h 의 상대적 순서를 알게 됩니다.

알파벳의 순서를 계산하는 프로그램을 작성하세요.

Q가 주어지고 Q마다 검증
들어오는 알파벳은 정렬된 순서다.
```
int C;
int N; 
int BUFFMAX = 20;

순서에 모순이 있다면 INVAILD
없다면 소문자 알파벳의 순서 적기.
```

위상정렬을 써야 되겠고, DFS를 사용해야 겠다
```
정점은 근데 뭐지?
	if 정점은 문자열 자체
		간선은 또 뭐고?
		
	els 정점은 캐릭터 하나 하나
		간선은 또 뭐고?
	
```

---

> ### 📄 의문점

#### 1. 그래프 모델링을 단어로 해야하나, 캐릭터로 해야 하나
   * 나름의 결론은 앞서브스트링과, 뒤서브스트링으로 그래프 모델링을 해야한다는것

```cpp
int Matching(str& a, str& b) {
	int mxLen = max(a.size(), b.size());
	int res = 0;
	for(int i = 0;i < mxLen; i++) {
		if(a[i] == b[i]) {
			res++;
			continue;
		}
		break;
	}
	return res;
}
```


#### 2. DAG를 만족해야 하고 DFS를 해야 한다는것, 그리고 Path BackTracking을 해야 하는것 까지는 알겠는데.
   * backtracking이 결과가 되도록 해야 하는것을 어떻게 가능케 하는지 삽입 순서를 모르겠다.


#### 3. 위상 정렬의 결과가 나왔으면

```cpp
vector<char> dicorderedV;
unordered_set<char> dicordered;
for(auto& e : dicorderedV) {
	cout << e;
}
for(int c = 'a'; c <= 'z'; c++) {
	if(dicordered.find(c) != dicordered.end()) continue;
	cout << c;
}
```

---

> ### 📄 해법

1. 캐릭터를 정점으로 표현한다.

```
g->k
k->l
l->h
o->g
```

> ### 📄 회고

1. 간단하게 일치하는 서브스트링 탐색은 $O(N)$ 
```cpp
for(int k = 0; k < len; k++) {
        if(strs[i][k] == strs[j][k]) continue;
	// predicate
        break;
}
```

2. `memset` 하지말고 걍 `fill` 쓰자.

3. 위상 정렬의 순서
   ```
   1. DFSALL 하고, 단 이미 방문한 정점은 다시 사용하지 않는다.
   2. DFS 종료시 백트래킹순회에 필요한 값 넣기
   3. DAG인 그래프의 모든 정점을 탐색했다면 백트래킹 수행
   4. 사이클이 생기는지 확인
	즉 양방향 edge가 생기는지 확인해야 하고.
	그것을 확인하는 방법은 
	백트래킹 했던 내용중 역행할 수 있는 간선이 존재하는지 판단하면 된다.
	즉 BACK_TRACK[j] -> BACK_TRACK[i] == 1 하는 정점이 있는지 판단 말이다.
   ```

4. 벡터에서 특정 원소 찾기
   1. 비정렬 `find(RES.begin(), RES.end(), i) == RES.end()` : 마지막 이터레이터
   2. 정렬 `binary_search(RES.begin(), RES.end(), i) == true` : 참 거짓