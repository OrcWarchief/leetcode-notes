README ??LeetCode?269?: Alien Dictionary
�� ������ �����߿� �̰͸� �о ������ �ع��� �ٷ� ���ø� �� �ֵ��ϡ�
�ٽ� ���̵��� ���� ����� ����մϴ�. Ǯ�� ���� C++17 �����Դϴ�.

1. ���� ���
���?: �ұ�Ģ�� �ܰ� ��� �ܾ� ����� ������ �������� ���ĵ� �ִ�.

��ǥ?: ���ĺ�(�ҹ��� a?z) ���� ����� ������ �߷��Ͽ� ��� ���ڸ� �����϶�.

����?

��Ͽ� ������ ���ڸ� ����� ����.

������ ������ ���� ���� �ƹ� ���̳� ��ȯ.

�Ұ����ϰų� ����� ������ �� ���ڿ� "" ��ȯ.

�Է�	���
vector<string> words (N �� 1???10��,	string order ? ��ȿ�� ���ĺ� ���� �Ǵ�
�� ���� �� 1???10��)	�� ���ڿ�

2. �ٽ� ���̵��???������ ����(Topological Sort)��
�׷��� �𵨸�

�� ���ڸ� ����, ù ��° ����ġ ���� �� (c1,?c2) �� ���� c1 �� c2 ���� ������ �߰�.

���� ���λ簡 �� �� �ܾ� �տ� ����("abc", "ab") ���?��?invalid.

���� ���� ����

���� ����(indegree) �� 0�� ��带 ť�� ���� �� BFS(Kahn) ����.

�湮�� ������ �� ���ĺ� ����.

���������� �湮 ��� �� == ���� ���� �� ���� ��ȿ.

3. �˰��� �ܰ躰 ����
�ܰ�	����	���⵵
1	������ ��� ���� ����, ��� �ʱ�ȭ	O(��
2	���� ����Ʈ & indegree ����	O(��
3	Kahn ���� ����	O(V?+?E) �� 26?+?E
4	��� ���� ����	O(1)

��ü?O(��|word|) (E �� 25?��?25 �־�) ? �Է� ũ�⿡ ����.

4. ���� Ʋ���� ����Ʈ ?
���̽�	����	����
["abc","ab"]	���λ� ���	���� �� �� ��� fail
�ߺ� ����	���� (c1,c2) �ݺ�	unordered_set �� dedup
�� ����	���� 0��	indegree 0 �� ť �ʱ⿡ ����
����Ŭ	indegree ���� �� ��	�湮 �� mismatch �� ����

5. ���缺 ���� ����ġ
���� ������ soundness

���� �� �迭���� ù ����ġ ���ڸ� ������ �������� ���ڿ� �� ���ǿ� ����.

���� ������ completeness

DAG �� ���� Kahn �� ��� ������ topological ordering �� �ϳ��� ��ȯ.

��� ����

���λ� ���� �� ����Ŭ ���� ������ ������ ���Ұ��ɡ� ���� ��Ȯ�� ����.

6. C++17 ���� �ٽ� �ڵ�
cpp
����
string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> g;
    array<int, 26> indeg{};              // 0?init
    array<bool, 26> seen{};              // ������ ����
    // 1. ��� ���� ���
    for (auto& w : words)
        for (char c : w) seen[c - 'a'] = true;

    // 2. ���� ����
    for (int i = 0; i + 1 < words.size(); ++i) {
        string &a = words[i], &b = words[i + 1];
        if (a.size() > b.size() && a.rfind(b,0) == 0) return ""; // ���λ� ���
        int len = min(a.size(), b.size());
        for (int k = 0; k < len; ++k)
            if (a[k] != b[k]) {
                if (g[a[k]].insert(b[k]).second)        // �� ����
                    ++indeg[b[k] - 'a'];
                break;
            }
    }

    // 3. Kahn
    queue<char> q;
    for (int i = 0; i < 26; ++i)
        if (seen[i] && indeg[i] == 0) q.push('a' + i);

    string order;
    while (!q.empty()) {
        char u = q.front(); q.pop();
        order += u;
        for (char v : g[u])
            if (--indeg[v - 'a'] == 0) q.push(v);
    }
    // 4. ����
    for (int i = 0; i < 26; ++i)
        if (seen[i]) { if (order.find('a'+i) == string::npos) return ""; }

    return order;
}
Tip?: unordered_map<char, unordered_set<char>> �� �ߺ� ������ �ڵ� ����.

7. ���� & ����
bash
����
g++ -std=c++17 -O2 alien_dictionary.cpp -o alien
./alien < input.txt
8. ȸ�� & Ȯ�� ���̵��
DFS + ��ĥ�� ���ε� ���� ���� ���� (post?order ����).

�߰� ���� ����(��: ���ĺ� 52��, �����ڵ�) �� ���� ���� Ȯ�� ����.

���� ��� �𵨸� �� Ȯ���� ����(edge weight) ��?Kahn ��� ���� ���� + �켱���� ť ���.

? ����ؾ� �� �� ����
��ù ����ġ ���ڸ� �������� ? DAG ���� Ȯ�� �� ���� ���ķ� ���� ����!��

�ۼ�?: 2025?08?06, ���� Ryu