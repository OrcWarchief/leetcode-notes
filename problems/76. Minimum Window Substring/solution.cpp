// 76. Minimum Window Substring / solution.cpp
// Time: O(M + N)  |  Space: O(1)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map <char, int> need;
        for (char c : t)
        {
            need[c]++;
        }

        int required = t.size();
        int bestLen = numeric_limits<int>::max(), bestL = 0;

        for (int L = 0, R = 0; R < s.size(); R++)
        {
            char cr = s[R];
            if (need[cr] > 0) required--;
            need[cr]--;

            while(required == 0)
            {
                if (R - L + 1 < bestLen)
                {
                    bestLen = R - L + 1;
                    bestL = L;
                }
                char cl = s[L++];
                ++need[cl];
                if (need[cl] > 0) ++required;
            }
        }

        return bestLen == numeric_limits<int>::max() ? "" : s.substr(bestL, bestLen);
    }
};