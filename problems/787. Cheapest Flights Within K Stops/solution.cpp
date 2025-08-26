// 787. Cheapest Flights Within K Stops / solution.cpp
// Time: O(K * E)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[src] = 0;

        for (int i = 0; i <= k; ++i) 
        {
            vector<int> ndist = dist;
            for (const auto& f : flights) 
            {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] == INF) continue;
                if (ndist[v] > dist[u] + w) 
                {
                    ndist[v] = dist[u] + w;
                }
            }
            dist.swap(ndist);
        }

        return dist[dst] == INF ? -1 : dist[dst];
    }
};