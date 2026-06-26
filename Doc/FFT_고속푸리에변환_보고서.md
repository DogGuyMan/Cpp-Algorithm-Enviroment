# FFT(고속 푸리에 변환)로 큰 수 곱셈하기 — 신호처리 0지식 학생용 보고서

> 이 문서는 "푸리에"라는 단어를 처음 듣는 학생도 이해할 수 있게 쓴 보고서입니다.
> 삼각함수와 곱셈, 그리고 분할정복(divide and conquer)만 알면 끝까지 따라올 수 있습니다.
> 마지막에 첨부된 PS용 C++ 코드를 한 줄씩 해부합니다.

---

## 0. 한 줄 요약

> **FFT는 "다항식 곱셈(=큰 수 곱셈)을 $O(n^2)$에서 $O(n \log n)$으로 줄여주는 마법 같은 변환"이다.**

신호처리에서 나온 도구지만, 우리(PS 하는 사람)에게 중요한 건 단 하나입니다.

- **두 개의 긴 수(또는 다항식)를 아주 빠르게 곱하고 싶다.**

그게 전부입니다. 신호, 주파수, 스펙트럼 같은 단어는 **몰라도 됩니다.**

---

## 1. 우리가 풀려는 문제: "엄청 큰 수 곱셈"

`12345678901234567890 × 98765432109876543210` 같은 곱셈을 생각해 봅시다.

`int`, `long long`으로는 담을 수 없는 큰 수입니다. 그래서 **문자열로 받아서 직접 곱셈**을 해야 합니다.

초등학교 때 배운 세로 곱셈을 떠올려 보세요.

```
        1 2 3
      ×   4 5
      -------
        6 1 5     (123 × 5)
      4 9 2       (123 × 4, 한 칸 밀어서)
      -------
      5 5 3 5
```

이 방식은 **위 숫자의 모든 자리** × **아래 숫자의 모든 자리**를 다 곱합니다.
즉 자릿수가 각각 $n$개라면 곱셈을 $n \times n = n^2$번 합니다.

- 자릿수가 10개면 → 100번
- 자릿수가 100,000개면 → **100억 번** 💀

$O(n^2)$은 자릿수가 수만 자리만 되어도 시간 초과입니다.
**이걸 $O(n \log n)$으로 줄이는 게 FFT입니다.**

---

## 2. 핵심 발상 1: "큰 수 = 다항식"

여기가 첫 번째 깨달음입니다. **숫자를 다항식으로 바꿔서 생각합니다.**

예를 들어 숫자 `123`은:

$$123 = 1 \times 10^2 + 2 \times 10^1 + 3 \times 10^0$$

여기서 `10`을 변수 $x$로 바꿔 봅시다.

$$A(x) = 1 \cdot x^2 + 2 \cdot x + 3$$

즉 **숫자의 각 자릿수가 다항식의 계수(coefficient)** 가 됩니다.

> 코드에서 자릿수를 배열에 거꾸로 담는 이유가 이것입니다.
> `123` → 배열 `[3, 2, 1]` (낮은 자리 = 낮은 차수 = 배열 앞쪽)

그럼 두 수의 곱셈은 **두 다항식의 곱셈**과 똑같습니다.

$$A(x) \times B(x) = C(x)$$

곱한 다항식 $C(x)$의 계수를 구한 뒤, 마지막에 $x = 10$을 대입하면서
**올림(carry)** 만 처리해주면 원래 숫자 곱셈 결과가 나옵니다.

### 다항식 곱셈 = 합성곱(convolution)

$A(x)$와 $B(x)$를 곱할 때 $C(x)$의 $k$번째 계수는 이렇게 만들어집니다.

$$c_k = \sum_{i+j=k} a_i \cdot b_j$$

> "차수가 더해서 $k$가 되는 모든 조합의 곱을 더한다."

이걸 **합성곱(convolution)** 이라고 부릅니다. 그냥 곧이곧대로 계산하면
모든 $(i, j)$ 쌍을 보니까 또 $O(n^2)$입니다. **아직 안 빨라졌습니다.**

