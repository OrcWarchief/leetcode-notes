// 70. Climbing Stairs / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, 0);
        if (n == 1) return 1;
        dp[1] = 1;
        if (n == 2) return 2;
        dp[2] = 2;

        for (int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};