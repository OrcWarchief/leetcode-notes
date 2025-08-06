// 560. Subarray Sum Equals K / solution.cpp
// Time: O(M * N)  |  Space: O(M * N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        freq[0] = 1;
        int prefix = 0, answer = 0;

        for (int num : nums) {
            prefix += num;
            answer += freq[prefix - k];
            ++freq[prefix];
        }
        return answer;
    }
};
