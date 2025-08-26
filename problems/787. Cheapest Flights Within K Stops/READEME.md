# 787. Cheapest Flights Within K Stops ? README (KO)

## ���� ���
���� �׷������� �� �װ����� `flights[i] = [u, v, w]` (���� `u` �� `v`, ���� `w`)�� �־�����. 
����� `src`���� ������ `dst`���� **������(�߰� ����) ���� �ִ� `k`��** ���ϰ� �ǵ��� �̵��� ���� �ּ� ����� ���϶�. 
��ΰ� ������ `-1`�� ��ȯ�Ѵ�.

> **Note.** �������� `k`������ ��� ������ **���� ���� �ִ� `k+1`��**��� ���̴�.

## �ٽ� ����Ʈ
- ����ġ�� **���**�̹Ƿ� ���ͽ�Ʈ�� �������ε� Ǯ �� �ִ�.
- ������ �ٽ��� `stops �� k`�̸�, �̴� ����� ���� �� �� `k+1`���� ��ġ��.
- ���� ���̵�/������ �������� **Bellman?Ford�� ���� ���� ����**�� ���� �����ϰ� �����ϴ�.
- �켱���� ť�� ���� `(�������, ���, ��� ���� ��)`�� �����ϴ� **���ͽ�Ʈ�� ���̾��(leveled) Ǯ��**�� ȿ�����̴�.

## ����(LeetCode ���� ���)
- ���� �� `n`�� �뷫 100 ����.
- ���� `w`�� 0 �̻�(���/������).
- �ع��� ���� `O((k+1) * E)` �Ǵ� `O(E log(V(k+1)))`�� ��� ����.

---

## ���� 1) Bellman?Ford (k+1 ���常 ��ȭ)
**���̵��**: ��� ������ ���� ���� �ִ� `k+1`���̹Ƿ�, ���� ��ȭ�� **��Ȯ�� `k+1`��**�� �����Ѵ�.  
���� ���忡�� ���� ������ ��� �����ĵ��� �ʵ���, ������ �迭(`ndist`)�� ����Ѵ�.

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[src] = 0;

        // �ִ� k+1���� ���� ��� ���
        for (int i = 0; i <= k; ++i) {
            vector<int> ndist = dist;  // ������
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

**���⵵**: `O((k+1) * E)`, ���� `O(V)`  
**����**: ���� �ܼ�, ���� ����, �ڳ� ���̽��� ����  
**����**: ������ ���� �� �迭�� ���� ���� ���忡�� ������ ���� ���ĵǾ� **���� �� ������ ���߸� �� ����**.

---

## ���� 2) ���ͽ�Ʈ��(���̾��): ���¿� ����� ���� ������ ����
**���̵��**: `(���, ���, ��� ���� ��)`�� �켱���� ť�� �ִ´�.  
`dist[u][s] = s���� ������ ����� u�� �����ϴ� �ּҺ��`�� �����Ѵ�.

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e9;

        // ���� ����Ʈ: u -> (v, w)
        vector<vector<pair<int,int>>> adj(n);
        for (auto& f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }

        // dist[u][s] = s�� ������ �Ἥ u�� �����ϴ� �ּ� ��� (s: 0..k+1)
        vector<vector<int>> dist(n, vector<int>(k + 2, INF));
        dist[src][0] = 0;

        using State = tuple<int,int,int>; // (cost, u, usedEdges)
        priority_queue<State, vector<State>, greater<State>> pq;
        pq.push({0, src, 0});

        while (!pq.empty()) {
            auto [cost, u, used] = pq.top(); pq.pop();
            if (u == dst) return cost;       // ���� ���� = �ּ� ��� (min-heap Ư��)
            if (used == k + 1) continue;     // �� �̻� ���� ��� �Ұ�

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

**���⵵**: ���� ���� `V*(k+1)`�̹Ƿ� �뷫 `O(E log(V(k+1)))`, ���� `O(V*(k+1))`  
**����**: ���� BF���� ���� ��, ���� ���� ����(������ pop ��)  
**����**: `dist`�� 2�������� ���� ������ ���� ���� �ٸ� ���� ���¸� ����� ���� �߻� ����.

---

## (����) ť ��� ���� DP(BFS ��Ÿ��)
`dist[v][s]`�� �����ϸ�, ť���� `(���, ��� ���� ��)`�� �ΰ� **�ش� ����������** �����Ѵ�.  
������ Bellman?Ford�� ť �������� �� �� ������, ���� ������ �ȴ�.

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

## ���� �ϴ� �Ǽ� & ����� ��
1. **���� ��� �񱳸� ���߸�**  
   `price[next] > edgeWeight`ó�� **���� ���� ��븸** ���ϸ� ����.  
   �׻� `������� + edgeWeight`�� ���ؾ� �Ѵ�.

2. **���� �� ���� �ؼ� ����**  
   ������ `k`�� = **���� �� �� `k+1`**. (����/������ �ִ� ������ ���� 1��, ���� 0��)

3. **Bellman?Ford���� ������ �̻��**  
   �� ���� ������ ������ �ٽ� �ݿ��Ǹ�, ��ǻ� ���� �� ������ ��������.

4. **���ͽ�Ʈ�󿡼� 1���� dist ���**  
   ���� ���� �ٸ� ��ε��� �� ��Ŷ�� ��������� ������ ��ĥ �� �ִ�. `dist[v][used]`�� ����.

5. **ť/�켱���� ť�� ���ʿ��� ���� ���� Ǫ��**  
   �������� ���� ���/��� ���� �� ������ Ǫ�� ���� �ɷ�����(2D `dist` üũ).

6. **�����÷ο�/��Ƽ�� �Ǽ�**  
   `INF`�� `1e9`ó�� �˳���. `INF + w` ������ �ϱ� ���� `dist[u] == INF`���� ���� üũ.

---

## ���� �׽�Ʈ
�Ʒ��� ���� �׽�Ʈ�� ������ ���� ���̽����̴�.

```
n = 4, flights = [
  [0,1,100], [1,2,100], [0,2,500], [2,3,100], [1,3,600]
]
src = 0, dst = 3

k = 0  �� -1 (���� ����)
k = 1  �� 700 (0��2��3�� 2�������� stops=1 �ʰ�, 0��1��3 = 700)
k = 2  �� 300 (0��1��2��3 = 300)
k = 3  �� 300 (����)
```

---

## ���⵵ �� ���

| ���� | �ð� ���⵵ | ���� ���⵵ | ���� | ���� |
|---|---:|---:|---|---|
| Bellman?Ford (k+1 ����) | `O((k+1) * E)` | `O(V)` | ���� �ܼ�, ���� ���� | ������ �ʿ� |
| ���ͽ�Ʈ��(���̾��) | `O(E log(V(k+1)))` | `O(V*(k+1))` | ���� ������ ���� ���� | 2D dist �ʿ� |
| ���� DP(BFS ��Ÿ��) | `O((k+1) * E)` | `O(V*(k+1))` | ������, ���� ���� | ���� ������ ���� |

---

## ���� ��
- **������**�� ���� ���� ���� ���� ������ ��� �������.  
  ��: `int ncost = cost + w; int nused = used + 1;` �Ŀ� ����/Ǫ�ÿ� ���.
- �������� �����ϸ� **���ͽ�Ʈ��� ���� ����** ����(���� pop�� �ּ�).  
  Bellman?Ford/���� DP�� ���� ��ü ���带 ������ ���� �����ϴ�.
- `k = 0`�� ���� ��� �Է��� ���� �׽�Ʈ�غ���.