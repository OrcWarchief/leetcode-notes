// 1203. Sort Items by Groups Respecting Dependencies / solution.cpp
// Time: O(V + E)  |  Space: O(V + E)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<int> g = group;
        int nextGroup = m;
        for (int i = 0; i < n; i++)
        {
            if (group[i] == -1) g[i] =nextGroup++;
        }

        int totalGroup = nextGroup;

        vector<vector<int>> itemAdj(n), groupAdj(totalGroup);
        vector<int> indegItem(n, 0), indegGroup(totalGroup, 0);\

        for (int v = 0; v < n; v++)
        {
            for (int& u : beforeItems[v])
            {
                itemAdj[u].push_back(v);
                ++indegItem[v];

                int gu = g[u], gv = g[v];
                if (gu != gv)
                {
                    groupAdj[gu].push_back(gv);
                    ++indegGroup[gv];
                }
            }
        }

        auto topo = [](const vector<vector<int>>& adj, vector<int> indeg) -> vector<int> {
            queue<int> q;
            for (int i = 0; i < (int)indeg.size(); i++)
                if (indeg[i] == 0) q.push(i);

            vector<int> order;
            order.reserve(adj.size());
            while (!q.empty())
            {
                int x = q.front(); q.pop();
                order.push_back(x);
                for (int y : adj[x])
                    if (--indeg[y] == 0) q.push(y);
            }
            if (order.size() != adj.size()) return {};
            return order;
        };

        vector<int> groupOrder = topo(groupAdj, indegGroup);
        if (groupOrder.empty()) return {};

        vector<int> itemOrder  = topo(itemAdj, indegItem);
        if (itemOrder.empty()) return {};

        vector<vector<int>> buckets(totalGroup);
        for (int x : itemOrder) buckets[g[x]].push_back(x);

        vector<int> ans;
        ans.reserve(n);
        for (int gg : groupOrder) {
            for (int x :buckets[gg]) ans.push_back(x);
        }

        return ans;
    }
};