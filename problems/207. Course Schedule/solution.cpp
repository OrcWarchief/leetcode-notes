// 207. Course Schedule / solution.cpp
// Time: O(N + P)  |  Space: O(N + P)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indeg(numCourses, 0);

        for (const auto& pre : prerequisites) 
        {
            adj[pre[1]].push_back(pre[0]);
            ++indeg[pre[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (indeg[i] == 0) q.push(i);
        }

        int visited = 0;
        while (!q.empty()) 
        {
            int cur = q.front(); q.pop();
            ++visited;

            for (int nxt : adj[cur])
                if (--indeg[nxt] == 0)
                    q.push(nxt);
        }
        
        return visited == numCourses;
    }
};
