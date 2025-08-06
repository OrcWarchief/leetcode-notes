// 269. Alien Dictionary / solution.cpp
// Time: O()  |  Space: O()
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        
        vector<vector<int>> adj(26);
        vector<int> indeg(26, 0);
        vector<bool> present(26, false);

        for (auto &w : words)
            for (char c : w) present[c - 'a'] = true;

        for (int i = 1; i < words.size(); ++i)
        {
            string &prev = words[i - 1], &cur = words[i];
            int j = 0, mn = min(prev.size(), cur.size());
            while (j < mn && prev[j] == cur[j]) j++;

            if (j == mn) {
                if (prev.size() > cur.size()) return "";
                continue;
            }
            int a = prev[j] - 'a';
            int b = cur[j] - 'a';
            adj[a].push_back(b);
            ++indeg[b];
        }

        queue<int> q;
        for (int i = 0; i < 26; i++)
        {
            if (present[i] && indeg[i] == 0) q.push(i);
        }

        string order;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            order.push_back(char(u + 'a'));
            for (int n :adj[u])
            {
                if (--indeg[n] == 0) q.push(n);
            }
        }
        
        int total = count(present.begin(), present.end(), true);
        return (order.size() == total) ? order : "";
    }
};
