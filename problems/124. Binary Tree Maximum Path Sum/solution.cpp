// 124. Binary Tree Maximum Path Sum / solution.cpp
// Time: O(N)Where N Is The Number Of Nodes In The Tree  |  Space: O(H) Where H Is The Height Of The Tree
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int maxSum = 0;
    int maxPathSum(TreeNode* root) {
        maxSum = root->val;
        dfs(root);
        return maxSum;
    }

    int dfs(TreeNode* cur)
    {
        if (!cur) return 0;
        int sum = cur->val;
        int left = max(0, dfs(cur->left));
        int right = max(0, dfs(cur->right));
        maxSum = max(maxSum, left + right + cur->val);
        return cur->val + max(left, right);
    }
};