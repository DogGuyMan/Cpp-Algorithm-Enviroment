달성할 목표

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
int QUERY_CNT = 1;

void HandleInput(istream& ins) {
    while(!ins.eof() && QUERY_CNT-- > 0 ) {
        ...
    }
}

...

int main(int argc, char * args[]) {
    if(argc <= 1) {
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
     }
}
```

### 타이머
3. 시간 복잡도

### Vscode 세팅

```
// 오히려 꺼야 한다.
// "cmake.debugConfig": {
//     "cwd": "${workspaceFolder}"
// },
```

