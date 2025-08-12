eetCode 206 ? Reverse Linked List (README)
문제 요약
단일 연결 리스트의 머리 포인터 head가 주어졌을 때, 리스트를 역순으로 뒤집어 새 머리 포인터를 반환하라.

입력: 1 → 2 → 3 → 4 → 5 → null

출력: 5 → 4 → 3 → 2 → 1 → null

핵심 아이디어
포인터를 네 줄로 뒤집는 반복(iterative) 인플레이스 풀이가 정석이다.

불변식(매 반복 시작 시 항상 참):

prev: 이미 뒤집힌 부분 리스트의 머리

cur: 아직 뒤집지 않은 부분 리스트의 머리

한 스텝에서 하는 일:

nextNode = cur->next ? 다음 노드 백업

cur->next = prev ? 현재 노드의 링크를 뒤로 돌림

prev = cur ? 뒤집힌 부분의 새 머리 갱신

cur = nextNode ? 남은 구간의 다음으로 전진

이걸 cur == nullptr 될 때까지 반복하면, 최종적으로 prev가 완전히 뒤집힌 리스트의 머리가 된다.

반복 풀이 (권장, O(1) 추가 메모리)
cpp
복사
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur  = head;

        while (cur != nullptr) {
            ListNode* nextNode = cur->next; // 1) 다음 노드 주소 백업
            cur->next = prev;               // 2) 링크 뒤집기
            prev = cur;                     // 3) prev를 새 머리로 이동
            cur = nextNode;                 // 4) 다음 노드로 전진
        }
        return prev; // 뒤집힌 리스트의 머리
    }
};
시간/공간 복잡도
시간: O(n) (각 노드를 한 번씩 방문)

공간: O(1) (추가 포인터 몇 개만 사용)

재귀 풀이 (간결하지만 스택 사용, O(n) 스택)
cpp
복사
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;

        ListNode* newHead = reverseList(head->next);
        head->next->next = head; // 뒤에서 앞으로 연결
        head->next = nullptr;    // 기존 앞으로 향하던 링크 끊기
        return newHead;
    }
};
주의
호출 깊이만큼 호출 스택 O(n) 사용. 입력이 매우 길면 스택 오버플로우 위험.

로직은 “맨 끝까지 내려간 뒤, 귀환하면서 링크를 뒤로 재배선”.

시각적 이해 (3노드 예시)
초기:

yaml
복사
prev: null
cur : [1] → [2] → [3] → null
1회전:

csharp
복사
nextNode=[2]
cur->next=prev(null) => [1]→null
prev=[1], cur=[2]→[3]→null
2회전:

csharp
복사
nextNode=[3]
cur->next=prev([1])  => [2]→[1]→null
prev=[2]→[1]→null, cur=[3]→null
3회전 후 종료:

ini
복사
prev=[3]→[2]→[1]→null
cur=null
에지 케이스
빈 리스트: head == nullptr → 그대로 nullptr 반환

원소 1개: 링크 뒤집어도 같음

매우 긴 리스트: 재귀 풀이 대신 반복 풀이 권장

자주 하는 실수 & 디버깅 팁
nextNode 백업을 생략: cur->next = prev 후 다음 노드를 잃어버림

대상 혼동:

cur->next = prev는 노드 내부 링크 수정

prev = cur는 포인터 변수의 대상(주소) 변경

진행 중간에 사이클이 생기면 순회가 끝나지 않음 → 단계별로 주소를 출력해 추적

cpp
복사
// 디버깅용 (주소 확인)
std::cout << "prev=" << prev << " cur=" << cur << " next=" << nextNode << "\n";