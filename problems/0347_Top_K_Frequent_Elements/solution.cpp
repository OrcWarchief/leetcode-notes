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
        
        // (��, ī��Ʈ) ���� ���ͷ� ����
        vector<pair<int,int>> v(freq.begin(), freq.end());

        // �� ī��Ʈ ��������, �� �����̸� �� ��������
        sort(v.begin(), v.end(),
            [](const auto& a, const auto& b) {
                if (a.second != b.second) return a.second > b.second; // �� ū ���� ����
                return a.first < b.first;                             // ���� ���� ���� ����
            });

        vector<int> result;
        for (int i = v.size(); i > v.size()-k; i--)
            result.push_back(v[i].first);
        
        return result;
    }
};