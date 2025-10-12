// 493. Reverse Pairs / solution.cpp
// Time: O()  |  Space: O()
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mergeSort(vector<int>& a, int l, int r)
    {
        if (l >= r) return 0;
        int m = (l + r) >> 1;
        int cnt = mergeSort(a, l, m) + mergeSort(a, m + 1, r); 

        int j = m + 1;
        for (int i = l; i <= m; ++i)
        {
            while (j <= r && (long long)a[i] > 2LL * (long long)a[j]) j++;
            cnt += j - (m + 1);
        }

        vector<int> tmp;
        tmp.reserve(r - l + 1);
        int i = l, j = m + 1;
        while (i <= m && j <= r)
        {
            if (a[i] <= a[j])   tmp.push_back(a[i++]);
            else                tmp.push_back(a[j++]);
        }
        while (i <= m) tmp.push_back(a[i++]);
        while (j <= r) tmp.push_back(a[j++]);
        copy(tmp.begin(), tmp.end(), a.begin() + l);
        return cnt;
    }
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};