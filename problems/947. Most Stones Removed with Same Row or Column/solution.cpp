// 947. Most Stones Removed with Same Row or Columne / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
    struct DSU
    {
        int n; vector<int> parent, sz;
        DSU(int n = 0) { init(n); }

        void init(int nn) 
        { 
            n = nn; parent.resize(n); 
            iota(parent.begin(), parent.end(), 0); 
            sz.assign(n, 1); 
        }
        
        int find(int x)
        {
            if (parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }

        bool unite (int a, int b)
        {
            a = find(a); b = find(b);
            if (a == b) return false;
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a; sz[a] += sz[b];
            return true;
        }
    };
public:
    int removeStones(vector<vector<int>>& stones) {
        DSU dsu;
        unordered_set<int> used;

        for (auto& s : stones)
        {
            int r = s[0];
            int c = s[1] + 10000;
            dsu.unite(r, c);
            used.insert(r);
            used.insert(c);
        }

        int comps = 0;
        for (int x : used)
        {
            if (dsu.find(x) == x) ++comps;
        }

        return stones.size() - comps;
    }
};