// 1368. Minimum Cost to Make at Least One Valid Path in a Grid / solution.cpp
// Time: O(M * N)  |  Space: O(M * N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        
        int dr[4] = {0, 0, 1, -1};
        int dc[4] = {1, -1, 0, 0};

        const int INF = 1e9;
        vector<vector<int>> dist(rows, vector<int>(cols, INF));
        deque<pair<int,int>> dq;
        dist[0][0] = 0;
        dq.emplace_front(0, 0);

        while (!dq.empty())
        {
            auto next = dq.front(); dq.pop_front();
            int r = next.first; int c = next.second;
            int base = dist[r][c];

            int free = grid[r][c] - 1;

            for (int k = 0; k < 4; ++k) 
            {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

                int w = (k == free) ? 0 : 1;
                if (dist[nr][nc] > base + w) 
                {
                    dist[nr][nc] = base + w;
                    if (w == 0) dq.emplace_front(nr, nc);
                    else        dq.emplace_back(nr, nc);
                }
            }
        }
        return dist[rows-1][cols-1];
    }
};