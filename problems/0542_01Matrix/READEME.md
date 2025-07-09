# 01?매트릭스 (LeetCode?542)

## 문제 설명

`n?×?m` 크기의 이진 행렬?`mat`이 주어질 때, 각 칸?`(i,?j)`에서 **가장 가까운?0**까지의 맨해튼 거리를 저장한 행렬?`dist`를 반환합니다.

```
입력  : [[0,0,0],
         [0,1,0],
         [1,1,1]]
출력  : [[0,0,0],
         [0,1,0],
         [1,2,1]]
```

---

## 알고리즘 접근법

| 방법              | 핵심 아이디어                                                      | 시간복잡도| 공간복잡도 |
| --------------    | ---------------------------------------------                   | -------- | -------- |
| **다중 BFS**      | 0?이 있는 모든 칸을 동시에 BFS?시작점으로 넣고, 네 방향으로 레이어별 확산 | `O(N·M)` | `O(N·M)` |
| **2?패스 DP 스캔** | ↖?방향, ↘?방향 두 번의 스캔으로 모든 간선을 한 번씩?relax            | `O(N·M)` | `O(N·M)` |

### 1. 다중?BFS?(가장 직관적)

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat){
    int n = mat.size(), m = n ? mat[0].size() : 0;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q;
    constexpr int dx[4] = {1,-1,0,0};
    constexpr int dy[4] = {0,0,1,-1};

    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(mat[i][j]==0){
                dist[i][j]=0;
                q.emplace(i,j);
            }

    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        for(int d=0; d<4; ++d){
            int nx = x + dx[d], ny = y + dy[d];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.emplace(nx,ny);
        }
    }
    return dist;
}
```

### 2. 2?패스 DP 스캔

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat){
    int n = mat.size(), m = n ? mat[0].size() : 0;
    const int INF = n + m + 5;          // 충분히 큰 값
    vector<vector<int>> dist(n, vector<int>(m, INF));

    // 1) ↖?방향 (위·왼쪽)
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j){
            if(mat[i][j]==0){ dist[i][j]=0; continue; }
            if(i) dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
            if(j) dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
        }

    // 2) ↘?방향 (아래·오른쪽)
    for(int i=n-1;i>=0;--i)
        for(int j=m-1;j>=0;--j){
            if(i+1 < n) dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
            if(j+1 < m) dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
        }
    return dist;
}
```

#### 최적성 증명 요약

* **첫 번째 스캔**: 위·왼쪽에서 오는 경로를 모두 고려.
* **두 번째 스캔**: 아래·오른쪽에서 오는 경로를 추가로 고려.
* 네 방향 간선이 정확히 한 번씩 relax 되므로, 단위 가중치 격자에서 최단 거리가 확정됩니다.

---

## 빌드 & 실행

```bash
# C++17 필요
g++ -std=c++17 update_matrix.cpp -o update_matrix
./update_matrix < input.txt > output.txt
```

### 입력 형식

1. 첫 줄: `n m`?(행, 열)
2. 다음?`n`줄: 공백으로 구분된?`m`개의 0/1

### 예시

```
3 3
0 0 0
0 1 0
1 1 1
```

출력

```
0 0 0
0 1 0
1 2 1
```

---

## 테스트 케이스 제안

1. 모든 칸이 0
2. 모든 칸이 1
3. `1×1`, `1×N`, `N×1` 경계 사례
4. 랜덤 80×80 행렬 (대형 입력)

---

## 복잡도 요약

* **시간**: `O(N·M)`
* **공간**: `O(N·M)` (입력?`mat`을 재활용하면 추가 공간?`O(1)`)

---

## 참고 문헌

* LeetCode?542 ? *01 Matrix*
* CLRS?§22.2 ? Breadth?First Search

---

??2025?Ryu?Soungmin.?MIT?License