// 1202. Smallest String With Swaps / solution.cpp
// Time: O(Nlogn)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
    struct DSU
    {
        vector<int> p, sz;
        DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
        int find (int x) 
        { 
            return p[x] == x ? x : find(p[x]); 
        }

        void unite(int a, int b)
        {
            a = find(a); b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            p[b] = a; sz[a] += sz[b];
        }
    };
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        DSU dsu(s.size());
        for (auto& p : pairs)
        {
            dsu.unite(p[0], p[1]);
        }
        unordered_map<int, vector<int>> idxOfRoot;
        for (int i = 0; i < (int)s.size(); ++i) 
        {
            int r = dsu.find(i);
            idxOfRoot[r].push_back(i);
        }
        string answer = s;
        for (auto& [root, idxs] : idxOfRoot) 
        {
            sort(idxs.begin(), idxs.end());
            vector<char> chars;
            chars.reserve(idxs.size());
            for (int idx : idxs) chars.push_back(s[idx]);
            sort(chars.begin(), chars.end());

            for (int k = 0; k < (int)idxs.size(); ++k) 
            {
                answer[idxs[k]] = chars[k];
            }
        }
        return answer;
    }
};