337. House Robber III
문제 요약

이진 트리의 각 노드에는 돈(val)이 들어있음.

같은 경로에서 부모와 자식을 동시에 털 수는 없음.

훔칠 수 있는 최대 금액을 구하는 문제.

핵심 아이디어 (DP on Tree)

각 노드에서 두 상태를 정의하면 됨:

rob(node) = 이 노드를 훔칠 때의 최대 금액
= val(node) + notRob(left) + notRob(right)

notRob(node) = 이 노드를 훔치지 않을 때의 최대 금액
= max(rob(left), notRob(left)) + max(rob(right), notRob(right))

구현 전략

후위 순회 DFS로 (rob, notRob)를 동시에 계산해 반환 (가장 간단, O(N)).

또는 두 함수(Rob/NotRob) + 메모이제이션으로 구현 (성민이 올린 코드 구조 그대로).

큐를 이용한 bottom-up 반복 구현도 가능하지만, DFS가 가장 정석.

최종 답

max(rob(root), notRob(root))