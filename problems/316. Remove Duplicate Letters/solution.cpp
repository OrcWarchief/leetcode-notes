// 316. Remove Duplicate Letters / solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);
        for (char c : s) count[c - 'a']++;

        string answer;
        vector<int> visited(26, 0);
        for (int i = 0; i < s.size(); i++)
        {
            int cur = s[i] - 'a';
            count[cur]--;
            if (visited[cur]) continue;

            while (!answer.empty() && s[i] < answer.back() && count[answer.back() - 'a'] > 0)
            { 
                visited[answer.back() - 'a'] = false;
                answer.pop_back();
            }
            answer.push_back(s[i]);
            visited[cur]++;
        }
        return answer;
    }
};