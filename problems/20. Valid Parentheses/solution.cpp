// 20. Valid Parentheses / solution.cpp
// Time: O(N)  |  Space: O(1)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s)
        {
            if (c == '(' || c == '[' || c == '{') st.push(c);
            else 
            {
                if (st.empty()) return false;
                char open = st.top();
                st.pop();
                if ((c == ')' && open != '(') ||
                    (c == ']' && open != '[') ||
                    (c == '}' && open != '{'))
                    return false;
            }
        }
        return st.empty() ? true : false; 
    }
};
