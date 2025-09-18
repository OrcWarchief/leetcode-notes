// 1091. Shortest Path in Binary Matrix/ solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return -1;
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) return -1;

        static const int dx[8] = {-1,-1,-1, 0,0, 1,1,1};
        static const int dy[8] = {-1, 0, 1,-1,1,-1,0,1};

        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int,int>> q;

        dist[0][0] = 1;
        q.push({0, 0});

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            if (r == n-1 && c == n-1) return dist[r][c];

            for (int k = 0; k < 8; ++k) {
                int nr = r + dy[k], nc = c + dx[k];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if (grid[nr][nc] != 0) continue;
                if (dist[nr][nc] != -1) continue;
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
        return -1;
    }
};