eetCode 206 ? Reverse Linked List (README)
���� ���
���� ���� ����Ʈ�� �Ӹ� ������ head�� �־����� ��, ����Ʈ�� �������� ������ �� �Ӹ� �����͸� ��ȯ�϶�.

�Է�: 1 �� 2 �� 3 �� 4 �� 5 �� null

���: 5 �� 4 �� 3 �� 2 �� 1 �� null

�ٽ� ���̵��
�����͸� �� �ٷ� ������ �ݺ�(iterative) ���÷��̽� Ǯ�̰� �����̴�.

�Һ���(�� �ݺ� ���� �� �׻� ��):

prev: �̹� ������ �κ� ����Ʈ�� �Ӹ�

cur: ���� ������ ���� �κ� ����Ʈ�� �Ӹ�

�� ���ܿ��� �ϴ� ��:

nextNode = cur->next ? ���� ��� ���

cur->next = prev ? ���� ����� ��ũ�� �ڷ� ����

prev = cur ? ������ �κ��� �� �Ӹ� ����

cur = nextNode ? ���� ������ �������� ����

�̰� cur == nullptr �� ������ �ݺ��ϸ�, ���������� prev�� ������ ������ ����Ʈ�� �Ӹ��� �ȴ�.

�ݺ� Ǯ�� (����, O(1) �߰� �޸�)
cpp
����
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur  = head;

        while (cur != nullptr) {
            ListNode* nextNode = cur->next; // 1) ���� ��� �ּ� ���
            cur->next = prev;               // 2) ��ũ ������
            prev = cur;                     // 3) prev�� �� �Ӹ��� �̵�
            cur = nextNode;                 // 4) ���� ���� ����
        }
        return prev; // ������ ����Ʈ�� �Ӹ�
    }
};
�ð�/���� ���⵵
�ð�: O(n) (�� ��带 �� ���� �湮)

����: O(1) (�߰� ������ �� ���� ���)

��� Ǯ�� (���������� ���� ���, O(n) ����)
cpp
����
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;

        ListNode* newHead = reverseList(head->next);
        head->next->next = head; // �ڿ��� ������ ����
        head->next = nullptr;    // ���� ������ ���ϴ� ��ũ ����
        return newHead;
    }
};
����
ȣ�� ���̸�ŭ ȣ�� ���� O(n) ���. �Է��� �ſ� ��� ���� �����÷ο� ����.

������ ���� ������ ������ ��, ��ȯ�ϸ鼭 ��ũ�� �ڷ� ��輱��.

�ð��� ���� (3��� ����)
�ʱ�:

yaml
����
prev: null
cur : [1] �� [2] �� [3] �� null
1ȸ��:

csharp
����
nextNode=[2]
cur->next=prev(null) => [1]��null
prev=[1], cur=[2]��[3]��null
2ȸ��:

csharp
����
nextNode=[3]
cur->next=prev([1])  => [2]��[1]��null
prev=[2]��[1]��null, cur=[3]��null
3ȸ�� �� ����:

ini
����
prev=[3]��[2]��[1]��null
cur=null
���� ���̽�
�� ����Ʈ: head == nullptr �� �״�� nullptr ��ȯ

���� 1��: ��ũ ����� ����

�ſ� �� ����Ʈ: ��� Ǯ�� ��� �ݺ� Ǯ�� ����

���� �ϴ� �Ǽ� & ����� ��
nextNode ����� ����: cur->next = prev �� ���� ��带 �Ҿ����

��� ȥ��:

cur->next = prev�� ��� ���� ��ũ ����

prev = cur�� ������ ������ ���(�ּ�) ����

���� �߰��� ����Ŭ�� ����� ��ȸ�� ������ ���� �� �ܰ躰�� �ּҸ� ����� ����

cpp
����
// ������ (�ּ� Ȯ��)
std::cout << "prev=" << prev << " cur=" << cur << " next=" << nextNode << "\n";