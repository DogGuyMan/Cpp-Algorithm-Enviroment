#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e4 + 1;

// 그래프 인터페이스 정의
class GraphInterface {
public:
    virtual void DFS(int start) = 0;
    virtual void DFSALL() = 0;
};

class ADList : public GraphInterface
{
public:
	int mVcnt;
	vector<deque<int>> mG;
	vector<bool> mVisited;
	
	ADList(int vcnt) : mVcnt(vcnt), mG(vcnt), mVisited(vcnt) {}
	
	ADList(int vcnt, bool reserve) : mVcnt(vcnt)
	{
		// emplace_back, push_back이든 용량(capacity) 초과 시 자동으로 재할당합니다
		// push_back: 스택 → 힙 (임시객체 + 복사/이동)
		// emplace_back : 힙에서 직접 생성 (placement new 사용)
		mG.reserve(vcnt);
		for (int i = 0; i < vcnt; i++)
		{
			mG.emplace_back(deque<int>());
		}
		mVisited.resize(vcnt);
	}

	// $O(|V| + |E|)$
	void DFS(int s) {
		mVisited[s] = true;
		for (auto& e : mG[s])
		{
			if (!mVisited[e])
			{
				DFS(e);
			}
		}
	}

	void DFSALL() {
		int compoCnt = 0;
		mVisited = vector<bool>(mG.size(), false);
		for(int i = 0; i < mG.size(); i++)
			if(!mVisited[i]) {
				DFS(i);
				compoCnt++;
			}
	}
};

class ADJMt : public GraphInterface
{
public:
	int mVcnt = 0;
	int mG[MAX][MAX] = {0,};
	bool mVisited[MAX] = {0,};

	ADJMt(int vcnt)
	{
		mVcnt = vcnt;
	}

	// $O(V^2)$
	void DFS(int s)
	{
		mVisited[s] = true;
		for (int i = 0; i < mVcnt; i++)
		{
			if(mG[s][i] == 0) continue;
			if (!mVisited[i])
			{
				DFS(i);

			}
		}
	}

	// 그래프의 부분집합 컴포넌트를 
	void DFSALL()
	{
		int compoCnt = 0;
		memset(mVisited, 0, mVcnt);
		for (int i = 0; i < mVcnt; i++)
		{
			if(!mVisited[i]){
				DFS(i);
				compoCnt++;
			}
		}
	}
};

int main()
{
	ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	cout << "Hello Graph Algorithm" << '\n';
	return 0;
}