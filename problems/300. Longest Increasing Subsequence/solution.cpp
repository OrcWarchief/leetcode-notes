// 300. Longest Increasing Subsequence / solution.cpp
// Time: O(NlogN)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
         if (nums.empty()) return 0;

        vector<int> lis;
        lis.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > lis.back()) { lis.push_back(nums[i]); continue; }
            if (nums[i] < lis.front()) { lis[0] = nums[i]; continue; }

            int left = 0;
            int right = lis.size() - 1;
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                
                if (lis[mid] < nums[i]) left = mid + 1;
                else                     right = mid; 
            }
            if (lis[left] != nums[i]) lis[left] = nums[i];
        }
        return lis.size();
    }
};