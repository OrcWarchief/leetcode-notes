// 424. Longest Repeating Character Replacement / solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        int counts[26] = {0};
        int l = 0, maxCharCount = 0;
        int maxLen = 0;

        int r = 0, l = 0;
        for (int r = 0; r < s.size(); ++r) {
            int idx = s[r] - 'A';
            counts[idx]++;
            maxCharCount = max(maxCharCount, counts[idx]);

            while ( (r - l + 1) - maxCharCount > k ) {
                counts[s[l] - 'A']--;
                l++;
            }
            maxLen = max(maxLen, r - l + 1);
        }
        return maxLen;
    }
};
