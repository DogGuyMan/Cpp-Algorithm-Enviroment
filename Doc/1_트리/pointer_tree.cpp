// ============================================================================
//  포인터 기반 트리 (Node/Pointer Tree)  — CP 최소 템플릿
// ----------------------------------------------------------------------------
//  노드마다 자식 포인터를 들고 있는 전통적 구조.
//  * 장점 : 실제 노드 수만큼만 메모리 사용. Sparse / 가변 차수에 유리.
//  * 단점 : 할당/해제 비용, 캐시 지역성 낮음, 코드가 길어짐.
//
//  아래는 자식 수가 가변인 N진 트리(vector<Node*>)로 작성.
//  이진 고정이면 struct Node{ int v; Node* l; Node* r; }; 로 줄이면 됨.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int			  val;
	vector<Node*> childPtr;			// 자식 노드 포인터들

	Node(int v) : val(v) {}
	Node* AddChild(int v)			// 자식 추가 후 그 노드 반환
	{
		Node* nodePtr = new Node(v);
		childPtr.push_back(nodePtr);
		return nodePtr;
	}
};

// ---- 전위 순회 (preorder) : 루트 → 자식들 -----------------------------------
void Preorder(Node* curPtr)
{
	if (curPtr == nullptr) return;
	printf("%d ", curPtr->val);
	for (Node * nextPtr : curPtr->childPtr) Preorder(nextPtr);
}

// ---- 후위 순회 (postorder) : 자식들 → 루트 ----------------------------------
void Postorder(Node* curPtr)
{
	if (curPtr == nullptr) return;
	for (Node * nextPtr : curPtr->childPtr) Postorder(nextPtr);
	printf("%d ", curPtr->val);
}

// ---- 메모리 해제 (후위 순서로 자식부터 delete) ------------------------------
void Clear(Node* curPtr)
{
	if (curPtr == nullptr) return;
	for (Node * nextPtr : curPtr->childPtr) Clear(nextPtr);
	delete curPtr;
}

int main()
{
	//         0
	//      1     2
	//    3   4     5
	Node* rootPtr = new Node(0);
	Node* n1Ptr	  = rootPtr->AddChild(1);
	Node* n2Ptr	  = rootPtr->AddChild(2);
	n1Ptr->AddChild(3);
	n1Ptr->AddChild(4);
	n2Ptr->AddChild(5);

	printf("preorder : "); Preorder(rootPtr);  printf("\n");
	printf("postorder: "); Postorder(rootPtr); printf("\n");

	Clear(rootPtr);					// 누수 방지 (CP에선 생략하기도 함)
	return 0;
}
