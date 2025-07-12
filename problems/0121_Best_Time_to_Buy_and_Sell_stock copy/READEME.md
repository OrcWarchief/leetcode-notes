# Copy List with Random Pointer (LeetCode 138)

> **문제 요약**  
> 단일 연결 리스트의 각 노드는 `next` 와 `random` 포인터를 가진다.  
> 동일한 구조와 값, 그리고 동일한 `random` 관계를 갖는 **깊은 복사본** 리스트의 헤더를 반환하라.

---

## 풀이 1 ? 해시맵 두 패스 (O(N) 공간)

| 단계 | 설명 | 핵심 코드 |
|------|------|-----------|
| 1. **노드 복사** | 원본을 순회하며 `new Node(cur->val)` 로 복사본을 만들고, `unordered_map<원본, 복사본>` 매핑을 저장 | `mp[cur] = new Node(cur->val);` |
| 2. **포인터 연결** | 다시 순회하면서 `clone->next = mp[cur->next];`<br>`clone->random = mp[cur->random];` 로 복사본끼리 연결 | 두 포인터 모두 `nullptr` 일 때도 안전하게 처리 |

```cpp
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    std::unordered_map<Node*, Node*> mp; // 원본 → 복사본

    for (Node* cur = head; cur; cur = cur->next)
        mp[cur] = new Node(cur->val);

    for (Node* cur = head; cur; cur = cur->next) {
        mp[cur]->next   = mp[cur->next];
        mp[cur]->random = mp[cur->random];
    }
    return mp[head];
}
풀이 2 ? Interleaving 3 패스 (O(1) 공간)
복사본 끼워넣기
A → B → C → A → A′ → B → B′ → C → C′

random 연결
clone->random = cur->random ? cur->random->next : nullptr;

원본·복사본 분리
지퍼(zipper)처럼 두 리스트를 다시 분리

cpp
복사
편집
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    // 1) 끼워넣기
    for (Node* cur = head; cur; cur = cur->next->next) {
        Node* clone = new Node(cur->val);
        clone->next = cur->next;
        cur->next   = clone;
    }

    // 2) random 설정
    for (Node* cur = head; cur; cur = cur->next->next)
        if (cur->random)
            cur->next->random = cur->random->next;

    // 3) 분리
    Node* newHead = head->next;
    for (Node* cur = head; cur; ) {
        Node* clone = cur->next;
        cur->next   = clone->next;          // 원본 복원
        cur         = cur->next;            // 다음 원본
        clone->next = cur ? cur->next : nullptr;
    }
    return newHead;
}
Complexity Comparison
풀이	시간	공간	장점	단점
해시맵	O(N)	O(N)	코드가 가장 직관적	메모리 증가
Interleaving	O(N)	O(1)	메모리 절약·캐시 효율 ↑	코드가 다소 복잡

빌드 & 실행
bash
복사
편집
g++ -std=c++17 -O2 -Wall main.cpp
./a.out        # 또는 LeetCode 등 온라인 저지에서 제출
main.cpp 에 두 풀이 중 하나만 포함해도 통과합니다.

참고 자료
LeetCode 138 ? Copy List with Random Pointer

Gayle Laakmann McDowell, Cracking the Coding Interview, 6th Ed., Q 2-7
