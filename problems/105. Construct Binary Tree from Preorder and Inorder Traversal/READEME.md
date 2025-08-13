
# LeetCode 105 ? Construct Binary Tree from Preorder and Inorder Traversal (C++ Rewind)

> **�ٽ� �� ��**  
> **Preorder�� ��Ʈ�� ���̴� ������, Inorder�� ��Ʈ �������� ������/�������� ������ Į��**  
> �� Preorder �� ���� �׻� ���� ����Ʈ���� ��Ʈ�̰�, �� ���� Inorder���� ã�� **����/������ ����Ʈ�� ����**�� ���� ���(�Ǵ� ����)�� �����մϴ�.

---

## 0. ���� ���
- �Է�: `preorder`, `inorder` (��� �� **����ũ**)
- ���: �� �� ��ȸ�� �����ϴ� **����Ʈ���� ��Ʈ**
- ����: �׻� ��ȿ�� �Է��� �־����ٰ� ����(LeetCode)

---

## 1. ���̵�� (�� �����Ѱ�?)
- **Preorder:** `(root) �� left �� right`  
  ���� ������ ���� ����Ʈ���� **ù ���� ��Ʈ**.
- **Inorder:** `left �� (root) �� right`  
  ��Ʈ�� �ε����� **����/������ ����Ʈ���� ���**.

���� �� ����Ʈ������
1) Preorder���� **��Ʈ ��**�� �ϳ� ���� ��,
2) �� ���� Inorder���� ã�� **������ ��/��� ����**,
3) ���� ������ ��������� �ݺ��ϸ� ��ü Ʈ���� O(n)�� ����.

> **Tip:** Inorder �� �� �ε��� ��(`unordered_map`)�� �̸� �����, �� ��Ʈ�� ��ġ�� O(1)�� ã�� �� �־� ��ü�� O(n)�� �˴ϴ�.

---

## 2. �˰��� ����

### ��� (�������� Ǯ��)
- ����/��� `preIdx`�� Preorder���� **���� ��Ʈ**�� ����ŵ�ϴ�.
- `build(inL, inR)`�� Inorder�� ���� ���� `[inL, inR]`�� �ش��ϴ� ����Ʈ���� ����ϴ�.
  - ����: `inL > inR` �� `nullptr`
  - ����: `rootVal = preorder[preIdx++]`, `k = inPos[rootVal]`
  - ����: `[inL, k-1]`, ������: `[k+1, inR]`

### �ݺ�(����) ? ��� ����
- Preorder�� ��带 ����� **�������� �ִ��� ��������**��,
- ���� top�� ���� ���� Inorder ���� �������� �����鿡 **pop(pop��)** �ϸ� **������ �ڽ�**���� ��ȯ.
- �Һ���: ���ÿ��� ���� **������ ó���� ����** ��ΰ� �ö� �ֽ��ϴ�.

---

## 3. ���⵵
- �ð�: **O(n)** ? �� ���� �� ������ ���������, Inorder ��ġ ��ȸ�� O(1).
- ����: **O(n)** ? �ؽø� + ��� ����(�ݺ� Ǯ�̿��� ����� ����).

---

## 4. C++ ����

### 4.1 ��� Ǯ�� (����, ���� ����)
```cpp
#include <bits/stdc++.h>
using namespace std;

// LeetCode ȣȯ TreeNode
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r): val(x), left(l), right(r) {}
};

class Solution {
    unordered_map<int,int> inPos; // �� -> inorder �ε���
    int preIdx = 0;

    TreeNode* build(int inL, int inR, const vector<int>& preorder) {
        if (inL > inR) return nullptr;
        int rootVal = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootVal);
        int k = inPos[rootVal];         // inorder���� ��Ʈ ��ġ
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

### 4.2 �ݺ�(����) Ǯ�� (��� ���� ��� ��)
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

            // ���� inorder[inIdx]�� ���� ���̸� �������� ������
            if (node->val != inorder[inIdx]) {
                node->left = new TreeNode(val);
                st.push(node->left);
            } else {
                // inorder�� ���� top�� ������ ������ pop �� ���������� ��ȯ
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

## 5. Dry Run (���� ����)

�Է�  
`pre = [3, 9, 20, 15, 7]`  
`in  = [9, 3, 15, 20, 7]`

1) ��Ʈ=3 (pre[0]) �� Inorder���� `3`�� ���� `[9]` = �� ����Ʈ��, ������ `[15,20,7]` = ���� ����Ʈ��  
2) ���� Preorder �� `9`�� �ڵ����� ���� ��Ʈ �� �� ���� �Ұ�  
3) ������ ��Ʈ `20` �� Inorder���� `20`�� �� `[15]`, ���� `[7]`  
�� ���� ����

```
    3
   / \
  9  20
    /  \
   15   7
```

---

## 6. ���� �׽�Ʈ�� ������ (����)

> �Ʒ� ���Ϸ� ������ �ܵ� �����ϸ�, �籸���� Ʈ���� preorder/inorder�� �ٽ� �̾� **������ ��ġ**�ϴ��� Ȯ���մϴ�.

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

    // ���� ����
    cout << "preorder OK? " << boolalpha << (pre==pre2) << '\n';
    cout << "inorder  OK? " << boolalpha << (in==in2) << '\n';
    return 0;
}
```

**���� & ����**
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp && ./a.out
```

---

## 7. ���� �ϴ� �Ǽ� üũ����Ʈ
- [ ] `inPos`(�����ε���) ���� �� ���� O(n^2)�� ������  
- [ ] `preIdx` �ʱ�ȭ/������ ������  
- [ ] ��� ���� `[inL, inR]`���� off-by-one  
- [ ] �ߺ� �� ���(�� ��) ? ���� ������ **����ũ**  
- [ ] �߸��� �Է�(���� ����ġ/���� ����ġ) ? LeetCode�� ��ȿ ����, �Ϲ� ���� �� ���� �ʿ�

---

## 8. �ùٸ�(������ ����ġ)
- Preorder ù ���Ұ� ��Ʈ�̰�, Inorder���� �� ��ġ�� ��/�� ����Ʈ���� ������ ������.  
- ��/�� ����Ʈ���� ���� ���� ���� ��� �����ϸ� ������ Ʈ���� �����˴ϴ�(�� ����ũ).  
- �� �ܰ迡�� �迭�� **�������� �ʰ� �ε��� ����**�� �����ϸ� O(n)�� �����ϴ�.

---

## 9. Ȯ�� ���̵��
- `inorder + postorder`�� ���� ���̵��(��Ʈ�� postorder�� �� ��).  
- `preorder + postorder`�� **Full Binary Tree**(��� ���γ���� �ڽ� ��=2) ���ǿ����� ����.

---

## 10. ���� ������
```
root = preorder[preIdx++]
k = inIndex[root]
root.left  = build(inL, k-1)
root.right = build(k+1, inR)
```

�ʿ��ϸ� **�ݺ�(����) �ڵ�**, **Ʈ�� ��� ��ƿ**�� ���� ���Ϸ� �и��� �帱�Կ�.