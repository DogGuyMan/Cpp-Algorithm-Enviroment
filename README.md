<div align=center>
<a href="https://solved.ac/felipuss/"><img src="http://mazassumnida.wtf/api/v2/generate_badge?boj=felipuss" alt="Solved.ac&#xD504;&#xB85C;&#xD544;"></a>
</div>

---

> ### 📄 Shell 커맨드

#### 1). 템플릿 환경

```
전처리문, 인클루드, 매크로 등등 PS에서 유용한 흑마법을 일일히 치는것은
시간상 너무 낭비되는데, 이를 자동화 함으로 문제 풀이 환경을 만들어 보자.
```

##### ① 커맨드
```bash
# ALGO : 알고 스팟, SWEA : 삼성 아카데미, BOJ : 백준
sh ./Shell/Env_Generate.sh \
    <문제풀이 사이트 [ALGO, SWEA, BOJ]> \
    <문제 식별자 [알고스팟문제키, 백준번호]>
```

##### ② 템플릿 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO                       \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);
#define FOR(i, a, b) for( int i = (a); i < (b); ++i)
#define Y first
#define X second
#define ALL(v) (v).begin(), (v).end()
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

void HandleInput(istream &ins)
{
    string str;
    ins >> str;
    cout << "Hello " << str << '\n';
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
```


#### 2). 인풋 자동화

```
컴파일 하고, 일일이 수작업으로 인풋을 넣는것은 진짜 귀찮다..
아니 그냥 코드 테스팅에 있어서 시간이 낭비된다.

따라서 파일스트림과, 텍스트를 인풋으로 파이프 하여, 인풋을 자동화 해볼 수 있다.
```

##### ① 문제별 커맨드

```shell
sh ./Shell/ALGO_Execute.sh < 알고스팟_문제_키 > < { option 1 이면 ${ProbNum}/InputQuerys/*.txt 모두 순회} >
sh ./Shell/SWEA_Execute.sh < 삼성_문제_번호 > < { option 1 이면 ${ProbNum}/InputQuerys/*.txt 모두 순회} >
sh ./Shell/BOJ_Execute.sh < 백준_문제_번호 > < { option 1 이면 ${ProbNum}/InputQuerys/*.txt 모두 순회} >
```


##### ② 인풋의 사이즈가 정해지지 않을때,

```cpp
while(!ins.eof()) {
    ins >> N >> M;
    if(ins.fail()) {ins.clear(); ins.ignore('\n'); continue;}
    T.reserve(N+1); T.resize(N);
}
```

#### 3). 문제를 읽자.
* 입력 출력을 먼저 보고
* 예제 입력을 보고 고민해 보자.
* 그리고 문제를 읽자.

---

> ### 📄 Vscode 세팅

```
// 오히려 꺼야 한다.
// "cmake.debugConfig": {
//     "cwd": "${workspaceFolder}"
// },
```

---

> ### 📄 도움 받은 문제라 다시 풀어야 하는 문제는 `X` 표시 하자.

`BOJ_X_OOOOO` 뭐.. 이런식으로