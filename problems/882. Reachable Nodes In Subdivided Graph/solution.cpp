// 882. Reachable Nodes In Subdivided Graph / solution.cpp
// Time: O(E + Log(N))  |  Space: O(N + E)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());

        for (auto e : edges)
        {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        priority_queue<pair<int, int>> pq;
        vector<int> best(n, -1); best[0] = maxMoves;
        pq.push({maxMoves, 0});
        while (!pq.empty())
        {
            auto[curMove, u] = pq.top(); pq.pop();
            if (curMove < best[u]) continue;
            
            for (auto [v, w] : adj[u])
            {
                if (curMove > w && curMove - (w + 1) > best[v])
                {
                    best[v] = curMove - w - 1;
                    pq.push({curMove - w - 1, v});
                }
            }
        }
        int answer = 0;
        for (int i = 0; i < n; ++i) if (best[i] >= 0) ++answer;
        for (auto &e : edges) 
        {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            long long fromU = max(0, best[u]);
            long long fromV = max(0, best[v]);
            answer += min<long long>(w, fromU + fromV);
        }

        return answer;
    }
};