
# LeetCode 105 ? Construct Binary Tree from Preorder and Inorder Traversal (C++ Rewind)

> **핵심 한 줄**  
> **Preorder는 루트를 “뽑는 순서”, Inorder는 루트 기준으로 “왼쪽/오른쪽을 가르는 칼”**  
> → Preorder 맨 앞이 항상 현재 서브트리의 루트이고, 그 값을 Inorder에서 찾아 **왼쪽/오른쪽 서브트리 구간**을 나눠 재귀(또는 스택)로 복원합니다.

---

## 0. 문제 요약
- 입력: `preorder`, `inorder` (노드 값 **유니크**)
- 출력: 이 두 순회를 만족하는 **이진트리의 루트**
- 전제: 항상 유효한 입력이 주어진다고 가정(LeetCode)

---

## 1. 아이디어 (왜 가능한가?)
- **Preorder:** `(root) → left → right`  
  아직 만들지 않은 서브트리의 **첫 값이 루트**.
- **Inorder:** `left → (root) → right`  
  루트의 인덱스가 **왼쪽/오른쪽 서브트리의 경계**.

따라서 각 서브트리마다
1) Preorder에서 **루트 값**을 하나 꺼낸 뒤,
2) 그 값을 Inorder에서 찾아 **구간을 좌/우로 분할**,
3) 같은 과정을 재귀적으로 반복하면 전체 트리를 O(n)에 복원.

> **Tip:** Inorder 값 → 인덱스 맵(`unordered_map`)을 미리 만들면, 각 루트의 위치를 O(1)에 찾을 수 있어 전체가 O(n)이 됩니다.

---

## 2. 알고리즘 개요

### 재귀 (전형적인 풀이)
- 전역/멤버 `preIdx`가 Preorder에서 **다음 루트**를 가리킵니다.
- `build(inL, inR)`는 Inorder의 닫힌 구간 `[inL, inR]`에 해당하는 서브트리를 만듭니다.
  - 종료: `inL > inR` → `nullptr`
  - 진행: `rootVal = preorder[preIdx++]`, `k = inPos[rootVal]`
  - 왼쪽: `[inL, k-1]`, 오른쪽: `[k+1, inR]`

### 반복(스택) ? 재귀 없이
- Preorder로 노드를 만들며 **왼쪽으로 최대한 내려가다**가,
- 스택 top의 값이 현재 Inorder 값과 같아지는 순간들에 **pop(pop…)** 하며 **오른쪽 자식**으로 전환.
- 불변식: 스택에는 아직 **오른쪽 처리를 남긴** 경로가 올라가 있습니다.

---

## 3. 복잡도
- 시간: **O(n)** ? 각 노드는 한 번씩만 만들어지고, Inorder 위치 조회는 O(1).
- 공간: **O(n)** ? 해시맵 + 재귀 스택(반복 풀이에선 명시적 스택).

---

## 4. C++ 구현

### 4.1 재귀 풀이 (권장, 가장 간결)
```cpp
#include <bits/stdc++.h>
using namespace std;

// LeetCode 호환 TreeNode
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r): val(x), left(l), right(r) {}
};

class Solution {
    unordered_map<int,int> inPos; // 값 -> inorder 인덱스
    int preIdx = 0;

    TreeNode* build(int inL, int inR, const vector<int>& preorder) {
        if (inL > inR) return nullptr;
        int rootVal = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootVal);
        int k = inPos[rootVal];         // inorder에서 루트 위치
        root->left  = build(inL, k - 1, preorder);
        root->right = build(k + 1, inR, preorder);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        inPos.clear();
        inPos.reserve(inorder.size());
        for (int i = 0; i < (int)inorder.size(); ++i) inPos[inorder[i]] = i;
        preIdx = 0;
        return build(0, (int)inorder.size() - 1, preorder);
    }
};
```

### 4.2 반복(스택) 풀이 (재귀 깊이 우려 시)
```cpp
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class SolutionIterative {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) return nullptr;

        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> st; st.push(root);
        int inIdx = 0;

        for (int i = 1; i < (int)preorder.size(); ++i) {
            int val = preorder[i];
            TreeNode* node = st.top();

            // 아직 inorder[inIdx]에 도달 전이면 왼쪽으로 내려감
            if (node->val != inorder[inIdx]) {
                node->left = new TreeNode(val);
                st.push(node->left);
            } else {
                // inorder와 스택 top가 같아질 때까지 pop → 오른쪽으로 전환
                while (!st.empty() && st.top()->val == inorder[inIdx]) {
                    node = st.top(); st.pop();
                    ++inIdx;
                }
                node->right = new TreeNode(val);
                st.push(node->right);
            }
        }
        return root;
    }
};
```

