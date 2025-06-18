# LeetCode 98 ? Validate Binary Search Tree (BST ����)

�� ������ �־��� ���� Ʈ���� **���� �˻� Ʈ��(BST)** ��Ģ�� �����ϴ��� �Ǻ��Ͽ� `true / false`�� **��ȯ**�ϴ� �����Դϴ�.

---

## ���� ���

- **�Է�** : `TreeNode* root` ? ��Ʈ ��带 ����Ű�� ������  
- **���** : `bool` ? Ʈ���� ��ȿ�� BST�̸� `true`, �ƴϸ� `false`  
- **BST ��Ģ**  
  1. ��� **���� ����Ʈ��**�� �� `<` ���� ����� ��  
  2. ��� **������ ����Ʈ��**�� �� `>` ���� ����� ��  
  3. ������ ����Ʈ�� ���� BST

---

## ����

| �Է� Ʈ��(���� �� �迭) | ��ȯ�� | ���� |
|------------------------|--------|------|
| `[2,1,3]`              | `true` | ������ BST |
| `[5,1,4,null,null,3,6]`| `false`| ��� 4�� ���� �ڽ� 3�� 5���� ���� �� ��Ģ ���� |

---

## �ذ� ����

| ��� | �ٽ� ���̵�� | �塤���� |
|------|--------------|---------|
| **DFS ��� + ����(min/max)** | ��帶�� `(low, high)` ��� ���� ����<br>�� : `(low, val)`, �� : `(val, high)` | �ڵ� ������, O(H) ���� |
| **����(In-order) ��ȸ + ���� �� ��** | BST�� ���� ��ȸ ����� **������ ��������** | �ݺ������ ��� ����, �ڵ� ª�� |
| **BFS(ť) + ���� ����** | ���� �Բ� `(low, high)` ������ ���� ��ȸ | BFS ����� ��ȣ �� ���� |
| **���� + ���� �ݺ�** | ��� ��� ����� ���� | ���� ��� ����, �޸� ���� ���� |

> �ܼ� **�θ�-�ڽ� �� �񱳸�**���δ� ���ڡ����� �ܰ迡���� ������ ��ĥ �� �����Ƿ�,  
> **���� ����**(min/max) �Ǵ� **���� ��������** ������ �ݵ�� �̿��ؾ� �մϴ�.

---

## ���⵵

| ��� | �ð� | ���� |
|------|------|------|
| ��� ��� | `O(N)` | `O(H)` ? Ʈ�� ���� (��� ����, ����� ���á�ť) |

`N` = ��� ��, `H` = Ʈ�� ���� (��� `log N`, �־� `N`)

---

## C++17 ���� ����

### 1. DFS ��� + ����(min, max)

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

### 2. ���� ��ȸ(���)
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
3. BFS + ���� ����
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
