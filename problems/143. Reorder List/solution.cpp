// 143. Reorder List / solution.cpp
// Time: O(MAX(M , N))  |  Space: O(MAX(M , N))
#include <bits/stdc++.h>
using namespace std;

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        ListNode* fast = head;
        ListNode* slow = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* prev = nullptr;
        ListNode* cur = slow->next;
        slow->next = nullptr;
        while (cur)
        {
            ListNode* nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }

        ListNode* p1 = head;
        ListNode* p2 = prev;
        while (p2) {
            ListNode* n1 = p1->next;
            ListNode* n2 = p2->next;

            p1->next = p2;
            p2->next = n1;

            p1 = n1;
            p2 = n2;
        }
    }
};