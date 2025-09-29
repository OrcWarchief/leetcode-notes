// 773. Sliding Puzzle / solution.cpp
// Time: O(6!?6?N)  |  Space: O(6!)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target = "123450";

        string init;
        for (auto& b : board)
        {
            for (auto&bb : b)
            {
                init.push_back('0' + bb);
            }
        }

        int diff = 0;
        for (int i = 0; i < 6; i++)
        {
            if (init[i] != target[i] && init[i] != '0') diff++;
        }
        if (diff % 2 == 1) return -1;

        int minChange = numeric_limits<int>::max();
        vector<vector<int>> cand ={{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};
        unordered_set<string> visit; visit.insert(init);
        queue<pair<string, int>> q; q.push({init, 0});
        
        while (!q.empty())
        {
            auto [cur, cnt] = q.front(); q.pop();

            if (cnt > minChange) continue;

            if (cur == target)
            {
                return cnt;
            }

            int zeroloc;
            for (int i = 0; i < 6; i++)
            {
                if (cur[i] == '0') { zeroloc = i; break; }
            }
            for (int& nxt : cand[zeroloc])
            {
                string next = cur;
                next[zeroloc] = cur[nxt]; next[nxt] = cur[zeroloc];
                if (visit.find(next) == visit.end())
                {
                    visit.insert(next);
                    q.push({next, cnt + 1});
                }
            }
        }
    }
};