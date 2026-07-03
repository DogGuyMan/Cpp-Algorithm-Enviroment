// ============================================================================
//  배열 기반 트리 (Implicit / Index-Based Tree)  — CP 최소 템플릿
// ----------------------------------------------------------------------------
//  포인터 없이 배열 인덱스 산술만으로 부모/자식을 계산한다.
//  * 장점 : 캐시 친화적, 할당/해제 없음, 코드가 짧다.
//  * 조건 : 트리가 조밀(dense)할 때 유리. Sparse하면 메모리 낭비가 지수적.
//
//  === k진 트리 인덱스 공식 (0-index) ===
//    j번째 자식 (j = 0 .. K-1) :  child = K*i + j + 1
//    부모                       :  parent = (i - 1) / K
//    (K = 2 이면 익숙한 2*i+1, 2*i+2, (i-1)/2 로 환원됨)
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

const int K = 2;			 // 트리 차수(2=이진, 3=삼진, 4=사진 ...)
const int MAXN = 1 << 20;	 // 노드 수 상한 (조밀 가정)

int	 tree[MAXN];			 // 노드 값 (0 = 빈 노드로 취급하고 싶으면 별도 used[] 사용)
int	 sz = 0;				 // 사용 중인 노드 개수

inline int Child(int i, int j)	{ return K * i + j + 1; } // j = 0..K-1
inline int Parent(int i)	{ return (i - 1) / K; }

// ---- 전위 순회 (preorder) : 루트 → 자식들 -----------------------------------
void Preorder(int i)
{
	if (i >= sz) return;
	printf("%d ", tree[i]);
	for (int j = 0; j < K; ++j) Preorder(Child(i, j));
}

// ---- 후위 순회 (postorder) : 자식들 → 루트 ----------------------------------
void Postorder(int i)
{
	if (i >= sz) return;
	for (int j = 0; j < K; ++j) Postorder(Child(i, j));
	printf("%d ", tree[i]);
}

// ---- (이진 전용) 중위 순회 : 왼쪽 → 루트 → 오른쪽 ---------------------------
void Inorder(int i)
{
	if (i >= sz) return;
	Inorder(Child(i, 0));	 // left
	printf("%d ", tree[i]);
	Inorder(Child(i, 1));	 // right
}

int main()
{
	// 예시: 값 0..8 을 레벨 순서(BFS 순서)로 채운 이진 완전 트리
	//                0
	//            1       2
	//          3   4   5   6
	//         7 8
	sz = 9;
	for (int i = 0; i < sz; ++i) tree[i] = i;

	printf("preorder : "); Preorder(0);  printf("\n");
	printf("inorder  : "); Inorder(0);   printf("\n");
	printf("postorder: "); Postorder(0); printf("\n");

	// 부모/자식 확인
	printf("node 1 children:");
	for (int j = 0; j < K; ++j) printf(" %d", Child(1, j)); // 3 4
	printf("\nnode 4 parent : %d\n", Parent(4));			// 1
	return 0;
}
