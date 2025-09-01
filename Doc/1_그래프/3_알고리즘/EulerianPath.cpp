#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class EulerianCircuit {
        /*********************************************************************************
        *
        * 간선이 있다 없다를 0, 1로 표현했다면
        * 이번에는 간선이 몇개 있는지를 1~INT.MAX 까지 넣는식으로도 가능하다.
        * 즉, A에서 B로 가는 간선이 INF개 있다고도 할 수 있지.
        *
        *********************************************************************************/
        int N = 0;
        int G[1010][1010] = {0, };
        
        /*********************************************************************************
        *
        * DFS가 맞지만, 대신 조금 다른것은 IsVisit처리를 하지 않는것을 할 수 있다.
        * 그 이유는 G[cur][nxt]가 처리를 해주기 떄문이다.
        *
        *********************************************************************************/
        void DFS(int cur, vector<int>& circuit) {
                for(int nxt = 0; nxt < N; nxt++) {
                        HandleEulerCircuit(cur, nxt, circuit, &EulerianCircuit::DFS);
                }
                circuit.push_back(cur);
        }

        /*********************************************************************************
        *
        * 오일러 서킷이 DFS를 수행할때마다 해야하는 작업
        *
        *********************************************************************************/
        void HandleEulerCircuit(int cur, int nxt, vector<int>&circuit, 
                        void (EulerianCircuit::*dfs) (int, vector<int>&)) {
                while(G[cur][nxt] > 0) {
                        G[cur][nxt]--;
                        G[nxt][cur]--;
                        (this->*dfs)(nxt, circuit);
                }
        }
};

class EulerianPath {

};
