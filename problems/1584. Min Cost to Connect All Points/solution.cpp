// 1584. Min Cost to Connect All Points / solution.cpp
// Time: O()  |  Space: O()
#include <bits/stdc++.h>
using namespace std;

class Solution {
struct DSU
{
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x)
    {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

struct Edge
{
    int u, v, w;
};

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        vector<Edge> edges;
        int n = points.size();

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int x = std::abs(points[i][0] - points[j][0]);
                int y = std::abs(points[i][1] - points[j][1]); 
                int weight = x + y;
                
                Edge e;
                e.u = i;
                e.v = j;
                e.w = weight;

                edges.push_back(e);
            }  
        }

        sort(edges.begin(),edges.end(), [](Edge a, Edge b) {
            return a.w < b.w; 
        });
        DSU dsu(n);
        int mst_weight = 0, used = 0;;

        for (auto& e : edges)
        {
            if (dsu.unite(e.u, e.v))
            {
                mst_weight += e.w;
                if (++used == n - 1) break;
            }
        }

        return mst_weight;
    }
};