README ? LeetCode 124: Binary Tree Maximum Path Sum

한 줄 핵심: dfs(node)는 부모로 올라가는 단일 가지 최대합만 반환하고, 양쪽 자식을 모두 더한 경로 합은 전역 maxSum으로만 갱신한다.

문제 요약

경로(Path): 트리에서 아무 노드에서 시작/끝날 수 있고, 부모-자식 간 연결만 따라가며 사이클 없음.

목표: 가능한 모든 경로 중 노드 값 합의 최대값을 구하라.

정석 풀이 아이디어

dfs(node)의 의미를 명확히 정의한다:

반환값: node에서 시작해 부모 방향으로 올라갈 때 가져갈 수 있는 단일 가지 최대합 (음수면 0으로 끊음).

전역 변수 maxSum으로 답을 유지한다:

node를 **중간(봉우리)**로 삼아 left + node->val + right로 양갈래 경로를 시도해 보고, maxSum를 갱신한다.

부모에게는 node->val + max(left, right)만 단일 가지로 반환한다.

C++ 레퍼런스 구현

class Solution {
public:
    int maxSum;
    int maxPathSum(TreeNode* root) {
        maxSum = root->val; // 모든 노드 값이 음수일 수 있으니 루트로 초기화
        dfs(root);
        return maxSum;
    }

    int dfs(TreeNode* node) {
        if (!node) return 0;
        int left  = max(0, dfs(node->left));   // 음수면 경로 끊기
        int right = max(0, dfs(node->right));  // 음수면 경로 끊기

        // node를 봉우리로 하는 경로(좌-노드-우)로 전역 답 갱신
        maxSum = max(maxSum, left + right + node->val);

        // 부모에게는 한쪽 가지로만 연결 가능
        return node->val + max(left, right);
    }
};

왜 이렇게 동작하나?

부모로 올라가는 경로는 한 방향만 선택 가능 ⇒ max(left, right)만 택한다.

최댓값 후보는 현재 노드에서 좌+중앙+우가 될 수 있음 ⇒ maxSum로만 갱신.

음수 경로는 이득이 없음 ⇒ 0으로 잘라서 이어붙이지 않음.

자주 하는 실수

dfs가 양쪽 합을 그대로 리턴 → 부모에서 두 갈래를 동시에 이어붙이는 비정상 경로 발생.

maxSum를 **루트 0 또는 -∞**로 두고 시작 → 모든 노드가 음수일 때 오답.

자식이 nullptr일 때 처리 누락.

예시 워크스루

트리

   -10
   /  \
  9    20
      /  \
     15   7

dfs(15)=15, dfs(7)=7

dfs(20): left=15, right=7 → maxSum=max(maxSum, 15+20+7)=42 → 반환은 20+max(15,7)=35

dfs(9)=9

루트 -10: left=9, right=35 → maxSum=max(42, 9-10+35=34)=42 → 반환은 -10+max(9,35)=25

최종 maxSum=42

엣지 케이스 체크리스트



시간·공간 복잡도

시간: O(N) ? 각 노드를 한 번씩 방문.

공간: O(H) ? 재귀 스택(트리 높이). Skewed 트리에서 H?N.

빠른 점검(메모용)

dfs 반환: 단일 가지 최대합.

maxSum 갱신: left + node + right.

음수는 0으로 끊기.

maxSum 초기화는 루트 값.

연습용 테스트 케이스

[-3] →  -3

[1,2,3] → 6

[-10,9,20,null,null,15,7] → 42

[2,-1] → 2

[-1,-2,-3] → -1

변형/확장 아이디어

경로 길이까지 함께 구하기 (합이 최대인 경로의 노드 수/리스트 추적).

엣지 가중치가 있는 경우로 확장.

k-ary 트리에서 동일 아이디어 적용: 반환은 한 갈래, 갱신은 다 갈래 합산.

디버깅 팁

각 노드에서 (left, right, node->val, return, maxSum)을 로그로 찍어 의미 검증.

음수 절단(max(0, ...))이 제대로 적용되는지, 반환과 갱신이 역할 분리되는지 확인.