# LeetCode 98 ? Validate Binary Search Tree (BST 검증)

이 문제는 주어진 이진 트리가 **이진 검색 트리(BST)** 규칙을 만족하는지 판별하여 `true / false`를 **반환**하는 과제입니다.

---

## 문제 요약

- **입력** : `TreeNode* root` ? 루트 노드를 가리키는 포인터  
- **출력** : `bool` ? 트리가 유효한 BST이면 `true`, 아니면 `false`  
- **BST 규칙**  
  1. 모든 **왼쪽 서브트리**의 값 `<` 현재 노드의 값  
  2. 모든 **오른쪽 서브트리**의 값 `>` 현재 노드의 값  
  3. 각각의 서브트리 역시 BST

---

## 예시

| 입력 트리(레벨 순 배열) | 반환값 | 설명 |
|------------------------|--------|------|
| `[2,1,3]`              | `true` | 완전한 BST |
| `[5,1,4,null,null,3,6]`| `false`| 노드 4의 왼쪽 자식 3이 5보다 작음 ⇒ 규칙 위반 |

---

## 해결 전략

| 방법 | 핵심 아이디어 | 장·단점 |
|------|--------------|---------|
| **DFS 재귀 + 범위(min/max)** | 노드마다 `(low, high)` 허용 범위 전달<br>좌 : `(low, val)`, 우 : `(val, high)` | 코드 직관적, O(H) 스택 |
| **중위(In-order) 순회 + 직전 값 비교** | BST의 중위 순회 결과는 **엄격히 오름차순** | 반복·재귀 모두 가능, 코드 짧음 |
| **BFS(큐) + 범위 전파** | 노드와 함께 `(low, high)` 저장해 레벨 순회 | BFS 사고방식 선호 시 적합 |
| **스택 + 중위 반복** | 재귀 대신 명시적 스택 | 꼬리 재귀 제거, 메모리 제어 용이 |

> 단순 **부모-자식 값 비교만**으로는 손자·증손 단계에서의 오류를 놓칠 수 있으므로,  
> **범위 전파**(min/max) 또는 **중위 오름차순** 조건을 반드시 이용해야 합니다.

---

## 복잡도

| 방법 | 시간 | 공간 |
|------|------|------|
| 모든 방법 | `O(N)` | `O(H)` ? 트리 높이 (재귀 스택, 명시적 스택·큐) |

`N` = 노드 수, `H` = 트리 높이 (평균 `log N`, 최악 `N`)

---

## C++17 구현 예시

### 1. DFS 재귀 + 범위(min, max)

```cpp
#include <limits>

class Solution {
    bool valid(TreeNode* n, long long low, long long high) {
        if (!n) return true;
        if (n->val <= low || n->val >= high) return false;
        return valid(n->left,  low, n->val) &&
               valid(n->right, n->val, high);
    }
public:
    bool isValidBST(TreeNode* root) {
        using LL = long long;
        return valid(root,
                     std::numeric_limits<LL>::min(),
                     std::numeric_limits<LL>::max());
    }
};

### 2. 중위 순회(재귀)
class Solution {
    bool inorder(TreeNode* n, long long& prev, bool& first) {
        if (!n) return true;
        if (!inorder(n->left, prev, first)) return false;

        if (!first && n->val <= prev) return false;
        first = false;  prev = n->val;

        return inorder(n->right, prev, first);
    }
public:
    bool isValidBST(TreeNode* root) {
        long long prev = 0; bool first = true;
        return inorder(root, prev, first);
    }
};
3. BFS + 범위 전파
#include <queue>
#include <limits>

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        struct Item { TreeNode* n; long long low, high; };
        std::queue<Item> q;
        q.push({root,
                std::numeric_limits<long long>::min(),
                std::numeric_limits<long long>::max()});

        while (!q.empty()) {
            auto [n, low, high] = q.front(); q.pop();
            long long v = n->val;
            if (v <= low || v >= high) return false;

            if (n->left)  q.push({n->left,  low, v});
            if (n->right) q.push({n->right, v,   high});
        }
        return true;
    }
};
