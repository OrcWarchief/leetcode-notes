# 787. Cheapest Flights Within K Stops ? README (KO)

## 문제 요약
방향 그래프에서 각 항공편은 `flights[i] = [u, v, w]` (도시 `u` → `v`, 가격 `w`)로 주어진다. 
출발지 `src`에서 목적지 `dst`까지 **경유지(중간 도시) 수가 최대 `k`개** 이하가 되도록 이동할 때의 최소 비용을 구하라. 
경로가 없으면 `-1`을 반환한다.

> **Note.** “경유지 `k`개”는 사용 가능한 **간선 수가 최대 `k+1`개**라는 뜻이다.

## 핵심 포인트
- 가중치가 **양수**이므로 다익스트라 변형으로도 풀 수 있다.
- 제약의 핵심은 `stops ≤ k`이며, 이는 “사용 간선 수 ≤ `k+1`”와 동치다.
- 구현 난이도/안정성 관점에서 **Bellman?Ford의 제한 라운드 버전**이 가장 간단하고 안전하다.
- 우선순위 큐로 상태 `(누적비용, 노드, 사용 간선 수)`를 관리하는 **다익스트라 레이어드(leveled) 풀이**도 효율적이다.

## 제약(LeetCode 기준 요약)
- 도시 수 `n`은 대략 100 이하.
- 가격 `w`는 0 이상(양수/비음수).
- 해법은 보통 `O((k+1) * E)` 또는 `O(E log(V(k+1)))`로 통과 가능.

---

## 접근 1) Bellman?Ford (k+1 라운드만 완화)
**아이디어**: 사용 가능한 간선 수가 최대 `k+1`개이므로, 간선 완화를 **정확히 `k+1`번**만 수행한다.  
동일 라운드에서 생긴 갱신이 즉시 재전파되지 않도록, 스냅샷 배열(`ndist`)을 사용한다.

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[src] = 0;

        // 최대 k+1개의 간선 사용 허용
        for (int i = 0; i <= k; ++i) {
            vector<int> ndist = dist;  // 스냅샷
            for (const auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] == INF) continue;
                if (ndist[v] > dist[u] + w) {
                    ndist[v] = dist[u] + w;
                }
            }
            dist.swap(ndist);
        }
        return dist[dst] == INF ? -1 : dist[dst];
    }
};
```

**복잡도**: `O((k+1) * E)`, 공간 `O(V)`  
**장점**: 구현 단순, 정답 보장, 코너 케이스에 강함  
**주의**: 스냅샷 없이 한 배열만 쓰면 같은 라운드에서 갱신이 연쇄 전파되어 **간선 수 제한을 깨뜨릴 수 있음**.

---

## 접근 2) 다익스트라(레이어드): 상태에 ‘사용 간선 수’를 포함
**아이디어**: `(비용, 노드, 사용 간선 수)`를 우선순위 큐에 넣는다.  
`dist[u][s] = s개의 간선을 사용해 u에 도달하는 최소비용`을 관리한다.

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e9;

        // 인접 리스트: u -> (v, w)
        vector<vector<pair<int,int>>> adj(n);
        for (auto& f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }

        // dist[u][s] = s개 간선을 써서 u에 도달하는 최소 비용 (s: 0..k+1)
        vector<vector<int>> dist(n, vector<int>(k + 2, INF));
        dist[src][0] = 0;

        using State = tuple<int,int,int>; // (cost, u, usedEdges)
        priority_queue<State, vector<State>, greater<State>> pq;
        pq.push({0, src, 0});

        while (!pq.empty()) {
            auto [cost, u, used] = pq.top(); pq.pop();
            if (u == dst) return cost;       // 최초 도착 = 최소 비용 (min-heap 특성)
            if (used == k + 1) continue;     // 더 이상 간선 사용 불가

            for (auto [v, w] : adj[u]) {
                int ncost = cost + w;
                int nused = used + 1;
                if (ncost < dist[v][nused]) {
                    dist[v][nused] = ncost;
                    pq.push({ncost, v, nused});
                }
            }
        }
        return -1;
    }
};
```

**복잡도**: 상태 수가 `V*(k+1)`이므로 대략 `O(E log(V(k+1)))`, 공간 `O(V*(k+1))`  
**장점**: 보통 BF보다 빠른 편, 조기 종료 가능(목적지 pop 시)  
**주의**: `dist`를 2차원으로 두지 않으면 경유 수가 다른 최적 상태를 덮어써 오답 발생 가능.

