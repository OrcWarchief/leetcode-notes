// 297. Serialize and Deserialize Binary Tree / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";

        string serial;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) 
        {
            TreeNode* cur = q.front(); q.pop();
            if (cur) 
            {
                serial += to_string(cur->val);
                serial.push_back(',');
                q.push(cur->left);
                q.push(cur->right);
            } 
            else 
            {
                serial += "null,";
            }
        }
        return serial;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return NULL;

        vector<string> tok;
        tok.reserve(data.size() / 2 + 1);
        string cur;
        for (char c : data) 
        {
            if (c == ',') 
            {
                tok.push_back(cur);
                cur.clear();
            } 
            else 
            {
                cur.push_back(c);
            }
        }
        if (!cur.empty()) tok.push_back(cur);

        if (tok.empty() || tok[0] == "null") return NULL;

        TreeNode* root = new TreeNode(stoi(tok[0]));
        queue<TreeNode*> q;
        q.push(root);

        int i = 1;
        while (!q.empty() && i < (int)tok.size()) 
        {
            TreeNode* node = q.front(); q.pop();

            if (i < (int)tok.size() && tok[i] != "null") 
            {
                node->left = new TreeNode(stoi(tok[i]));
                q.push(node->left);
            }
            ++i;

            if (i < (int)tok.size() && tok[i] != "null") 
            {
                node->right = new TreeNode(stoi(tok[i]));
                q.push(node->right);
            }
            ++i;
        }
        return root;
    }
};