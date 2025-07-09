## Union-Find
> #### Disjoint Set 자료구조를 이용한 알고리즘

### 📄 1. Union-Find

#### 1). 설명

* 여러개의 노드가 존재할 때, 두개의 노드 선택하고 두 노드가 서로 같은 그래프에 속하나?

#### 2). 사용 예시.

##### ① 사이클을 확인할 떄 사용.
* 최소 신장 트리에서 사이클을 체크할 수 있다.

##### ② 시간 복잡도가 빠른
* Rank를 통한 Find최적화 
  * 항상 높은 랭크에 셋을 붙이는 전략
* 집합을 표현하는 Parent 혹은 Root

#### 3). 코드

```cpp
struct DSetEl{
    int par = 0;
    int rank = 0;
}

DSetEl DSet[10] {0, }

void MakeSet() {
    for(int i = 1; i < 1010; i++) {
        DSet[i] = i;
        DSet[i] = 1;
    }
}

int FindSet(int x) {
    if(x == par[x]) return x;
    return par[x] = findSet(par[x]);
} 

void Union(int x, int y) {
    x = FindSet(x), y= FindSet(y);
    if(x == y) return ;
    if(rank[x] < rank[y])
        swap(x, y);

    par[y] = x; // 랭크 높은놈이 부모.

    if(rank[x] == rank[y])
        rank[x]++;
} 
```

#### 4). DisjointSet
```cpp
class DisjointSet {
private : 
    vector<int> mParent;
    vector<int> mRank;
public :
    DisjointSet(int N, int init){
        for(int i = init; i < N; i++){
            this->mParent.pushback(i);
            this->mRank.pushback(0);
        }
    }

    bool Equal(int p, int q){
        if(Find(p) == Find(q)) return true;
        return false;
    }

    int FindSet(int i) {
        if(i == this->mParent[i]) return i;
        return this->mParent[i] = FindSet(this->mParent[i]);
    }

    void Union(int p, int q) {
        p = FindSet(p); q = FindSet(q);
        if(p == q) return;
        if(this->mRank[p] < this->mRank[q]){swap(p, q);}
        this->mParent[q] = p;
        if(this->mRank[p] == this->mRank[q]){this->mRank[p]++;}
    }
};
```