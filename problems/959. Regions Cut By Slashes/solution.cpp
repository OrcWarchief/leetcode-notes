// 959. Regions Cut By Slashes / solution.cpp
// Time: O(N?M?A(N?M))  |  Space: O(N?M)
#include <bits/stdc++.h>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
    struct DSU {
        vector<int> p, sz;
        DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
        int find (int x) { return p[x] == x ? x : p[x] = find(p[x]); }
        void unite (int a, int b)
        {
            a = find(a); b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            p[b] = a; sz[a] += sz[b];
        }
    };
public:
    int regionsBySlashes(vector<string>& grid) {
        int r = grid.size(); int c = grid[0].size();
        int total = 4 * r * c;
        DSU dsu(total);
        for (int i = 0; i < r; i++)
        {
            string s = grid[i];
            for (int j = 0; j < c; j++)
            {
                int index = (i * c + j) * 4;
                if (s[j] == ' ') 
                {
                    dsu.unite(index, index + 1);
                    dsu.unite(index + 1, index + 2);
                    dsu.unite(index + 2, index + 3);
                    if (i + 1 < r) dsu.unite(index + 2, index + 4 * c);
                    if (j + 1 < c) dsu.unite(index + 1, index + 7);
                }
                else if (s[j] == '/')
                {
                    dsu.unite(index, index + 3);
                    dsu.unite(index + 1, index + 2);
                    if (i + 1 < r) dsu.unite(index + 2, index + 4 * c);
                    if (j + 1 < c) dsu.unite(index + 1, index + 7);
                }
                else if (s[j] == '\\')
                {
                    dsu.unite(index, index + 1);
                    dsu.unite(index + 2, index + 3);
                    if (i + 1 < r) dsu.unite(index + 2, index + 4 * c);
                    if (j + 1 < c) dsu.unite(index + 1, index + 7);
                }
            }
        }
        int answer = 0;
        for (int i = 0; i < total; i++)
        {
            if (dsu.find(i) == i) ++answer;
        }
        return answer;
    }
};