// 307. Range Sum Query - Mutable / solution.cpp
// Time: O(log N)  |  Space: O(N)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class NumArray {
    vector<int> tree; 
    int n;
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;
        tree.assign(2 * n, 0); 
        for (int i = 0; i < n; i++) 
        {
            tree[n + i] = nums[i];
        }
        for (int i = n - 1; i > 0; i--) 
        {
            tree[i] = tree[2 * i] + tree[2 * i | 1];
        }
    }
    
    void update(int index, int val) {
        if (n == 0) return;
        int pos = n + index;
        tree[pos] = val;
        while (pos > 1) 
        {
            pos >>= 1;
            tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
        }
    }
    
    int sumRange(int left, int right) {
        if (n == 0) return 0;
        int l = left + n;
        int r = right + n + 1;
        int res = 0;
        while (l < r)
        {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */