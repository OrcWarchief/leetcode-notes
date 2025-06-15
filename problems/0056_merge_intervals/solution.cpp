// 0056_merge-intervals / solution.cpp
// Time: O(NlogN)  |  Space: O(1)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // 1) 시작점 기준 정렬
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        // 2) 결과 벡터 초기화
        vector<vector<int>> res;
        res.push_back(intervals[0]);

        // 3) 한 번의 스캔
        for (size_t i = 1; i < intervals.size(); ++i) {
            // 겹치는 경우: 시작점 ≤ res.back의 끝점
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);  // 끝점 확장
            } else {
                res.push_back(intervals[i]);  // 새 구간 추가
            }
        }
        return res;
    }
};
