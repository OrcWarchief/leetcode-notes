LeetCode 143 ? Reorder List (README)
���� ���
���� ���� ����Ʈ L0 �� L1 �� �� �� Ln�� **���ڸ�(in?place)**����
L0 �� Ln �� L1 �� Ln-1 �� L2 �� Ln-2 �� �� ���·� ��迭�϶�.

��� ��ü�� ���ġ�ؾ� �ϸ�, ���� ��ȯ�ϰų� �� ��带 ����� �� ��

�߰� ������ O(1) (��� �ݽ��õ� �������� ����)

��: 1��2��3��4��5 �� 1��5��2��4��3

�ٽ� ���̵�� (3�ܰ�)
�߰� ã��: ����/���� �����ͷ� ��� ���(slow)�� ã�´�.

���� �� ����: slow->next���� ������ �������� �����´�.

���� ����: �չ�(���� head)�� �ڹ�(���� ���)�� ������ �����Ѵ�.

�� ������ ��� ����(¦/Ȧ)�� ���� O(n) �ð�, O(1) �������� �����Ѵ�.

�˰��� ��
1) ��� ã�� (Fast/Slow)
�Ϲ������� while (fast && fast->next) ���.

¦�� ������ �� slow�� ������ ������� �����.

������� while (fast->next && fast->next->next)�� ���� ���� ������� �����.

��� ���̵� ���� �ܰ�(�и�������������)�� �´ٸ� �ùٸ��� �����Ѵ�.

2) �и� + ����
second = slow->next; slow->next = nullptr;�� ��/�� ����Ʈ�� �и��Ѵ�.

second�� �ݺ������� ����(reverse) ó���Ѵ�.

3) ���� ���� (Weave/Merge)
������ �� ��(p1=head, p2=��������Ʈ)�� ����.

�� �ܰ迡�� ���� �����͸� �̸� ������ �� ��, p1��p2��p1next ������ �մ´�.

�Ǽ� ������ ���� **���� ����Ʈ ����(while (p2))**���� ������ ���� ����ϴ�.

���� ���� (C++)
cpp
����
// ���� ���� ����Ʈ ����
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// O(n) time, O(1) extra space
void reorderList(ListNode* head) {
    if (!head || !head->next) return;

    // 1) ��� ã�� (¦�� ���̿��� slow�� ������ ���)
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 2) ���� �� �и� + ����
    ListNode* second = slow->next;
    slow->next = nullptr;             // ��/�� ����Ʈ �и� (�߿�)
    ListNode* prev = nullptr;
    while (second) {
        ListNode* nxt = second->next;
        second->next = prev;
        prev = second;
        second = nxt;
    }
    // prev: ������ ���� ���� ���� �Ӹ� (Ln, Ln-1, ...)

    // 3) ���� ���� (���� ����Ʈ ����)
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
��Ȯ�� ����ġ
������� �и� �� ���� ���� �������� ����� ������ Ln, Ln-1, �� ������ ���ο� ��ġ�Ѵ�.

�չݰ� �ڹ��� ������ �����ϸ� �䱸�ϴ� ���� L0, Ln, L1, Ln-1, ���� �ȴ�.

�� ���� �ִ� �� ���� �̵�/�����ϹǷ� �ð��� O(n)�̰�, �߰� ������ ���� �ʾ� ������ O(1)�̴�.

���� �߻��ϴ� �Ǽ� üũ����Ʈ
 head==nullptr �Ǵ� head->next==nullptr ó�� ����

 slow->next = nullptr�� �и����� �ʾ� ����Ŭ/���ѷ��� �߻�

 ������ slow���� ����(����) ? �ݵ�� slow->next����

 ���� ���տ��� ���� ������(n1, n2)�� ���� �������� �ʾ� ��ũ �ս�

 ���� ���� ����(while (p2)) �̻������ ���� ó�� �Ǽ�

 �� ��� ����/�� ���� ��� (���� ���� ����)

�� vector + new ����� Ʋ����?

���� �����Ͽ� �� ����Ʈ�� �����, ���� ����� next�� �������� �ʱ� ����.

LeetCode �ñ״�ó�� void reorderList(ListNode* head)�� head ��ü�� �ٲ� ���� ����.

��������� ȣ���ڴ� ������ ������ ����Ʈ���� ���� �ȴ�. (�Դٰ� in-place ���� ����)

���� ���� (�Է�: 0��1��2��3)
��� ã�� �� slow=2

�и�: �� 0��1��2, �� 3 (�����ص� 3)

����: 0��3��1��2

���⵵
�ð�: O(n) ? fast/slow, ����, ���� ���� ���� ����

����: O(1) ? �߰� �����̳�/��� �̻��

�̴� �׽�Ʈ ���� (���ÿ��� Ȯ�ο�)
cpp
����
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void print(ListNode* h){ for(;h;h=h->next) cout<<h->val<<" "; cout<<"\n"; }

ListNode* build(const vector<int>& v){
    ListNode dummy(0), *cur=&dummy;
    for(int x: v){ cur->next=new ListNode(x); cur=cur->next; }
    return dummy.next;
}

// ���� reorderList �Լ� �ٿ��ֱ�

int main(){
    auto h = build({0,1,2,3,4});
    reorderList(h);
    print(h); // ���: 0 4 1 3 2
}
����/���� ����
Reverse Linked List

Middle of the Linked List

Palindrome Linked List

Merge Two Sorted Lists

Remove Nth Node From End of List

Odd Even Linked List

Rotate List

Sort List

���
�и� �� ���� �� ���� 3�ܰ踸 ��Ű�� ���������� �ذ� ����.

fast/slow ������ �� �� ����(fast && fast->next / fast->next && fast->next->next),
���� ������ �ϰ��ǰ� ���߸� �ȴ�.