---

## (참고) 큐 기반 레벨 DP(BFS 스타일)
`dist[v][s]`를 유지하며, 큐에는 `(노드, 사용 간선 수)`만 두고 **해당 레벨에서만** 전파한다.  
구현은 Bellman?Ford의 큐 버전으로 볼 수 있으며, 정답 보장이 된다.

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e9;

        vector<vector<pair<int,int>>> adj(n);
        for (auto &f : flights) adj[f[0]].push_back({f[1], f[2]});

        vector<vector<int>> dist(n, vector<int>(k + 2, INF));
        dist[src][0] = 0;

        queue<pair<int,int>> q; // (u, usedEdges)
        q.push({src, 0});

        while (!q.empty()) {
            auto [u, used] = q.front(); q.pop();
            if (used == k + 1) continue;

            for (auto [v, w] : adj[u]) {
                if (dist[u][used] == INF) continue;
                int ncost = dist[u][used] + w;
                if (ncost < dist[v][used + 1]) {
                    dist[v][used + 1] = ncost;
                    q.push({v, used + 1});
                }
            }
        }

        int ans = *min_element(dist[dst].begin(), dist[dst].end());
        return ans == INF ? -1 : ans;
    }
};
```

---

## 자주 하는 실수 & 디버깅 팁
1. **누적 비용 비교를 빠뜨림**  
   `price[next] > edgeWeight`처럼 **단일 간선 비용만** 비교하면 오답.  
   항상 `누적비용 + edgeWeight`로 비교해야 한다.

2. **경유 수 제한 해석 오류**  
   “경유 `k`” = **간선 수 ≤ `k+1`**. (시작/도착만 있는 직행은 간선 1개, 경유 0개)

3. **Bellman?Ford에서 스냅샷 미사용**  
   한 라운드 내에서 갱신이 다시 반영되면, 사실상 간선 수 제한이 무너진다.

4. **다익스트라에서 1차원 dist 사용**  
   경유 수가 다른 경로들을 한 버킷에 섞어버리면 최적을 놓칠 수 있다. `dist[v][used]`로 관리.

5. **큐/우선순위 큐에 불필요한 상태 과도 푸시**  
   이전보다 나쁜 비용/사용 간선 수 조합은 푸시 전에 걸러내자(2D `dist` 체크).

6. **오버플로우/센티넬 실수**  
   `INF`는 `1e9`처럼 넉넉히. `INF + w` 연산을 하기 전에 `dist[u] == INF`인지 먼저 체크.

---

## 예시 테스트
아래는 수기 테스트에 유용한 간단 케이스들이다.

```
n = 4, flights = [
  [0,1,100], [1,2,100], [0,2,500], [2,3,100], [1,3,600]
]
src = 0, dst = 3

k = 0  → -1 (직행 없음)
k = 1  → 700 (0→2→3은 2간선으로 stops=1 초과, 0→1→3 = 700)
k = 2  → 300 (0→1→2→3 = 300)
k = 3  → 300 (같음)
```

---

## 복잡도 비교 요약

| 접근 | 시간 복잡도 | 공간 복잡도 | 장점 | 주의 |
|---|---:|---:|---|---|
| Bellman?Ford (k+1 라운드) | `O((k+1) * E)` | `O(V)` | 구현 단순, 정답 보장 | 스냅샷 필요 |
| 다익스트라(레이어드) | `O(E log(V(k+1)))` | `O(V*(k+1))` | 보통 빠르고 조기 종료 | 2D dist 필요 |
| 레벨 DP(BFS 스타일) | `O((k+1) * E)` | `O(V*(k+1))` | 직관적, 정답 보장 | 구현 디테일 주의 |

---

## 구현 팁
- **가독성**을 위해 계산된 값은 지역 변수에 담아 사용하자.  
  예: `int ncost = cost + w; int nused = used + 1;` 후에 조건/푸시에 사용.
- 목적지에 도달하면 **다익스트라는 조기 종료** 가능(최초 pop이 최소).  
  Bellman?Ford/레벨 DP는 보통 전체 라운드를 돌리는 편이 안전하다.
- `k = 0`과 같은 경계 입력을 별도 테스트해보자.