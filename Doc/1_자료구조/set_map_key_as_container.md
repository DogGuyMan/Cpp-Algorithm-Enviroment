> ### 셋, 맵, 해시테이블 자료구조의 Key를 컨테이너 자료구조로 설정하기
* 의외로 컨테이너로 키를 만들어도 단 하나의 식별 해시 키를 가지게 된다.
    ```cpp
    set<vector<int>> s;
    map<vector<int>> m;
    ```