---

## 3. 핵심 발상 2: 다항식을 표현하는 두 가지 방법

다항식 $A(x)$를 표현하는 방법은 사실 두 가지가 있습니다.

### (A) 계수 표현 (Coefficient form) — 우리가 아는 방식
$$A(x) = a_0 + a_1 x + a_2 x^2 + \dots$$
계수 리스트 `[a0, a1, a2, ...]`로 표현. **곱셈하면 $O(n^2)$.**

### (B) 점-값 표현 (Point-value form) — 핵심 트릭
> **"$n$차 다항식은 서로 다른 점 $n+1$개에서의 값으로도 유일하게 결정된다."**

중학교에서 배운 것을 떠올려 보세요.

- 점 2개 → 직선(1차) 1개 결정
- 점 3개 → 포물선(2차) 1개 결정
- 점 $n+1$개 → $n$차 다항식 1개 결정

그래서 다항식을 "여러 점에서 함숫값을 찍은 표"로도 표현할 수 있습니다.

$$A: \{(x_0, A(x_0)), (x_1, A(x_1)), \dots\}$$

### 점-값 표현의 엄청난 장점

같은 $x$ 점들에서 두 다항식의 값을 안다면, **곱한 다항식의 값은 그냥 곱하면 끝**입니다.

$$C(x_i) = A(x_i) \times B(x_i)$$

점이 $2n$개 있으면 곱셈을 **딱 $2n$번**만 하면 됩니다. 이게 **$O(n)$** 입니다!

```
계수 표현   --(곱셈 O(n^2), 느림)-->   계수 표현
점-값 표현  --(곱셈 O(n),  빠름!)-->   점-값 표현
```

### 그래서 전략은 이렇게 됩니다

```
1. A, B (계수 표현)  ──▶  A, B (점-값 표현)      [평가, evaluation]
2. 점마다 값을 곱한다                            [O(n), 빠름]
3. 결과 (점-값 표현) ──▶ 결과 C (계수 표현)       [보간, interpolation]
```

문제는 **1번(계수→점값)과 3번(점값→계수)을 빨리 하는 것**입니다.
아무 점이나 막 골라서 대입하면 그 과정 자체가 $O(n^2)$이라 의미가 없습니다.

> **여기서 등장하는 것이 바로 FFT입니다.**
> FFT = "특별한 점들"을 영리하게 골라서 1번과 3번을 $O(n \log n)$에 해주는 알고리즘.

---

## 4. 핵심 발상 3: "특별한 점" = 단위근 (Roots of Unity)

빠르게 만드는 비결은 **대입할 $x$ 점들을 아무거나 쓰지 않고, 아주 대칭적인 점들로 고르는 것**입니다. 그 점들이 **단위근(roots of unity)** 입니다.

### 단위근이 뭔가요? (복소수가 처음이어도 OK)

복소수를 **반지름 1짜리 원 위의 점**이라고 생각하세요.
이 원을 $n$등분 한 점들이 "$n$개의 단위근"입니다.

예를 들어 $n = 4$이면 원을 4등분: 오른쪽, 위, 왼쪽, 아래 (즉 $1, i, -1, -i$).

각 점은 각도 $\theta$로 표현되고, 복소수로는:
$$w = \cos\theta + i\sin\theta$$

> 코드의 이 줄이 바로 단위근을 만드는 부분입니다.
> ```cpp
> double ang = 2 * M_PI / len;        // 원을 len등분한 각도
> base wlen(cos(ang), sin(ang));      // 그 각도의 단위근
> ```

### 왜 하필 단위근인가?

단위근은 **제곱하면 절반 크기 문제의 단위근이 되는** 마법 같은 대칭성이 있습니다.

- "$x$"와 "$-x$"가 항상 짝으로 존재한다 (원이라서 정반대편이 있음).
- 이 대칭성 덕분에 **큰 문제를 절반 크기 문제 2개로 쪼갤 수 있습니다.**

