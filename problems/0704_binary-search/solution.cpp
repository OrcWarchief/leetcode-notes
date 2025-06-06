// 0704_binary-search / solution.cpp
// Time: O(logN)  |  Space: O(1)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            int mid = (left + right) / 2;

            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                left = mid + 1; 
            }
            else // nums[mid] > target
            {
                right = mid - 1;
            }
        }
    }
};