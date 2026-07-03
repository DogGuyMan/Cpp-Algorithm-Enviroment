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
//  ▷ 힙 인덱싱(Heap Indexing) 이란?
// ----------------------------------------------------------------------------
//  "완전(complete) 이진 트리를 레벨 순서(위->아래, 왼->오른)로 배열에 담으면,
//   부모-자식 관계가 인덱스 산술만으로 결정된다"는 성질.
//  -> 포인터(lNode/rNode)를 저장하는 대신, 인덱스가 곧 구조가 된다.
//
//   레벨 순서로 배열에 나열한 모습:
//     index : 0 | 1   2 | 3   4   5   6 | 7  8
//             L0|  L1   |      L2        | L3
//
//   ┌ 0-index 공식(이 파일) 	┐	   ┌ 1-index 공식(대표적 힙 / SWEA_1231식) ┐
//   │  left  = 2*i + 1      │		│  left   = 2*i                     │
//   │  right = 2*i + 2      │		│  right  = 2*i + 1                 │
//   │  parent= (i - 1) / 2  │		│  parent = i / 2                   │
//   └───────────────────────┘   	└───────────────────────────────────┘
//   ※ 표현만 다를 뿐 같은 아이디어. 1-index가 2i / 2i+1 로 더 깔끔해
//     경쟁 프로그래밍에서는 1번부터 쓰는 경우가 많다.
//
//  ─ 왜 포인터가 필요 없나? ─
//    o 구조(부모<->자식) = 인덱스 계산(2*i+1 등)          -> 링크 저장 불필요
//    o "자식이 없음"    = 계산한 인덱스가 범위 밖        -> nullptr 검사를 대체
//                         (0-index: idx >= sz / 1-index: idx > N)
//    o 노드가 담는 것   = 값 하나(tree[i])               -> 메모리 최소
//
//  ─ 전제 조건(중요) ─
//    o 완전 트리(왼쪽부터 빈틈없이 채워짐)여야 인덱스가 연속이라 성립.
//    o 희소(sparse)하면 중간 빈 칸까지 배열을 잡아야 해 메모리가 2^깊이로 폭증.
//    o 구멍 뚫린 임의 구조면 이 트릭 대신 "실제 자식 링크"를 저장해야 한다.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

const int K = 2;			 // 트리 차수(2=이진, 3=삼진, 4=사진 ...)
const int MAXN = 1 << 20;	 // 노드 수 상한 (조밀 가정)

int	 tree[MAXN];			 // 노드 값 (0 = 빈 노드로 취급하고 싶으면 별도 used[] 사용)
int	 sz = 0;				 // 사용 중인 노드 개수

inline int Child(int i, int j)	{ return K * i + j + 1; } // j = 0..K-1
inline int Parent(int i)	{ return (i - 1) / K; }

// ---- 전위 순회 (preorder) : 루트 -> 자식들 -----------------------------------
void Preorder(int i)
{
	if (i >= sz) return;	 // 인덱스가 범위 밖 -> 그 자식은 없음 (포인터판 nullptr 검사)
	printf("%d ", tree[i]);
	for (int j = 0; j < K; ++j) Preorder(Child(i, j));
}

// ---- 후위 순회 (postorder) : 자식들 -> 루트 ----------------------------------
void Postorder(int i)
{
	if (i >= sz) return;	 // 인덱스가 범위 밖 -> 그 자식은 없음 (포인터판 nullptr 검사)
	for (int j = 0; j < K; ++j) Postorder(Child(i, j));
	printf("%d ", tree[i]);
}

// ---- (이진 전용) 중위 순회 : 왼쪽 -> 루트 -> 오른쪽 ---------------------------
void Inorder(int i)
{
	if (i >= sz) return;	 // 인덱스가 범위 밖 -> 그 자식은 없음 (포인터판 nullptr 검사)
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
