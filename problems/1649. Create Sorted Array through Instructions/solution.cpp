// 1649. Create Sorted Array through Instructions / solution.cpp
// Time: O(NlogN)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct BIT {
        int n; vector<int> p;
        BIT(int n) : n(n), p(n + 1, 0) {}
        void add(int i, int x) 
        {
            for (; i<= n; i += i & -i)
            {
                p[i] += x;
            }
        }

        long long sum(int i) const
        {
            long long s = 0;
            for (; i > 0; i -= i & -i) s += p[i];
            return s;
        }
    };
    int createSortedArray(vector<int>& instructions) {
        const int MOD = 1'000'000'007;

        vector<int> vals = instructions;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        // TODO -> ∆Ê¿® ∆Æ∏Æ ∏∏µÈ±‚ ¿Ã»ƒ ∏∏µÈæÓ¡¯ ∆Ê¿®∆Æ∏Æ∑Œ lower, greater = size() - notgreater

        BIT bit(vals.size());

        auto idxOf = [&](int x) {
            return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
        };

        long long ans = 0;
        long long inserted = 0;

        for (int x : instructions)
        {
            int idx = idxOf(x);
            long long less = bit.sum(idx - 1);
            long long notGreater = bit.sum(idx);
            long long greater = inserted - notGreater;
            ans += min(less, greater);
            ans %= MOD;
            bit.add(idx, 1);
            inserted++;
        }
        return (int)(ans % MOD);
    }
};