337. House Robber III
���� ���

���� Ʈ���� �� ��忡�� ��(val)�� �������.

���� ��ο��� �θ�� �ڽ��� ���ÿ� �� ���� ����.

��ĥ �� �ִ� �ִ� �ݾ��� ���ϴ� ����.

�ٽ� ���̵�� (DP on Tree)

�� ��忡�� �� ���¸� �����ϸ� ��:

rob(node) = �� ��带 ��ĥ ���� �ִ� �ݾ�
= val(node) + notRob(left) + notRob(right)

notRob(node) = �� ��带 ��ġ�� ���� ���� �ִ� �ݾ�
= max(rob(left), notRob(left)) + max(rob(right), notRob(right))

���� ����

���� ��ȸ DFS�� (rob, notRob)�� ���ÿ� ����� ��ȯ (���� ����, O(N)).

�Ǵ� �� �Լ�(Rob/NotRob) + �޸������̼����� ���� (������ �ø� �ڵ� ���� �״��).

ť�� �̿��� bottom-up �ݺ� ������ ����������, DFS�� ���� ����.

���� ��

max(rob(root), notRob(root))