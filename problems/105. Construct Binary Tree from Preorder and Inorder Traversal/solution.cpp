// 105. Construct Binary Tree from Preorder and Inorder Traversal / solution.cpp
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
    unordered_map<int,int> inPos;
    int preIdx = 0;

    TreeNode* build(int inL, int inR, const vector<int>& preorder) {
        if (inL > inR) return nullptr;
        int rootVal = preorder[preIdx++];
        int k =inPos[rootVal];

        TreeNode* root = new TreeNode(rootVal);
        root->left  = build(inL, k - 1, preorder);
        root->right =build(k + 1, inR, preorder);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        inPos.reserve(inorder.size());
        inPos.clear();
        for (int i = 0; i < inorder.size(); i++)
        {
            inPos[inorder[i]] = i;
        }
        return build(0, inorder.size() - 1, preorder);
    }
};