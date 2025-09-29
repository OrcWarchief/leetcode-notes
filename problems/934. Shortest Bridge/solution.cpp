// 934. Shortest Bridge / solution.cpp
// Time: O(N^2)  |  Space: O(N^2)
#include <bits/stdc++.h>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> visited(n, vector<int>(n, 0));
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        queue<pair<int,int>> q;
        auto inb = [&](int x, int y){ return 0 <= x && x < n && 0 <= y && y < n; };

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1 && !visited[i][j])
                {
                    queue<pair<int,int>> qq;
                    qq.push({i,j});
                    visited[i][j] = 1;
                    q.push({i,j});

                    while (!qq.empty())
                    {
                        auto [cx, cy] = q.front(); q.pop();
                        for (int n = 0; n < 4; n++)
                        {
                            int nx = cx + dx[n], ny = cy + dy[n];
                            if (!inb(nx,ny) || visited[nx][ny] || grid[nx][ny] != 1) continue;
                            visited[nx][ny] = 1;
                            qq.push({nx,ny});
                            q.push({nx,ny});
                        }
                    }
                }
            }
        }

       int dist = 0;
        while (!q.empty()) {
            int sz = (int)q.size();
            while (sz--) {
                auto [cx, cy] = q.front(); q.pop();
                for (int k = 0; k < 4; ++k) {
                    int nx = cx + dx[k], ny = cy + dy[k];
                    if (!inb(nx,ny) || visited[nx][ny]) continue;
                    if (grid[nx][ny] == 1) {
                        return dist;
                    }
                    visited[nx][ny] = 1;
                    q.push({nx,ny});
                }
            }
            ++dist;
        }
        return -1;
    }
};