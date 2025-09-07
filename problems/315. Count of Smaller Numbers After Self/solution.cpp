// 315. Count of Smaller Numbers After Self / solution.cpp
// Time: O(Nlogn)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;
struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void update(int i, int delta)
    {
        for (; i <= n; i += (i & -i)) bit[i] += delta;
    }

    int sum(int i)
    {
        int s = 0;
        for (; i > 0; i -= (i & -i)) s += bit[i];
        return s;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        if (n == 0) return ans;

        vector<int> vals(nums.begin(), nums.end());
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        
        auto getRank = [&](int x) {
            return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
        };

        Fenwick fw(vals.size());

        for (int i = n - 1; i >= 0; --i)
        {
            int r = getRank(nums[i]);
            ans[i] = fw.sum(r - 1);
            fw.update(r, 1);
        }
        return ans;
    }
};