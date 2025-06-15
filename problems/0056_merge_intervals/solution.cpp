// 0056_merge-intervals / solution.cpp
// Time: O(NlogN)  |  Space: O(1)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // 1) ������ ���� ����
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        // 2) ��� ���� �ʱ�ȭ
        vector<vector<int>> res;
        res.push_back(intervals[0]);

        // 3) �� ���� ��ĵ
        for (size_t i = 1; i < intervals.size(); ++i) {
            // ��ġ�� ���: ������ �� res.back�� ����
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);  // ���� Ȯ��
            } else {
                res.push_back(intervals[i]);  // �� ���� �߰�
            }
        }
        return res;
    }
};
