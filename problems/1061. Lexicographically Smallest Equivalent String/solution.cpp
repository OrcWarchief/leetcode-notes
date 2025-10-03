// 1061. Lexicographically Smallest Equivalent String / solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
    struct DSU {
        vector<int> p, sz;
        DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
        int find (int x) { return p[x] == x ? x : find(p[x]); }

        void unite (int a, int b) {
            a = find(a); b = find(b);
            if (a == b) return;
            if (a < b) p[b] = a;
            else       p[a] = b;
        }
    };
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.size();
        DSU dsu(26);

        for (int i = 0; i < n; i++)
        {
            dsu.unite(s1[i] - 'a', s2[i] - 'a');
        }

        string answer = baseStr;
        for (int i = 0; i < baseStr.size(); i++)
        {
            int r = dsu.find(baseStr[i] - 'a');
            answer[i] = char('a' + r);
        }

        return answer;
    }
};