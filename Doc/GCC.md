### Makefile

https://80000coding.oopy.io/b553047b-42f6-4066-9f30-f4aef0b0503d

### 컴파일 옵션

`gcc -c 1.c` : main 함수 없이도 컴파일 가능 그렇다면 오브젝트 파일이 생기겠지.
`gcc -g 1.c`

```
**gcc 옵션
    * -v : 컴파일 상태 출력
    * -O2 : 최적화 레벨 2 적용
    * -E : 전처리 과정 결과 출력. --save-temps 옵션 사용 추천
    * -S : cc1으로 전처리된 파일을 어셈블리 파일(.s) 까지만 컴파일
    * -c : as에 의한 어셈블까지만 수행하고 링크하지 않음
    * --save-temps : 전처리 파일(*.i) 과 어셈블리 파일(*.s) 를 지우지 않고 현재 디렉토리에 저장 (컴파일 오류 분석용)


### 전처리기
    * -I : 헤더 파일 경로 (ex. -I/usr/local/include)
    * -D[매크로]=[값] : #define 매크로 (ex. -DDEBUG, -DPACKAGE=1)
    * -U[매크로] : #undef 매크로
    * -M : make를 위한 소스 파일의 모든 종속 항목 출력
    * -MM : 기본 include 디렉토리의 헤더 파일을 제외한 종속 항목 출력
    * -nostdinc : 기본 include 디렉토리(/usr/include) 에서 헤더 파일을 탐ㅅ핵하지 않고 -I 옵션의 디렉토리에서만 헤더 파일 검색
    * -C : -E 와 함께 사용. 전처리 과정에서 주석을 제거하지 않음.
    * -Wp,[옵션] : gcc를 거치지 않고 cpp0 으로 바로 옵션을 전달
        (ex. -Wp,-DDEBUG,-I/usr/include,-M)


### C 컴파일러
    * -W : 합법적이지만 모호한 코딩에 경고 출력
    * -Wall : 모호한 코딩에 경고 출력
    * -ansi : ANSI C 표준으로 문법 체크. (GNU C 확장 문법 사용 불가)
    * -std=[C 표준] : 표준 지정시 사용 (ex. -std=c++11)
    * -w : 경고 메시지 제거하지
    * -Werror : 경고 발생시 컴파일 중단
    * -pedantic : ANSI C89 표준의 모든 경고 메시지 표시
    * -pedantic-errors : ANSI C89 표준의 모든 오류 메시지 표시
    * -O[숫자] : 최적화 옵션
        * -O0 : 최적화 미수행(default). 인라인 함수 확장되지 않음.
        * -O1 : 파일을 가능한 작게 하면서, 컴파일 시간이 오래걸리지 않는 범위에서 최적화
        * -O2 : 속도 최적화. (코드 크기 고려)
        * -O3 : 속도 최적화. (코드 크기 고려하지 않음 : 모든 함수를 인라인 함수로 취급)
        * -Os : 사이즈 최적화. (ex. 임베디드 시스템)
    * -g : 디버깅 정보 추가. (용량이 매우 커짐)
        * -g0 : 디버깅 정보 미삽입
        * -g2 : -g 와 동일
        * -g3 : 가장 많은 디버깅 정보
        * -pg : 프로파일 코드 삽입. 프로그램 실행 후 gmon.out에 프로파일 결과 저장하여 gprof 로 분석 가능.

### 어셈블러
    * -Wa,[as 옵션] : gcc를 거치지 않고 바로 전달. (ex. -Wa-al,-as)
    * -al : 어셈블된 인스트럭션 출력
    * -as : 정의된 심볼 출력
    * -I[경로] : include 디렉토리 지정. 어셈블리 소스에서 사용된 .include 지정자가 지정한 헤더 파일 검색시 사용
    * -W : 경고 메시지 미 출력(--no-warm)
    * -match=[아키텍처 문자열] : 해당 어셈블리s

### 링커
    * -L[라이브러리 경로] : 사용할 라이브러리 경로 지정
    * -l [라이브러리 이름] : 사용할 라이브러리 이름 지정
    * -shared : 공유라이브러리 를 우선하여 링크(default)
    * -static : 정적 라이브러릴르 우선하여 링크
    * -nostdlib : 링크 시 표준 C 라이브러리 미사용
    * -nostartfiles : 링크 시 crt1.o 등 start up 파일 미사용
    * -Wl,[링크 옵션] : gcc를 거치지 않고 링크에게 옵션 전달. 사용법은 -Wa와 동일
    * -s : 실행 파일에 심볼 테이블 제거
    * -x : 출력 파일에 로컬 심볼 제거
    * -n : 읽기 전용 텍스트 영역 사용
    * -r : 추후 링크 가능하도록 오브젝트 생성
    * -e [name] : 시작 심볼을 name 심볼로 사용(기본은 _start 심볼)
    * -M : 자세한 심볼 정보 출력
    * -oformat [format] : format 형식의 오브젝트 파일 생성
  
```

### 디렉토리 구조

#### 1). 한 번에 모든 파일 컴파일 및 링크
```shell
g++ kim.cpp lee.cpp main.cpp -o program
g++ fruit_main.cpp  FruitBuyer.cpp FruitSeller.cpp -o fruit_program
```

#### 2). 단계별 컴파일 후 링크
```shell
g++ -c kim.cpp -o kim.o
g++ -c lee.cpp -o lee.o
g++ -c main.cpp -o main.o
g++ kim.o lee.o main.o -o program
```

#### 3). include 헤더
```shell
clang++ -I car_const.hpp -c struct_test.cpp
clang++ struct_test.o -o struct_test
g++ car_class.cpp car_main.cpp -I car_const.hpp -o car_program
MallocStackLogging=1 leaks --atExit --list -- "./$BUILD_DIR/$PROJECT_NAME"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program
```


### 컴파일 옵션

```shell
clang++  -I"./Include" \
    -g -fno-omit-frame-pointer \ # 프레임 포인터를 보존. 스택트레이스가 정확해져 디버깅·프로파일링 용이. 약간의 성능 손해(보통 1–3%). 
    -fcolor-diagnostics \ # 컴파일 경고·에러를 컬러로 출력. 가독성 향상.
    -fno-common \ # 동일 전역변수의 “암시적 다중 정의”를 금지.
    -fsanitize=undefined,integer \ # UBSan 활성화 잘못된 시프트, 0으로 나눗셈, 배열 경계 위반, 정렬(alignment) 위반, null 관련 연산, 서명/무부호 정수 오버플로 등 정수 연산 오류 포착
    -fno-sanitize-recover=all \ # Sanitizer 에러 발생 시 계속 실행하지 않고 즉시 중단. 실패 지점에서 정확한 스택트레이스·코어덤프 확보.
    -Wall -Wextra -Werror -Wshadow -Warray-bounds -Wduplicate-decl-specifier -Wredundant-decls \
    -Wno-error=unused-but-set-variable \ # “값을 읽지 않고 세팅만 한 변수” 경고를 에러로 승격하지 않음. 경고는 남김.
    -Wno-unused-variable \ # 사용되지 않는 변수 경고 자체를 끔.
    -Wno-unused-function \ # 정의만 있고 호출되지 않은 함수 경고를 끔. 주로 static/내부 유틸에 해당.
    -Wno-unused-parameter \ # 사용되지 않는 함수 매개변수 경고를 끔. 인터페이스 맞출 때 유용.
    --std=c++17 -O1 -g "./Problems/${ProbNum}/main.cpp" -o "./Problems/${ProbNum}/main"
```