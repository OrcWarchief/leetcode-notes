// 732. My Calendar III / solution.cpp
// Time: O()  |  Space: O()
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int mx = 0, add = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};
class MyCalendarThree {
    Node* root;
    static const int L = 0;
    static const int R = 1000000000;

    void push(Node* t)
    {
        if (!t-> left) t-> left = new Node();
        if (!t->right) t->right = new Node();
        if (t->add != 0)
        {
            t->left->mx     += t->add;
            t->left->add    += t->add;
            t->right->mx    += t->add;
            t->right->add   += t->add;
            t->add = 0;
        }
    }

    void rangeAdd(Node* t, int tl, int tr, int ql, int qr, int val)
    {
        if (qr <= tl || tr <= ql) return;
        if (ql <= tl && tr <= qr)
        {
            t->mx +=val;
            t->add += val;
            return;
        }
        push(t);
        int tm = tl + (tr - tl) / 2;
        rangeAdd(t->left, tl, tm, ql, qr, val);
        rangeAdd(t->right, tm, tr, ql, qr, val);
        t->mx = std::max(t->left->mx, t->right->mx);
    }
public:

    MyCalendarThree() { root = new Node(); }
    
    int book(int startTime, int endTime) {
        rangeAdd(root, L, R, startTime, endTime, 1);
        return root->mx;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */