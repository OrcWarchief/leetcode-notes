// 316. 327. Count of Range Sum / solution.cpp
// Time: O(Nlogn)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mergeSort(vector<long long>& preSum, int L, int R, long long lower, long long upper)
    {
        if (L >= R) return 0;
        int M = (L + R) >> 1;
        long long cnt = mergeSort(preSum, L, M, lower, upper) + mergeSort(preSum, M + 1, R, lower, upper);

        int l = M + 1, r = M + 1;
        for (int i = L; i <= M; ++i) 
        {
            while (l <= R && preSum[l] - preSum[i] <  lower) ++l;
            while (r <= R && preSum[r] - preSum[i] <= upper) ++r;
            cnt += (r - l);
        }

        vector<long long> tmp;
        tmp.reserve(R - L + 1);
        int i = L, j = M + 1;
        while (i <= M && j <= R)
        {
            if (preSum[i] <= preSum[j]) tmp.push_back(preSum[i++]);
            else                        tmp.push_back(preSum[j++]);
        }
        while (i <= M) tmp.push_back(preSum[i++]);
        while (j <= R) tmp.push_back(preSum[j++]);
        copy(tmp.begin(), tmp.end(), preSum.begin() + L);
        return cnt;
    }
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> preSum(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
        return mergeSort(preSum, 0, n, lower, upper);
    }
};