# LeetCode?207 ? Course?Schedule

**TL;DR**??Use topological sort (Kahn¡¯s BFS) or DFS?coloring to detect cycles in the prerequisite graph.?If no cycle exists, every course can be completed.?Both methods run in **O(V?+?E)** time and **O(V?+?E)** space, where *V*?=?number of courses and *E*?=?number of prerequisite pairs.

---

## 1. Problem Statement

> Given `numCourses` and a list `prerequisites` where `prerequisites[i] = [a,?b]` means *b*?must be taken before *a*, return `true`?if it is possible to finish all courses, otherwise `false`.

Equivalent to asking if a directed graph is **acyclic**.

---

## 2. Graph?Model

* **Vertices:** `0?¡¦?numCourses???1` (each course).
* **Directed edges:** `b?¡æ?a` for every prerequisite pair `[a,?b]`.
* Detecting **any** directed cycle ¢¡ impossible to finish.

---

## 3. Algorithm?1???BFS?Topological?Sort (Kahn)

1. Build adjacency list `adj[b].push_back(a)` and indegree array `indeg[a]++`.
2. Push all vertices with `indeg ==?0` into a queue.
3. Pop queue:

   * Append `u` to an `order` list (topological order).
   * Decrease indegree of each neighbor `v`.
   * If `indeg[v]` becomes?0, push `v`.
4. **If** `order.size() == numCourses` ¡æ no cycle ¡æ `true`; else `false`.

### C++?Reference Implementation

```cpp
bool canFinish(int numCourses, const vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indeg(numCourses, 0);
    for (const auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        ++indeg[p[0]];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (indeg[i] == 0) q.push(i);

    int visited = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        ++visited;
        for (int nxt : adj[cur])
            if (--indeg[nxt] == 0)
                q.push(nxt);
    }
    return visited == numCourses;
}
```

---

## 4. Algorithm?2???DFS?with?Three?Color?Marking

* `state[v] = 0`?(unvisited), `1`?(visiting), `2`?(done).
* DFS from every node:

  * If we encounter a `visiting` node again, a cycle exists.
* Stop early when a cycle is found.

### Python Reference Implementation

```python
from collections import defaultdict

def canFinish(numCourses, prerequisites):
    graph = defaultdict(list)
    for a, b in prerequisites:
        graph[b].append(a)

    state = [0] * numCourses  # 0=unvisited,1=visiting,2=done

    def dfs(v):
        if state[v] == 1:
            return False       # cycle
        if state[v] == 2:
            return True
        state[v] = 1
        for nxt in graph[v]:
            if not dfs(nxt):
                return False
        state[v] = 2
        return True

    return all(dfs(i) for i in range(numCourses))
```

---

## 5. Complexity Analysis

| Method       | Time       | Space      |
| ------------ | ---------- | ---------- |
| BFS (Kahn)   | `O(V?+?E)` | `O(V?+?E)` |
| DFS?Coloring | `O(V?+?E)` | `O(V?+?E)` |

---

## 6. Edge?Cases & Tips

* **Self?loop** `[a,?a]` immediately forms a cycle.
* Multiple identical pairs do **not** affect correctness but inflate memory.
* When `numCourses == 1` or `prerequisites` is empty, answer is always?`true`.

---

## 7. Testing

| Input                                   | Expected |
| --------------------------------------- | -------- |
| `numCourses = 2`, `[[1,0]]`             | `true`   |
| `numCourses = 2`, `[[1,0],[0,1]]`       | `false`  |
| `numCourses = 3`, `[[0,1],[1,2],[2,0]]` | `false`  |
| `numCourses = 5`, `[]`                  | `true`   |

---

## 8. How?to?Run (C++)

```bash
g++ -std=c++17 main.cpp -o course_schedule
./course_schedule < input.txt
```

---

## 9. Further Reading

* LeetCode?official discussion board.
* CLRS, *Section?22.4?Topological Sort*.

---

Happy coding!
