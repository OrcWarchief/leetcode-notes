Add Two Numbers
연결 리스트로 표현된 두 비음수 정수를 더하는 고전 문제(LeetCode #2). 
각 노드에는 한 자리 숫자(0?9)가 담겨 있고, 자리수는 역순(ones → tens → hundreds …)으로 저장됩니다. 
두 리스트의 합을 같은 형식의 새 연결 리스트로 반환하세요.

문제 설명
입력:

l1, l2 ? 각 노드가 한 자리 수를 담는 단일 연결 리스트.

숫자는 역순으로 저장됨. 예: 342는 2 -> 4 -> 3.

출력:

두 수의 합을 나타내는 연결 리스트(역순).

예:

rust
복사
l1 = 2 -> 4 -> 3   (342)
l2 = 5 -> 6 -> 4   (465)
-----------------------------
ans = 7 -> 0 -> 8  (807)
핵심 아이디어
숫자를 통째로 정수형에 담아 더하면 오버플로 위험이 큽니다. 대신 **자리수 단위로 더하면서 캐리(carry)**를 전파합니다.

매 단계에서 x = l1의 현재 자리, y = l2의 현재 자리.

s = x + y + carry

새 노드 값은 s % 10, 다음 캐리는 s / 10

l1, l2 포인터를 각각 다음 노드로 이동

둘 다 끝나도 carry가 남아 있으면 마지막으로 노드 추가

의사코드
kotlin
복사
carry = 0
dummy = 새 노드(0)
cur = dummy

while l1 또는 l2 또는 carry 존재:
    x = (l1 ? l1.val : 0)
    y = (l2 ? l2.val : 0)
    s = x + y + carry
    carry = s / 10
    cur.next = 새 노드(s % 10)
    cur = cur.next
    l1 = (l1 ? l1.next : null)
    l2 = (l2 ? l2.next : null)

return dummy.next
C++ 구현
cpp
복사
// 단일 연결 리스트 정의 (LeetCode 기본)
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* cur = &dummy;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int x = (l1 ? l1->val : 0);
            int y = (l2 ? l2->val : 0);
            int s = x + y + carry;

            carry = s / 10;
            cur->next = new ListNode(s % 10);
            cur = cur->next;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        return dummy.next;
    }
};
시간·공간 복잡도
시간: O(max(m, n)) ? 모든 자리(노드)를 한 번씩 방문

공간: O(max(m, n)) ? 결과 리스트 길이(추가 보조 공간은 O(1))

엣지 케이스
한 리스트가 더 길 때: 부족한 자리는 0으로 처리

최종 캐리: 예) 5 -> 5 + 5 -> 5 = 0 -> 1 -> 1

0만 있는 입력: 0 + 0 = 0

매우 긴 리스트: 정수형 캐스팅 없이 자리수 합으로 처리하므로 안전

자주 하는 실수
오버플로: int/long long에 숫자를 통째로 담아 더하기

헤드 처리 실수: 더미(dummy) 노드를 안 써서 첫 노드 연결이 꼬임

스택 변수 주소 보관: ListNode next; ans->next = &next; 처럼 지역 변수 주소를 연결하면 Dangling Pointer 발생

마지막 carry 누락: 마지막에 carry가 1이면 노드를 하나 더 추가해야 함

테스트 케이스
기본

ini
복사
l1 = [2,4,3], l2 = [5,6,4] → [7,0,8]
캐리 전파

ini
복사
l1 = [9,9,9,9], l2 = [1] → [0,0,0,0,1]
길이 다름

ini
복사
l1 = [0], l2 = [0,1,2] → [0,1,2]
둘 다 0

ini
복사
l1 = [0], l2 = [0] → [0]
확장/변형 문제
정방향 저장(Forward Order): 자리수가 앞에서부터 저장(예: 342는 3 -> 4 -> 2).
해결: 스택 두 개로 뒤집어 더하거나, 리스트를 반전(reverse)해서 같은 로직 적용 후 다시 되돌림. (LeetCode #445)

왜 “정수로 합쳐서 더하기”가 안 좋을까?
입력 길이 제한이 크면 어떤 고정 폭 정수형도 넘칠 수 있습니다.

언어마다 정수 범위가 달라 휴대성(portability)도 떨어집니다.

자리수 합 알고리즘은 오버플로 없이 항상 동작하고, 구현도 간단합니다.

참고 팁
더미 노드 패턴은 단일 연결 리스트 생성 시 헤드/테일 처리를 단순화합니다.

반복문 조건을 while (l1 || l2 || carry)로 두면 마무리 케이스가 깔끔합니다.

입력 리스트를 수정하지 않습니다(불변 유지).