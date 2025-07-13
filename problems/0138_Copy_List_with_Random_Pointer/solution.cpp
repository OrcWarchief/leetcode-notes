// 0138_Copy_List_with_Random_Pointer / solution.cpp
// Time: O(N)  |  Space: O(N)
#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        unordered_map<Node*, Node*> mp;
        for (Node* cur = head; cur; cur = cur->next)
        {
            mp[cur] = new Node(cur->val);
        }
        for (Node* cur = head; cur; cur = cur->next)
        {
            mp[cur]->next = mp[cur->next];
            mp[cur]->random = mp[cur->random];
        }
        return mp[head];
    }
};