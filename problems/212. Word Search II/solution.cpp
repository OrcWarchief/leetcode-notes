// 212. Word Search II // solution.cpp
// Time: O(M*N*4^L)  |  Space: O(W * L)
#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* child[26]{};
    string word;
};
class Solution {
    Node* root = new Node();
    vector<string> ans;
    int R, C;

    void insert(string& s)
    {
        Node* cur = root;
        for (char& ch : s)
        {
            int i = ch - 'a';
            if (!cur->child[i]) cur->child[i] = new Node();
            cur = cur->child[i];
        }
        cur->word = s;
    }

    void dfs(vector<vector<char>>& board, int r, int c, Node* node)
    {
        char ch = board[r][c];
        if (ch == '#') return;
        Node* next = node->child[ch - 'a'];
        if (!next->word.empty())
        {
            ans.push_back(next->word);
            next->word.clear();
        }
        board[r][c] = '#';
        if (r > 0)     dfs(board, r - 1, c, next);
        if (c > 0)     dfs(board, r, c - 1, next);
        if (r + 1 < R) dfs(board, r + 1, c, next);
        if (c + 1 < C) dfs(board, r, c + 1, next);
        board[r][c] = ch;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for (auto& w : words) insert(w);
        R = board.size();
        C = board.empty() ? 0 : board[0].size();
        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                dfs(board, i, j, root);
            }
        }
        return ans;
    }
};