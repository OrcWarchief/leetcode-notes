// 0098_validate-BST / solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
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
    bool recur(TreeNode* node, int min, int max) {
        if (!node) return true;
        if (node->val <= min || node->val >= max) return false;
        return recur(node->left, min, node->val) && recur(node->right, node->val, max);
    }
    bool isValidBST(TreeNode* root) {
        return recur(root, numeric_limits<int>::min(), numeric_limits<int>::max());
    }
};