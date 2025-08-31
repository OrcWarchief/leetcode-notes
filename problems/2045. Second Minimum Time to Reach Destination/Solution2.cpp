#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> adj(n + 1);

        for (auto& edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<int> dist1(n + 1, numeric_limits<int>::max());
        vector<int> dist2(n + 1, numeric_limits<int>::max());
        vector<int> freq(n + 1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

        min_heap.push({0, 1});
        dist1[1] = 0;

        while(!min_heap.empty())
        {
            auto [timetaken, node] = min_heap.top(); min_heap.pop();
            freq[node]++;

            if (freq[node] ==2 && node == n) return timetaken;

            if ((timetaken / change) % 2)
            {
                timetaken = change * (timetaken / change + 1) + time;
            }
            else
            {
                timetaken = timetaken + time;   
            }
            for (auto& neighbor : adj[node])
            {
                if (freq[neighbor] == 2) continue;
                if (dist1[neighbor] > timetaken)
                {
                    dist2[neighbor] = dist1[neighbor];
                    dist1[neighbor] = timetaken;
                    min_heap.push({timetaken, neighbor});
                }
                else if (dist2[neighbor] > timetaken && dist1[neighbor] != timetaken)
                {
                    dist2[neighbor] = timetaken;
                    min_heap.push({timetaken, neighbor});
                }
            }
        }
        return 0;
    }
};