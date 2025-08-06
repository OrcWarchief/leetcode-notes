// 567. Permutation in String / solution.cpp
// Time: O(M)  |  Space: O(1)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        if (n > m) return false;

        int need[26] = {0}, window[26] = {0};

        for (char c : s1) need[c - 'a']++;

        // 초기 윈도 채우기
        for (int i = 0; i < n; ++i)
            window[s2[i] - 'a']++;

        if (equal(begin(need), end(need), begin(window))) return true;

        // 슬라이딩
        for (int i = n; i < m; ++i) {
            window[s2[i] - 'a']++;                  // 오른쪽 문자 추가
            window[s2[i - n] - 'a']--;              // 왼쪽 문자 제거
            if (equal(begin(need), end(need), begin(window)))
                return true;
        }
        return false;
    }
};
