# Copy List with Random Pointer (LeetCode 138)

> **���� ���**  
> ���� ���� ����Ʈ�� �� ���� `next` �� `random` �����͸� ������.  
> ������ ������ ��, �׸��� ������ `random` ���踦 ���� **���� ���纻** ����Ʈ�� ����� ��ȯ�϶�.

---

## Ǯ�� 1 ? �ؽø� �� �н� (O(N) ����)

| �ܰ� | ���� | �ٽ� �ڵ� |
|------|------|-----------|
| 1. **��� ����** | ������ ��ȸ�ϸ� `new Node(cur->val)` �� ���纻�� �����, `unordered_map<����, ���纻>` ������ ���� | `mp[cur] = new Node(cur->val);` |
| 2. **������ ����** | �ٽ� ��ȸ�ϸ鼭 `clone->next = mp[cur->next];`<br>`clone->random = mp[cur->random];` �� ���纻���� ���� | �� ������ ��� `nullptr` �� ���� �����ϰ� ó�� |

```cpp
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    std::unordered_map<Node*, Node*> mp; // ���� �� ���纻

    for (Node* cur = head; cur; cur = cur->next)
        mp[cur] = new Node(cur->val);

    for (Node* cur = head; cur; cur = cur->next) {
        mp[cur]->next   = mp[cur->next];
        mp[cur]->random = mp[cur->random];
    }
    return mp[head];
}
Ǯ�� 2 ? Interleaving 3 �н� (O(1) ����)
���纻 �����ֱ�
A �� B �� C �� A �� A�� �� B �� B�� �� C �� C��

random ����
clone->random = cur->random ? cur->random->next : nullptr;

���������纻 �и�
����(zipper)ó�� �� ����Ʈ�� �ٽ� �и�

cpp
����
����
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    // 1) �����ֱ�
    for (Node* cur = head; cur; cur = cur->next->next) {
        Node* clone = new Node(cur->val);
        clone->next = cur->next;
        cur->next   = clone;
    }

    // 2) random ����
    for (Node* cur = head; cur; cur = cur->next->next)
        if (cur->random)
            cur->next->random = cur->random->next;

    // 3) �и�
    Node* newHead = head->next;
    for (Node* cur = head; cur; ) {
        Node* clone = cur->next;
        cur->next   = clone->next;          // ���� ����
        cur         = cur->next;            // ���� ����
        clone->next = cur ? cur->next : nullptr;
    }
    return newHead;
}
Complexity Comparison
Ǯ��	�ð�	����	����	����
�ؽø�	O(N)	O(N)	�ڵ尡 ���� ������	�޸� ����
Interleaving	O(N)	O(1)	�޸� ���ࡤĳ�� ȿ�� ��	�ڵ尡 �ټ� ����

���� & ����
bash
����
����
g++ -std=c++17 -O2 -Wall main.cpp
./a.out        # �Ǵ� LeetCode �� �¶��� �������� ����
main.cpp �� �� Ǯ�� �� �ϳ��� �����ص� ����մϴ�.

���� �ڷ�
LeetCode 138 ? Copy List with Random Pointer

Gayle Laakmann McDowell, Cracking the Coding Interview, 6th Ed., Q 2-7
