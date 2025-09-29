// 1557. Minimum Number of Vertices to Reach All Nodes / solution.cpp
// Time: O(N + M)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> indeg(n);
        for (auto& e : edges)
        {
            indeg[e[1]]++;
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (indeg[i] == 0) ans.push_back(i);
        }
        return ans;
    }
};