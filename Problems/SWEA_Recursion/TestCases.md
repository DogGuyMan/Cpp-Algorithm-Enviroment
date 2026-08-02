# SWEA_Recursion 팩토리얼 — 테스트 케이스 10종

대상 코드: `scanf`로 `T` 읽고, `factorial(num)`을 `long long`으로 재귀 계산해
`#%d %d! = %lld` 형식으로 출력하는 버전.

모든 결과는 아래 두 가지 빌드로 **실제 실행해서 확인한 값**이다.

- `plain` : `clang++ --std=c++17 -O0`
- `ubsan` : `Shell/SWEA_Execute.sh`와 동일한 `-fsanitize=undefined,integer -fno-sanitize-recover=all`

기대 출력(`Expected/*.out`)은 프로그램 출력을 베낀 것이 아니라
Python `math.factorial`로 **독립 생성**한 뒤 diff로 대조했다.

---

## 케이스 목록

| # | 파일 | 입력 | 노리는 것 | 실측 결과 |
|---|------|------|-----------|-----------|
| 01 | `input_01_sample.txt` | `3 / 9 12 20` | 정상 경로 (기존 `input.txt`와 동일) | PASS |
| 02 | `input_02_base_zero.txt` | `1 / 0` | 기저 조건 `num == 0` → 1 | PASS |
| 03 | `input_03_boundary_int.txt` | `2 / 12 13` | `int` 경계. 12!=479001600은 int에 들어가고 13!=6227020800은 넘침 → 승격이 제대로 되는지 | PASS |
| 04 | `input_04_boundary_llmax.txt` | `1 / 20` | `long long`에 들어가는 최대 팩토리얼 | PASS |
| 05 | `input_05_overflow_ll.txt` | `1 / 21` | **부호 있는 정수 오버플로(UB)** | ❌ plain: `-4249290049419214848` / ubsan: **abort(134)** |
| 06 | `input_06_negative.txt` | `1 / -1` | **기저 조건이 `== 0`뿐 → 무한 재귀** | ❌ plain: **SIGSEGV(139)** / ubsan: stack-overflow abort |
| 07 | `input_07_tc_shortage.txt` | `3 / 5` (값 부족) | **`scanf` 반환값 미검사** → 실패해도 `num`이 그대로 남음 | ❌ `#1 #2 #3` 전부 `5! = 120` (조용히 반복) |
| 08 | `input_08_tc_zero.txt` | `0` | `T = 0` 공회전, 출력 없음 | PASS (출력 0줄, exit 0) |
| 09 | `input_09_format_variants.txt` | `4 0 1 007 +5` (한 줄, 개행 없이 끝) | 공백 구분·선행 0·`+` 부호·EOF 개행 없음 | PASS (`0! 1! 7! 5!`) |
| 10 | `input_10_regression_all.txt` | `21 / 0..20` | 유효 범위 전수 회귀 | PASS (21줄 전부 일치) |

정상/경계 7종은 오라클과 완전 일치(**7 pass / 0 fail**), 결함 노출 3종(05·06·07)은 의도대로 터진다.

## 확인된 결함 3가지

1. **`num` 21 이상에서 오버플로.** `20! = 2432902008176640000`이 `long long` 한계.
   `21 * 20!`이 UB라서 저장소 빌드 플래그(`-fno-sanitize-recover=all`)에선 그냥 죽는다.
   → 입력 검증을 넣든지, 문제 제약이 `N ≤ 12`면 그걸 코드에도 박아두는 편이 낫다.
2. **음수에서 무한 재귀.** `if (num == 0)` 대신 `if (num <= 1)`로 바꿔도
   음수는 여전히 못 막는다. `num < 0`을 별도로 걸러야 한다.
3. **`scanf` 반환값을 안 본다.** 입력이 모자라거나 숫자가 아니면 `num`이 이전 값(첫 회차면
   미초기화 값)을 그대로 쓴다. `if (scanf("%d", &num) != 1) break;` 한 줄이면 막힌다.

`T` 자체도 같은 문제가 있다. 빈 파일을 주면 `T`가 미초기화 상태로 읽히는데,
이번 실행에선 우연히 0 이하가 나와 조용히 끝났을 뿐 보장된 동작이 아니다.

## 돌리는 법

⚠️ 위 코드에는 `freopen(argv[1], "r", stdin)`이 없어서
`SWEA_Execute.sh`의 쿼리 모드(`$2 = 1`)로는 파일이 안 먹는다.
현재 `main.cpp`에 있는 `if (argc > 1) freopen(argv[1], "r", stdin);` 두 줄을 유지해야 한다.

```bash
# 저장소 하네스로 전체 순회 (로그는 log.txt)
sh ./Shell/SWEA_Execute.sh Recursion 1

# 기대 출력과 자동 대조 (05·06·07은 Expected가 없으니 자동 제외)
cd Problems/SWEA_Recursion
for e in Expected/*.out; do
  n=$(basename "$e" .out)
  if ./main "InputQuerys/$n.txt" 2>/dev/null | diff -q - "$e" >/dev/null
  then echo "PASS  $n"; else echo "FAIL  $n"; fi
done
```