---

## 5. Dry Run (작은 예시)

입력  
`pre = [3, 9, 20, 15, 7]`  
`in  = [9, 3, 15, 20, 7]`

1) 루트=3 (pre[0]) → Inorder에서 `3`의 왼쪽 `[9]` = 왼 서브트리, 오른쪽 `[15,20,7]` = 오른 서브트리  
2) 다음 Preorder 값 `9`는 자동으로 왼쪽 루트 → 더 분할 불가  
3) 오른쪽 루트 `20` → Inorder에서 `20`의 왼 `[15]`, 오른 `[7]`  
→ 최종 구조

```
    3
   / \
  9  20
    /  \
   15   7
```

---

## 6. 로컬 테스트용 스니펫 (선택)

> 아래 파일로 저장해 단독 실행하면, 재구성된 트리의 preorder/inorder를 다시 뽑아 **원본과 일치**하는지 확인합니다.

```cpp
// file: main.cpp
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val; TreeNode *left; TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r): val(x), left(l), right(r) {}
};

class Solution {
    unordered_map<int,int> inPos; int preIdx = 0;
    TreeNode* build(int L, int R, const vector<int>& pre){
        if (L > R) return nullptr;
        TreeNode* root = new TreeNode(pre[preIdx++]);
        int k = inPos[root->val];
        root->left  = build(L, k-1, pre);
        root->right = build(k+1, R, pre);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
        inPos.clear(); inPos.reserve(inorder.size());
        for (int i = 0; i < (int)inorder.size(); ++i) inPos[inorder[i]] = i;
        preIdx = 0;
        return build(0, (int)inorder.size()-1, preorder);
    }
};

void preorderTrav(TreeNode* r, vector<int>& out){
    if(!r) return; out.push_back(r->val); preorderTrav(r->left,out); preorderTrav(r->right,out);
}
void inorderTrav(TreeNode* r, vector<int>& out){
    if(!r) return; inorderTrav(r->left,out); out.push_back(r->val); inorderTrav(r->right,out);
}

int main(){
    vector<int> pre = {3,9,20,15,7};
    vector<int> in  = {9,3,15,20,7};

    Solution sol;
    TreeNode* root = sol.buildTree(pre, in);

    vector<int> pre2, in2;
    preorderTrav(root, pre2);
    inorderTrav(root, in2);

    cout << "preorder: ";
    for (int x: pre2) cout << x << ' '; cout << '\n';
    cout << "inorder : ";
    for (int x: in2) cout << x << ' '; cout << '\n';

    // 간단 검증
    cout << "preorder OK? " << boolalpha << (pre==pre2) << '\n';
    cout << "inorder  OK? " << boolalpha << (in==in2) << '\n';
    return 0;
}
```

**빌드 & 실행**
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp && ./a.out
```

---

## 7. 자주 하는 실수 체크리스트
- [ ] `inPos`(값→인덱스) 맵을 안 만들어서 O(n^2)로 느려짐  
- [ ] `preIdx` 초기화/증가를 깜빡함  
- [ ] 재귀 구간 `[inL, inR]`에서 off-by-one  
- [ ] 중복 값 허용(안 됨) ? 문제 전제는 **유니크**  
- [ ] 잘못된 입력(길이 불일치/원소 불일치) ? LeetCode는 유효 보장, 일반 구현 시 검증 필요

---

## 8. 올바름(직관적 스케치)
- Preorder 첫 원소가 루트이고, Inorder에서 그 위치는 좌/우 서브트리의 유일한 분할점.  
- 좌/우 서브트리에 대해 같은 논리를 재귀 적용하면 유일한 트리가 구성됩니다(값 유니크).  
- 각 단계에서 배열을 **복사하지 않고 인덱스 범위**만 전달하면 O(n)로 끝납니다.

---

## 9. 확장 아이디어
- `inorder + postorder`도 동일 아이디어(루트가 postorder의 맨 뒤).  
- `preorder + postorder`는 **Full Binary Tree**(모든 내부노드의 자식 수=2) 조건에서만 유일.

---

## 10. 기억용 스니펫
```
root = preorder[preIdx++]
k = inIndex[root]
root.left  = build(inL, k-1)
root.right = build(k+1, inR)
```

필요하면 **반복(스택) 코드**, **트리 출력 유틸**도 별도 파일로 분리해 드릴게요.