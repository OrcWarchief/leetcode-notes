// 1976. Number of Ways to Arrive at Destination / solution.cpp
// Time: O(E*Log(N))  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) 
    {
        vector<vector<pair<int, int>>> adj (n);
        for (auto &r : roads)
        {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        const long long INF = (long long)4e18;
        const long long MOD = 1000000007LL;

        vector<long long> dist(n, INF);
        vector<long long> ways(n, 0);

        dist[0] = 0;
        ways[0] = 1;

        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            auto [dis, cur] = pq.top(); pq.pop();
            if (dis != dist[cur]) continue;
            
            for (auto [next, cost] : adj[cur])
            {
                if (dist[next] > dist[cur] + cost)
                {
                    dist[next] = dist[cur] + cost;
                    ways[next] = ways[cur];
                    pq.push({dist[next], next});
                }
                else if (dist[next] == dist[cur] + cost)
                {
                    ways[next] = (ways[next] + ways[cur]) % MOD;
                }
            }
        }
        return ways[n - 1];
    }
};
