// 0121_Best_Time_to_Buy_and_Sell_stock / solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice  = std::numeric_limits<int>::max();
        int maxProfit = 0;

        for (int price : prices) {
            minPrice  = std::min(minPrice, price);
            maxProfit = std::max(maxProfit, price - minPrice);
        }
        return maxProfit;
    }
};