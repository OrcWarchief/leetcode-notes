// 0102_Binary Tree Level Order Traversal / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
         vector<vector<int>> result;
        if (root == nullptr) return result;

        queue<TreeNode*> curQ;
        queue<TreeNode*> nextQ;
        curQ.push(root);

        vector<int> levelVals;

        while (!curQ.empty()) {
            TreeNode* node = curQ.front();
            curQ.pop();
            levelVals.push_back(node->val);

            if (node->left)  nextQ.push(node->left);
            if (node->right) nextQ.push(node->right);

            // ���� ������ ������ ��
            if (curQ.empty()) {
                result.push_back(move(levelVals));     // �� ����
                levelVals.clear();                      // ���� ����
                swap(curQ, nextQ);                      // ���� ������ �̵�
            }
        }
        return result;
    }
};
