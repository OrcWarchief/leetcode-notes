// 2045. Second Minimum Time to Reach Destination / solution.cpp
// Time: O(ElogE)  |  Space: O(E)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int INF = 1e9;
        vector<int> dist1(n + 1, INF); vector<int> dist2(n + 1, INF); 
        dist1[1] = 0;
        queue<int> q; q.push(1);

        while (!q.empty())
        {
            int cur = q.front(); q.pop();
            for (auto& a : adj[cur])
            {
                int d = dist1[cur] + 1;

                if (d < dist1[a])
                {
                    dist2[a] = dist1[a];
                    dist1[a] = d;
                    q.push(a);
                }
                else if (d > dist1[a] && d < dist2[a])
                {
                    dist2[a] = d;
                    q.push(a);
                }
                
                int d2 = dist2[cur] + 1;
                
                if (dist1[a] < d2 && d2 < dist2[a]) 
                {
                    dist2[a] = d2;
                    q.push(a);
                }
            }
        }

        int count = dist2[n];
        int cur = 0;
        for (int step = 0; step < count; step++)
        {
            int period = cur / change;
            bool isRed = (period % 2 == 1);
            if (isRed)
            {
                cur = (period + 1) * 1 * change; 
            }
            cur += time;
        }
        return cur;
    }
};
