정보 기반 길찾기도 될 것 같은데..
그리디 방식이든, 다익스트라든.

> ### 결론은 다익스트라를 사용한다 하더라도, 가중치가 1이라 별 효능이 없다.

#### 선택 가이드

* 테스트가 많고 보드가 큼: **양방향 BFS**가 구현 간단·효율 좋음.
* 시작·끝이 멀고 빈칸 많음: **A***가 확장 노드 수를 더 줄일 수 있음.
* 다익스트라: 가중치 1이면 **BFS와 동일**, 이득 없음.

#### 1). 양방향 BFS (권장)

아이디어: 시작·도착 양쪽에서 동시에 BFS. 두 탐색이 만나는 순간 `distS+distT`가 답. 평균 확장 노드 수가 (b^{d/2})로 감소.

```cpp
#include <bits/stdc++.h>
using namespace std;
int dy[8]={2,1,-2,-1,2,1,-2,-1}, dx[8]={1,2,1,2,-1,-2,-1,-2};

int biBFS(int L, pair<int,int> s, pair<int,int> t){
    if(s==t) return 0;
    vector<vector<int>> ds(L, vector<int>(L, -1)), dt=ds;
    queue<pair<int,int>> qs, qt;
    ds[s.first][s.second]=0; qs.push(s);
    dt[t.first][t.second]=0; qt.push(t);

    auto step=[&](queue<pair<int,int>>& q, vector<vector<int>>& dself,
                  vector<vector<int>>& dother)->int{
        int qsz=q.size();
        while(qsz--){
            auto [y,x]=q.front(); q.pop();
            for(int k=0;k<8;k++){
                int ny=y+dy[k], nx=x+dx[k];
                if(ny<0||ny>=L||nx<0||nx>=L) continue;
                if(dself[ny][nx]!=-1) continue;
                dself[ny][nx]=dself[y][x]+1;
                if(dother[ny][nx]!=-1) return dself[ny][nx]+dother[ny][nx];
                q.push({ny,nx});
            }
        }
        return -1;
    };

    while(!qs.empty() || !qt.empty()){
        if(!qs.empty()){
            int got=step(qs, ds, dt);
            if(got!=-1) return got;
        }
        if(!qt.empty()){
            int got=step(qt, dt, ds);
            if(got!=-1) return got;
        }
    }
    return -1; // unreachable 없음(문제 특성상)
}
```

#### 2). A* with admissible heuristic

아이디어: 휴리스틱 (h)로 우선순위 (f=g+h). 나이트 최소 이동의 **무한 보드 정답식**은 **하한**이므로 유효한 휴리스틱(과소평가)이다.

```cpp
#include <bits/stdc++.h>
using namespace std;
int dy[8]={2,1,-2,-1,2,1,-2,-1}, dx[8]={1,2,1,2,-1,-2,-1,-2};

int knight_heur(int y,int x,int ty,int tx){
    int dx0=abs(x-tx), dy0=abs(y-ty);
    if(dx0<dy0) swap(dx0,dy0);
    if(dx0==1 && dy0==0) return 3;
    if(dx0==2 && dy0==2) return 4;
    int d = max((dx0+1)/2, (dx0+dy0+2)/3);
    if( (d&1) != ((dx0+dy0)&1) ) d++; // parity 보정
    return d;
}

int astar(int L, pair<int,int> s, pair<int,int> t){
    if(s==t) return 0;
    vector<vector<int>> dist(L, vector<int>(L, INT_MAX));
    using Node = tuple<int,int,int,int>; // f,g,y,x
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int h = knight_heur(s.first,s.second,t.first,t.second);
    dist[s.first][s.second]=0;
    pq.push({h,0,s.first,s.second});
    while(!pq.empty()){
        auto [f,g,y,x]=pq.top(); pq.pop();
        if(make_pair(y,x)==t) return g;
        if(g!=dist[y][x]) continue;
        for(int k=0;k<8;k++){
            int ny=y+dy[k], nx=x+dx[k];
            if(ny<0||ny>=L||nx<0||nx>=L) continue;
            int ng=g+1;
            if(ng<dist[ny][nx]){
                dist[ny][nx]=ng;
                int nf=ng+knight_heur(ny,nx,t.first,t.second);
                pq.push({nf,ng,ny,nx});
            }
        }
    }
    return -1;
}
```