이게 바로 **분할정복**이 작동하는 이유고, $\log n$이 등장하는 이유입니다.

---

## 5. FFT의 분할정복 원리 (직관만)

다항식 $A(x)$의 계수를 **짝수 번째 / 홀수 번째**로 나눕니다.

$$A(x) = \underbrace{(a_0 + a_2 x^2 + \dots)}_{\text{짝수항}} + \underbrace{(a_1 x + a_3 x^3 + \dots)}_{\text{홀수항}}$$

이걸 정리하면:

$$A(x) = A_{even}(x^2) + x \cdot A_{odd}(x^2)$$

여기서 핵심은:

- $A_{even}$, $A_{odd}$는 **크기가 절반인 다항식**입니다.
- 단위근의 대칭성($x$와 $-x$가 같은 $x^2$를 가짐) 덕분에,
  $A(x)$와 $A(-x)$를 **한 번의 계산 재료로 동시에** 얻을 수 있습니다.

$$A(x) = A_{even}(x^2) + x \cdot A_{odd}(x^2)$$
$$A(-x) = A_{even}(x^2) - x \cdot A_{odd}(x^2)$$

> 두 식이 **덧셈/뺄셈만 다릅니다.** 한 번 계산해서 두 점을 동시에 채웁니다.

이 "절반으로 쪼개기"를 반복하면 단계가 $\log n$번, 각 단계가 $O(n)$이라
전체가 **$O(n \log n)$** 이 됩니다. 이게 FFT의 전부입니다.

> 코드는 재귀 대신 **반복문(bottom-up)** 으로 구현했는데, 원리는 같습니다.
> 작은 조각부터 합쳐 올라가는 방식(2개씩 → 4개씩 → 8개씩 → ...)입니다.

### IFFT (역변환): 점-값 → 계수로 되돌리기

곱셈이 끝나면 결과가 "점-값 표현"입니다. 이걸 다시 "계수 표현"으로
되돌려야 우리가 원하는 숫자를 읽을 수 있습니다. 이 되돌리기를 **IFFT**라고 합니다.

놀랍게도 IFFT는 **FFT와 거의 똑같습니다.** 딱 두 가지만 다릅니다.

1. 단위근을 **반대 방향**으로 돈다 (각도에 $-1$을 곱함).
2. 마지막에 전체를 $n$으로 나눈다.

> 코드에서 `invert` 플래그 하나로 FFT와 IFFT를 모두 처리하는 이유입니다.
> ```cpp
> double ang = 2 * M_PI / len * (invert ? -1 : 1);  // 1번: 방향 반대
> ...
> if (invert) for (...) a[i] /= n;                  // 2번: n으로 나누기
> ```

---

## 6. 코드 전체 해부

이제 처음 보면 암호처럼 보이던 코드가 전부 설명됩니다.

### 6.1 `fft()` — 핵심 변환 함수

```cpp
void fft(vector<base>& a, bool invert) {
    int n = a.size();
```
`a`는 다항식 계수 배열(복소수). `invert=false`면 FFT(계수→점값),
`true`면 IFFT(점값→계수). `n`은 항상 2의 거듭제곱입니다.

#### ① 비트 반전 재배치 (Bit-reversal Permutation)

```cpp
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
```

- 분할정복에서 "짝수/홀수로 계속 쪼개면" 원소들이 결국
  **인덱스를 2진수로 뒤집은 순서**로 재배열됩니다.
  (예: `001` ↔ `100`, `011` ↔ `110`)
- 재귀 없이 반복문으로 풀려면, 처음에 이 순서로 미리 섞어두면
  나중에 단순히 인접한 것끼리 합치기만 하면 됩니다.
- **결론: "재귀 안 쓰려고 미리 자리를 맞춰두는 준비 작업"** 입니다.

#### ② 바텀업 분할정복 (나비 연산, Butterfly)

