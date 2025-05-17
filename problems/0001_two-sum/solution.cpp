// 0001_two-sum / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;           // value -> index
        for (int i = 0; i < (int)nums.size(); ++i) {
            int need = target - nums[i];
            if (mp.count(need)) {
                return { mp[need], i };       // ���� ��
            }
            mp[nums[i]] = i;                  // ���� Ž���� ���� ����
        }
        return {}; // ���� ���ǻ� never reached
    }
};