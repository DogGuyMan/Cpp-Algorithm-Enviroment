#include <iostream>
#include <vector>
using namespace std;

class Node
{
public :
	int val;
	Node* lNode = nullptr;
	Node* rNode = nullptr;
	Node(int _val) : val(_val) {}
	~Node()
	{
		if (lNode != nullptr) delete lNode;
		if (rNode != nullptr) delete rNode;
		lNode = nullptr;
		rNode = nullptr;
	}
	Node* AddLeft(int v)  { lNode = new Node(v); return lNode; }
	Node* AddRight(int v) { rNode = new Node(v); return rNode; }
};

void InOrder(Node* cur)
{
	if (cur == nullptr) return;
	InOrder(cur->lNode);
	printf("%c", (char)cur->val);
	InOrder(cur->rNode);
}

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		freopen(argv[1], "r", stdin);
		printf("%s\n", argv[1]);
	}

	for (int t = 1; t <= 10; ++t)
	{
		int N;  scanf("%d", &N);
		vector<Node*> nodeIdx;
		nodeIdx.push_back(nullptr);
		for (int i = 0; i < N; i++)
			nodeIdx.push_back(new Node(-1));
		for (int i = 0; i < N; i++)
		{
			char BUFF[1024];
			scanf(" %[^\n]", BUFF);
			int idx, l = 0, r = 0; char ch;
			int cnt = sscanf(BUFF, "%d %c %d %d", &idx, &ch, &l, &r);
			nodeIdx[idx]->val = ch;
			if (cnt >= 3) nodeIdx[idx]->lNode = nodeIdx[l];
			if (cnt == 4) nodeIdx[idx]->rNode = nodeIdx[r];
		}
		printf("#%d ", t);
		InOrder(nodeIdx[1]);
		printf("\n");
	}
}