```cpp
    for (int len = 2; len <= n; len <<= 1) {        // 조각 크기: 2,4,8,...
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));              // 이 단계의 단위근
        for (int i = 0; i < n; i += len) {          // 각 블록마다
            base w(1);                              // 1부터 시작
            for (int j = 0; j < len / 2; j++) {
                base u = a[i + j];                  // 짝수 쪽
                base v = a[i + j + len / 2] * w;    // 홀수 쪽 × 단위근
                a[i + j]           = u + v;         // A(x)  = even + odd
                a[i + j + len / 2] = u - v;         // A(-x) = even - odd
                w *= wlen;                          // 다음 단위근으로 회전
            }
        }
    }
```

- 위에서 본 `A(x) = u + v`, `A(-x) = u - v` 공식이 **바로 이 줄**입니다.
- `len`을 2배씩 키우며(2→4→8...) 작은 조각을 큰 조각으로 합쳐 올라갑니다.
- 이 `u+v / u-v` 쌍 연산을 모양 때문에 **나비 연산(butterfly)** 이라 부릅니다.

#### ③ IFFT 스케일링

```cpp
    if (invert) {
        for (int i = 0; i < n; i++) a[i] /= n;      // 되돌릴 때만 n으로 나눔
    }
}
```

### 6.2 `multiply()` — 곱셈 조립

```cpp
void multiply(const vector<int>& a, const vector<int>& b, vector<int>& res) {
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;        // 결과를 담을 2의 거듭제곱 크기
    fa.resize(n);  fb.resize(n);                    // 나머지는 0으로 패딩

    fft(fa, false);  fft(fb, false);                // 1. 계수 → 점값 (둘 다)
    for (int i = 0; i < n; i++) fa[i] *= fb[i];     // 2. 점마다 곱 (O(n), 핵심!)
    fft(fa, true);                                  // 3. 점값 → 계수 (IFFT)

    res.resize(n);
    for (int i = 0; i < n; i++)
        res[i] = (int)round(fa[i].real());          // 4. 실수부 반올림 → 정수 계수
}
```

> **3장에서 세운 3단계 전략이 그대로 코드가 됩니다.**
> - `n`을 `a.size()+b.size()` 이상의 2의 거듭제곱으로 잡는 이유:
>   곱한 다항식의 차수가 그만큼 커지고, FFT는 2의 거듭제곱 크기에서만 동작하기 때문.
> - `round`로 반올림하는 이유: `double` 연산이라 `5.0`이 `4.9999`처럼
>   미세 오차가 생기므로 정수로 보정.

### 6.3 `main()` — 입출력과 올림 처리

```cpp
    // 자릿수를 거꾸로 담기: "123" → [3,2,1] (낮은 자리 = 낮은 차수)
    for (int i = s1.length() - 1; i >= 0; i--) a.push_back(s1[i] - '0');
    for (int i = s2.length() - 1; i >= 0; i--) b.push_back(s2[i] - '0');

    vector<int> res;
    multiply(a, b, res);

    // 올림(carry) 처리: 각 자리를 10 미만으로 정리
    int carry = 0;
    for (int i = 0; i < res.size(); i++) {
        res[i] += carry;
        carry = res[i] / 10;        // 10 넘는 부분은 위 자리로
        res[i] %= 10;
    }
    if (carry > 0) res.push_back(carry);

    reverse(res.begin(), res.end());   // 다시 뒤집어서 사람이 읽는 순서로
```

- **올림 처리**가 중요합니다. FFT가 만든 계수는 `[15, 25, ...]`처럼
  10을 넘을 수 있습니다($x=10$ 대입). 이걸 자리올림으로 정리해야 진짜 숫자가 됩니다.
- 앞자리에 패딩으로 생긴 의미 없는 `0`은 마지막에 건너뛰고 출력합니다.

---

## 7. 전체 흐름 한눈에 보기

