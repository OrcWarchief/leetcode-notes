// 2115. Find All Possible Recipes from Given Supplies / solution.cpp
// Time: O(N + M)  |  Space: O(N + M)
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_set<string> have(supplies.begin(), supplies.end());
        unordered_map<string, int> indeg;
        unordered_map<string, vector<string>> needers;
        
        for (int i = 0; i < recipes.size(); i++)
        {
            for (auto& ing : ingredients[i])
            {
                if (!have.count(ing))
                {
                    ++indeg[recipes[i]];
                    needers[ing].push_back(recipes[i]);
                }
            }
        }

        queue<string> q;

        for (int i = 0; i < recipes.size(); i++)
        {
            if (indeg[recipes[i]] == 0)
            {
                q.push(recipes[i]);
            }
        }

        vector<string> ans;
        while (!q.empty())
        {
            string cur = q.front(); q.pop();
            ans.push_back(cur);
            have.insert(cur);

            for (auto& nxt : needers[cur])
            {
                if (--indeg[nxt] == 0) q.push(nxt);
            }
        }

        return ans;
    }
};