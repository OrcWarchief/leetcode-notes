// 739. Daily Temperatures / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
      vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> st;

        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && temperatures[i] > temperatures[st.top()])
            {
                int top = st.top(); st.pop();
                answer[top] = i - top;
            }
            st.push(i);
        }
        return answer;
    }
};