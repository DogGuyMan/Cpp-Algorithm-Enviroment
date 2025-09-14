### 행렬 거듭제곱 피보나치
$$
F_0 = 0, F_1 = 1, \\
F_{i+1} = F_{i} + F_{i-1} \\
F_{i} = F_{i} + 0
$$

$$
\begin{bmatrix}
F_{i_+1} \\
F_{i}
\end{bmatrix} =
\begin{bmatrix}
1, 1 \\
1, 0
\end{bmatrix}
\begin{bmatrix}
F_{i} \\
F_{i-1}
\end{bmatrix} = 
\begin{bmatrix}
1, 1 \\
1, 0
\end{bmatrix}^{i}
\begin{bmatrix}
F_1 \\
F_0
\end{bmatrix} =
\begin{bmatrix}
1, 1 \\
1, 0
\end{bmatrix}^{i}
\begin{bmatrix}
1 \\
0
\end{bmatrix} 
$$


#### 1). 행렬 곱셈
```cpp
typedef vector<vector<int>> imatrix;

imatrix operator*(const imatrix& lhs, const imatrix& rhs) {
	int n = lhs.size();
	int m = rhs[0].size();
	if(lhs[0].size() != rhs.size()) abort();
	int l = rhs.size();
	imatrix newMat(n, vector<int>(m, 0));
	FOR(i, 0, n) {
		FOR(j, 0, m) {
			FOR(k, 0, l) {
				newMat[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}
	return newMat;
}

```

---

#### 2). 정다각행렬 곱셈
```cpp
typedef vector<vector<int>> imatrix;

imatrix operator*(const imatrix& lhs, const imatrix& rhs) {
    int n = lhs.size();
    resMat = vector(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                resMat[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return resMat;
}
```

---

#### 3). 행렬의 거듭제곱
**반드시 정다각 행렬에서만 정의가능**

##### ① 행렬 거듭제곱 분할정복
* 정직하게 하면 $O(n)$
* 분할정복하면 $O(logn)$

```cpp
imatrix& MatPow(const& iMatrix& A, int n) {
    if(n == 0) return I;
    if(n == 1) return A;
    imatrix halfA = MatPow(A, n/2);
    return (power % 2) ? halfA * halfA * A : halfA * halfA;
}
```

##### ② 행렬 거듭제곱과 그 행렬식의 관계.
$$
A = \begin{pmatrix}
a\ b \\
c\ d \\
\end{pmatrix}
$$
$$
det(A^k) = det(A)^{k} \\
= (ac - bd)^k
$$


---

#### 4). 정방행렬 고유값 구하기

$$
A = \begin{pmatrix}
a\ b \\
c\ b \\
\end{pmatrix} \text{일때, 특성 방정식은} (A - \lambda I)\vec{x} = 0, \\
\lambda \text{를 찾는게 목표임} \\
I \text{는 단위 행렬이다.}
$$

$$
det(A -\lambda I) \\
= \begin{pmatrix}
a - \lambda & b \\
c & d - \lambda
\end{pmatrix} \\
= (a - \lambda)(d-\lambda) - bc = 0
$$

그렇다면 $\begin{bmatrix} 1\ 1 \\ 1\ 0\end{bmatrix}$ 에 대한 행렬의 고유값을 이용해 일반해를 구해보자면.
$(1-\lambda)(0-\lambda) - 1 = 0$
$\lambda^2 - \lambda - 1 = 0$
$\lambda = \frac{-(-1) \pm \sqrt{(-1)^2 - 4(1)(-1)}}{2 * (1)} = \frac{1 \pm \sqrt{5}}{2}$

##### 고유 벡터 구하기

* 고유벡터는 수많은.. 엄청 많을 수 있다.
알맞는거 하나 찾아주면 된다.

$$
\vec{v} = \begin{bmatrix}
x_1 \\
x_2
\end{bmatrix}
$$

$$
\begin{bmatrix}
1 - \lambda & 1 \\ 
1 & 0 - \lambda
\end{bmatrix} \begin{bmatrix}
x_1 \\
x_2
\end{bmatrix} 
= 0
$$

$$
\begin{bmatrix}
x_1(1 -\lambda) + x_2 \\
x_1 - x_2\lambda
\end{bmatrix} = 
\begin{bmatrix}
0 \\
0
\end{bmatrix} 
$$

$$
\vec{x} =  (1, -\lambda), (1, 1 -\lambda)
$$

##### 고윳값 분해(대각화 가능한 경우. )
* 고윳값이 뭐다냐.. 행렬$A$를 단순한 하나의 값으로 표현할 수 있다.
$$
Ax = \lambda Ix
$$

##### 행렬 대각화

<div align=center>
    <img src="./P x Pinv.png" width="80%">
    <h5></h5>
</div>

$$
A = PDP^{-1}
$$
* $P$ : 고유벡터들을 열로 가지는 행렬
  $$
  P = \begin{bmatrix}
    1 & 1 \\
    -\lambda_1 & 1 -\lambda_1
  \end{bmatrix}
  $$
* $D$ : 대각선 원소가 고유닶들인 대각행렬 $\lambda I$
* $P^{-1} = P^T$ : P의 역행렬
    $$
    P^{-1} = \frac{1}{det(P)}\begin{bmatrix} 
    d & -b \\
    -c & a
    \end{bmatrix} \\
    = 1 \begin{bmatrix}
      1 -\lambda_1 & -1 \\
      \lambda_1 & 1
    \end{bmatrix}
    $$

$$
A^k = PD^kP^{-1} = PD^kP^{T} = P(\lambda I)^{k}P^T
$$

* 이때 D^k는 단순히 각 대각 원소(고윳값)의 k제곱입니다: 
$$
D^k = \begin{bmatrix} \lambda_1^k & 0 & \cdots & 0 \\
0 & \lambda_2^k & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & \lambda_n^k \end{bmatrix}
$$

따라서 A^k는: 
$$
A^k = \frac{1}{\sqrt{5}} \begin{bmatrix}
\lambda_1^{k+1} - \lambda_2^{k+1} & \lambda_1^k - \lambda_2^k \\ 
\lambda_1^k - \lambda_2^k & \lambda_1^{k-1} - \lambda_2^{k-1} 
\end{bmatrix}
$$

##### 아직도 이해가 잘 안되지만..
유도를 잘 해보면

$$
\lambda_1 = \frac{1 + \sqrt{5}}{2}\\
\lambda_2 = \frac{1 - \sqrt{5}}{2}\\
F(n) = \frac{1}{\sqrt{5}}(\lambda_1)^n -\frac{1}{\sqrt{5}}(\lambda_2)^n
$$

```cpp
const double SQRT5 = sqrt(5);
const double EIGEN_VALUE_1 = (1.0 + SQRT5) / 2.0;
const double EIGEN_VALUE_2 = (1.0 - SQRT5) / 2.0;
inline double FiboFormula(int n) {
    return (1/SQRT5)pow(EIGEN_VALUE_1, n) - (1/SQRT5)pow(EIGEN_VALUE_2, n)
}
```

### 참고
https://ohgym.tistory.com/1
https://blog.naver.com/chaserp/223309007123
https://jjycjnmath.tistory.com/535
https://blog.naver.com/junhyuk7272/50128859551
https://mathbang.net/562
https://blog.naver.com/ldj1725/221252967252