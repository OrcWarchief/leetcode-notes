// 1462. Course Schedule IV / solution.cpp
// Time: O((N + E) * (N / w))  |  Space: O((N^2 / w ) + (N+E))
#include <bits/stdc++.h>
#include <bitset>
#include <array>
using namespace std;

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> adj(numCourses);
        vector<int> indeg(numCourses);

        for (auto& pre : prerequisites)
        {
            int u = pre[0], v = pre[1];
            adj[u].push_back(v);
            indeg[v]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (indeg[i] == 0) q.push(i);
        }

        vector<int> topo; topo.reserve(numCourses);
        while (!q.empty())
        {
            int cur = q.front(); q.pop();
            topo.push_back(cur);
            for (int& nxt : adj[cur]) if (--indeg[nxt] == 0) q.push(nxt);
        }

        array<bitset<100>, 100> reach;
        for (int i = 0; i < numCourses; i++) reach[i].reset();

        for (int u : topo)
        {
            for (int v : adj[u])
            {
                reach[v] |= reach[u];
                reach[v].set(u); 
            }
        }

        vector<bool> ans;
        ans.reserve(queries.size());
        for (auto &qr : queries) 
        {
            int u = qr[0], v = qr[1];
            ans.push_back(reach[v].test(u));
        }
        return ans;
    }
};