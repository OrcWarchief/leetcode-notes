// 0200_number-of-islands / solution.cpp
// Time: O(M * N)  |  Space: O(M * N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        const int R = grid.size();
        if (R == 0) return 0;
        const int C = grid[0].size();

        const int dy[4] = {0, 0, 1, -1};
        const int dx[4] = {1, -1, 0, 0};

        int islands = 0;
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        vector<pair<int,int>> st;            // explicit stack

        for (int y = 0; y < R; ++y) {
            for (int x = 0; x < C; ++x) {
                if (grid[y][x] == '1' && !visited[y][x]) {
                    ++islands;               // found a new island
                    st.emplace_back(y, x);
                    visited[y][x] = true;

                    // ---------- iterative DFS ----------
                    while (!st.empty()) {
                        auto [cy, cx] = st.back();
                        st.pop_back();
                        for (int k = 0; k < 4; ++k) {
                            int ny = cy + dy[k];
                            int nx = cx + dx[k];
                            if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
                            if (grid[ny][nx] == '0' || visited[ny][nx]) continue;
                            visited[ny][nx] = true;
                            st.emplace_back(ny, nx);
                        }
                    }
                }
            }
        }
        return islands;
    }
};
