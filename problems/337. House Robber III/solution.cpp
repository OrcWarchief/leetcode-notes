// 337. House Robber III/ solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
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

    unordered_map<TreeNode*, int> memoRob;
    unordered_map<TreeNode*, int> memoNot;

    int Rob(TreeNode* node) 
    {
        if (node == nullptr) return 0;
        if (auto it = memoRob.find(node); it != memoRob.end()) return it->second;

        int left  = NotRob(node->left);
        int right = NotRob(node->right);
        int ans = node->val + left + right;

        memoRob[node] = ans;
        return ans;
    }

    int NotRob(TreeNode* node) 
    {
        if (node == nullptr) return 0;
        if (auto it = memoNot.find(node); it != memoNot.end()) return it->second;

        int leftBest  = max(Rob(node->left),  NotRob(node->left));
        int rightBest = max(Rob(node->right), NotRob(node->right));
        int ans = leftBest + rightBest;

        memoNot[node] = ans;
        return ans;
    }

    int rob(TreeNode* root) {
        return max(Rob(root), NotRob(root));
    }
};