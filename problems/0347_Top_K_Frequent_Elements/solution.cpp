// 0347_Top_K_Frequent_Elements / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freq;

        for (int n : nums)
        {
            ++freq[n];
        }
        
        // (값, 카운트) 쌍을 벡터로 복사
        vector<pair<int,int>> v(freq.begin(), freq.end());

        // ① 카운트 내림차순, ② 동점이면 값 오름차순
        sort(v.begin(), v.end(),
            [](const auto& a, const auto& b) {
                if (a.second != b.second) return a.second > b.second; // 빈도 큰 것이 먼저
                return a.first < b.first;                             // 값이 작은 것이 먼저
            });

        vector<int> result;
        for (int i = v.size(); i > v.size()-k; i--)
            result.push_back(v[i].first);
        
        return result;
    }
};