```
"123"  "45"   (문자열 입력)
   │
   ▼  자릿수를 다항식 계수로 (거꾸로)
[3,2,1]  [5,4]   ← 계수 표현
   │
   ▼  FFT  (계수 → 점값)         ★ O(n log n)
점값A    점값B
   │
   ▼  점마다 곱하기              ★ O(n)
점값C
   │
   ▼  IFFT (점값 → 계수)         ★ O(n log n)
[15, 22, 13, 4, ...]   ← 곱한 다항식 계수 (10 넘을 수 있음)
   │
   ▼  올림(carry) 처리
[5, 3, 5, 5]
   │
   ▼  뒤집어서 출력
"5535"
```

---

## 8. 복잡도 정리

| 단계 | 방식 | 복잡도 |
|------|------|--------|
| 계수 → 점값 (FFT ×2) | 분할정복 | $O(n \log n)$ |
| 점별 곱셈 | 단순 곱 | $O(n)$ |
| 점값 → 계수 (IFFT) | 분할정복 | $O(n \log n)$ |
| 올림 처리 | 선형 스캔 | $O(n)$ |
| **전체** | | **$O(n \log n)$** |

기존 세로 곱셈 $O(n^2)$ 대비, 자릿수가 클수록 압도적으로 빨라집니다.

---

## 9. PS에서 주의할 점 (실전 팁)

1. **정밀도(precision) 문제**
   - `double` 기반 `complex`는 자릿수가 아주 많거나 계수가 크면
     반올림 오차로 답이 틀릴 수 있습니다.
   - 대안: 더 큰 정밀도(`long double`)를 쓰거나, 오차가 아예 없는
     **NTT(Number Theoretic Transform, 정수 모듈러 FFT)** 를 사용합니다.

2. **크기는 반드시 2의 거듭제곱**
   - `while (n < a.size()+b.size()) n <<= 1;` — 이 패딩을 빠뜨리면 안 됩니다.

3. **0 입력 예외 처리**
   - 한쪽이 `"0"`이면 결과는 무조건 `0`. 코드에 따로 처리되어 있습니다.

4. **언제 FFT를 쓰나?**
   - "두 큰 수/긴 다항식 곱셈", "합성곱(convolution)", "문자열 매칭의 변형",
     "특정 합이 되는 쌍의 개수 세기" 등에서 등장합니다.
   - 키워드: **"두 배열을 합성곱하라"** 가 보이면 FFT를 의심하세요.

---

## 10. 한 문장 복습

> 큰 수 곱셈을 다항식 곱셈으로 바꾸고,
> 다항식을 **단위근이라는 특별한 점들에서의 값**으로 표현(FFT)한 뒤,
> 점끼리 빠르게 곱하고, 다시 계수로 되돌려(IFFT) 올림만 처리하면,
> **$O(n^2)$ 곱셈이 $O(n \log n)$이 된다.**

신호처리는 몰라도 됩니다. **"빠른 곱셈 도구"** 로 기억하면 충분합니다.

---

## 부록: 분석한 원본 코드

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <string>
#include <algorithm>
using namespace std;

typedef complex<double> base;

void fft(vector<base>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; j++) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& res) {
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(n);
    for (int i = 0; i < n; i++) res[i] = (int)round(fa[i].real());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    if (!(cin >> s1 >> s2)) return 0;
    if (s1 == "0" || s2 == "0") { cout << 0 << "\n"; return 0; }
    vector<int> a, b;
    for (int i = s1.length() - 1; i >= 0; i--) a.push_back(s1[i] - '0');
    for (int i = s2.length() - 1; i >= 0; i--) b.push_back(s2[i] - '0');
    vector<int> res;
    multiply(a, b, res);
    int carry = 0;
    for (int i = 0; i < res.size(); i++) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
    if (carry > 0) res.push_back(carry);
    reverse(res.begin(), res.end());
    int start = 0;
    while (start < res.size() && res[start] == 0) start++;
    for (int i = start; i < res.size(); i++) cout << res[i];
    cout << "\n";
    return 0;
}
```
