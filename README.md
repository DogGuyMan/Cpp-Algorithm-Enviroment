<div align=center>
<a href="https://solved.ac/felipuss/"><img src="http://mazassumnida.wtf/api/v2/generate_badge?boj=felipuss" alt="Solved.ac&#xD504;&#xB85C;&#xD544;"></a>
</div>

---

### Shell
##### 1. 손쉬운 인풋 아웃풋 처리
##### 2. N개 쿼리 체크

```shell
sh ./shell/Execute.sh < 백준_문제_번호 > < { option 1 이면 ${ProbNum}/InputQuerys/*.txt 모두 순회} >
```

#### 1). BOJ_28702 문제로 쉘 허점 발견 및 수정

로직상 전혀 틀릴게 없다 생각했는데.
이번 인풋, 아웃풋 구조의 허점을 발견하게 되었다.
바로 `EOF`를 받지 못하면 틀렸습니다를 받을 수 있다는것을 확인 따라서
`QUERY_CNT` 변수로 쿼리 루프 횟수를 넘겨 받아야 된다를 확인
```cpp

void HandleInput(istream& ins) {
}

void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) {
        HandleInput(fs);
    }
}
...

int main(int argc, const char* args[]) {
    if(argc > 1) {
        HandleQuery(args[1]);
    }
    else {
        HandleInput(cin);
    }
}
```

#### 2). 문제를 읽자.
* 입력 출력을 먼저 보고
* 예제 입력을 보고 고민해 보자.
* 그리고 문제를 읽자.

---

### 타이머
3. 시간 복잡도

---

### Vscode 세팅

```
// 오히려 꺼야 한다.
// "cmake.debugConfig": {
//     "cwd": "${workspaceFolder}"
// },
```

---

### 도움 받은 문제라 다시 풀어야 하는 문제는 `X` 표시 하자.

`BOJ_X_OOOOO` 뭐.. 이런식으로