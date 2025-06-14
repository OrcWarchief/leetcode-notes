// 0217_contains-duplicate / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int n : nums) {
            if (seen.count(n))
                return true;
            seen.insert(n);
        }
        return false;    
    }  
};
