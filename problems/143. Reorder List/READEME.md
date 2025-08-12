LeetCode 143 ? Reorder List (README)
문제 요약
단일 연결 리스트 L0 → L1 → … → Ln을 **제자리(in?place)**에서
L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → … 형태로 재배열하라.

노드 자체를 재배치해야 하며, 값만 교환하거나 새 노드를 만들면 안 됨

추가 공간은 O(1) (재귀 콜스택도 공간으로 간주)

예: 1→2→3→4→5 → 1→5→2→4→3

핵심 아이디어 (3단계)
중간 찾기: 빠른/느린 포인터로 가운데 노드(slow)를 찾는다.

뒤쪽 반 역순: slow->next부터 끝까지 역순으로 뒤집는다.

교차 병합: 앞반(원래 head)과 뒤반(역순 결과)을 번갈아 연결한다.

이 접근은 모든 길이(짝/홀)에 대해 O(n) 시간, O(1) 공간으로 동작한다.

알고리즘 상세
1) 가운데 찾기 (Fast/Slow)
일반적으로 while (fast && fast->next) 사용.

짝수 길이일 때 slow는 오른쪽 가운데에서 멈춘다.

대안으로 while (fast->next && fast->next->next)를 쓰면 왼쪽 가운데에서 멈춘다.

어느 쪽이든 이후 단계(분리·역순·교차)가 맞다면 올바르게 동작한다.

2) 분리 + 역순
second = slow->next; slow->next = nullptr;로 앞/뒤 리스트를 분리한다.

second를 반복문으로 역순(reverse) 처리한다.

3) 교차 병합 (Weave/Merge)
포인터 두 개(p1=head, p2=역순리스트)로 진행.

각 단계에서 다음 포인터를 미리 저장해 둔 뒤, p1→p2→p1next 순서로 잇는다.

실수 방지를 위해 **뒤쪽 리스트 기준(while (p2))**으로 루프를 돌면 깔끔하다.

정답 구현 (C++)
cpp
복사
// 단일 연결 리스트 정의
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// O(n) time, O(1) extra space
void reorderList(ListNode* head) {
    if (!head || !head->next) return;

    // 1) 가운데 찾기 (짝수 길이에서 slow는 오른쪽 가운데)
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 2) 뒤쪽 반 분리 + 역순
    ListNode* second = slow->next;
    slow->next = nullptr;             // 앞/뒤 리스트 분리 (중요)
    ListNode* prev = nullptr;
    while (second) {
        ListNode* nxt = second->next;
        second->next = prev;
        prev = second;
        second = nxt;
    }
    // prev: 역순이 끝난 뒤쪽 반의 머리 (Ln, Ln-1, ...)

    // 3) 교차 병합 (뒤쪽 리스트 기준)
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
정확성 스케치
가운데에서 분리 후 뒤쪽 반을 역순으로 만들면 노드들이 Ln, Ln-1, … 순으로 선두에 위치한다.

앞반과 뒤반을 번갈아 연결하면 요구하는 순서 L0, Ln, L1, Ln-1, …가 된다.

각 노드는 최대 몇 번만 이동/접근하므로 시간은 O(n)이고, 추가 구조를 쓰지 않아 공간은 O(1)이다.

자주 발생하는 실수 체크리스트
 head==nullptr 또는 head->next==nullptr 처리 누락

 slow->next = nullptr로 분리하지 않아 사이클/무한루프 발생

 역순을 slow에서 시작(오류) ? 반드시 slow->next부터

 교차 병합에서 다음 포인터(n1, n2)를 먼저 저장하지 않아 링크 손실

 뒤쪽 기준 루프(while (p2)) 미사용으로 꼬리 처리 실수

 새 노드 생성/값 복사 사용 (문제 제약 위반)

왜 vector + new 방식이 틀리나?

값만 복사하여 새 리스트를 만들고, 원본 노드의 next를 수정하지 않기 때문.

LeetCode 시그니처가 void reorderList(ListNode* head)라 head 자체를 바꿀 수도 없음.

결과적으로 호출자는 여전히 “원본 리스트”를 보게 된다. (게다가 in-place 제약 위반)

예시 추적 (입력: 0→1→2→3)
가운데 찾기 → slow=2

분리: 앞 0→1→2, 뒤 3 (역순해도 3)

교차: 0→3→1→2

복잡도
시간: O(n) ? fast/slow, 역순, 교차 병합 각각 선형

공간: O(1) ? 추가 컨테이너/재귀 미사용

미니 테스트 헬퍼 (로컬에서 확인용)
cpp
복사
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

// 위의 reorderList 함수 붙여넣기

int main(){
    auto h = build({0,1,2,3,4});
    reorderList(h);
    print(h); // 기대: 0 4 1 3 2
}
관련/응용 문제
Reverse Linked List

Middle of the Linked List

Palindrome Linked List

Merge Two Sorted Lists

Remove Nth Node From End of List

Odd Even Linked List

Rotate List

Sort List

요약
분리 → 역순 → 교차 3단계만 지키면 안정적으로 해결 가능.

fast/slow 조건은 둘 다 가능(fast && fast->next / fast->next && fast->next->next),
이후 절차만 일관되게 맞추면 된다.