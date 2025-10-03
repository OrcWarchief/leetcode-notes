// 839. Similar String Groups / solution.cpp
// Time: O(N^2 * M)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct DSU 
    {
        vector<int> p, sz;
        DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
        int find (int x) { return p[x] == x ? x : find(p[x]); }
        void unite (int a, int b)
        {
            a = find(a); b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            p[b] = a; sz[a] += sz[b];
        }
    };
public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        DSU dsu(n);

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int diff = 0;
                int nn = strs[i].size();
                for (int k = 0; k < nn; k++)
                {
                    if (strs[i][k] != strs[j][k]) diff++;
                    if (diff > 2) break; 
                }

                if (diff == 2 || diff == 0)
                {
                    dsu.unite(i, j);
                }
            }
        }

        int answer = 0;
        for (int i = 0; i < n; i++)
        {
            if (dsu.p[i] == i) answer++;
        }

        return answer;
    }
};