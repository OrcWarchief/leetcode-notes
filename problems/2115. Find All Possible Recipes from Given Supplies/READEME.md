2115. Find All Possible Recipes from Given Supplies

���: C++
�ٽ� ����: ���� ����(Topological Sort), �׷���, BFS, �ؽ� ���̺�

���� ���

recipes[i]�� i��° �������� �̸�.

ingredients[i]�� i��° �����Ǹ� ����� ���� �ʿ��� ����(���ڿ�).

supplies�� ó���� �����ϰ� �ִ� ���(���ڿ�) ���.

� �������� �̸��� �ٸ� �������� ���� ���� �� ����. ��, �����Ǹ� ����� �� ������ �̸��� ���ο� ��ᰡ �Ǿ� �ٸ� �����Ǹ� ���� �� �ִ�.

���� �� �ִ� ��� ������ �̸��� ��ȯ.

�ܼ��� ingredients[i]�� supplies�� ���� ���ԵǴ����� üũ�ϸ� **���� ����(������ �� ���)**�� ó������ ���ϹǷ� �����Դϴ�.

���̵��

������/��� ���踦 ���� �׷����� �𵨸��մϴ�.

���: ���ڿ�(��� �Ǵ� ������ �̸�)

����: ingredient �� recipe (�� ��Ḧ ���� �ش� �����Ǹ� ���� �� ����)

�� �������� ���� ����(indegree) = �ʿ��� ���� ��� ����

ť�� supplies�� �ʱ�ȭ�ϰ� BFS ����:

ť���� ���� ���ڿ� cur�� ���� �ʿ�� �ϴ� ��� �������� indegree�� 1�� ����.

� �������� indegree�� 0�� �Ǹ� �� ���� ����: ����� �߰��ϰ�, �� ������ �̸��� ���ο� ���� ť�� �־� ���� ������ �̾.

�� ����̸�

���� ����(�����ǰ� �����Ǹ� �ʿ�� ��)

����Ŭ(������ �ʴ� ��ȯ ������ ���� 0�� ���� ����)
�� �ڿ������� ó���� �� �ֽ��ϴ�.

���⵵

N = ������ ��, M = ��� �������� ��� ����(�ߺ� ����)

�ð�: O(N + M)
(���� ���� M, �� ������ BFS �� �ִ� �� ���� ó��)

����: O(N + M)
(�׷��� ���� ����Ʈ, indegree, ť, �ؽ� ��Ʈ ��)

���� (C++)
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes,
                                  vector<vector<string>>& ingredients,
                                  vector<string>& supplies) {
        // �׷���: ingredient -> recipes that need it
        unordered_map<string, vector<string>> graph;
        // �� recipe�� ���� �ʿ� ���� ��� ��
        unordered_map<string, int> indeg;

        const int n = (int)recipes.size();

        // �� �������� ��Ḧ ����ȭ(���� ��� �ߺ� ���� ����: ������ �� ������ ����)
        for (int i = 0; i < n; ++i) {
            unordered_set<string> uniq(ingredients[i].begin(), ingredients[i].end());
            for (const string& ing : uniq) {
                graph[ing].push_back(recipes[i]);
                ++indeg[recipes[i]];
            }
        }

        // BFS ť �ʱ�ȭ: ó�� ������ supplies
        queue<string> q;
        unordered_set<string> seen; // ť �ߺ� ����
        for (const string& s : supplies) {
            if (seen.insert(s).second) q.push(s);
        }

        vector<string> ans;

        // �� ���(�ʿ� ��� 0) �����ǰ� �ִٸ� �ٷ� ����
        for (const string& r : recipes) {
            if (indeg[r] == 0) {        // �������� ������ 0���� ��޵�
                ans.push_back(r);
                if (seen.insert(r).second) q.push(r); // r ��ü�� ���ο� ��ᰡ ��
            }
        }

        // BFS: ���/�����Ǹ� �Һ��ϸ� �������� ����
        while (!q.empty()) {
            string cur = q.front(); q.pop();

            auto it = graph.find(cur);
            if (it == graph.end()) continue; // �� ��Ḧ �ʿ�� �ϴ� �����ǰ� ����

            for (const string& rec : it->second) {
                // rec�� ���� �ʿ� ��� �� ����
                if (--indeg[rec] == 0) {
                    ans.push_back(rec);          // ���� ����
                    if (seen.insert(rec).second) // �� ���� ť��
                        q.push(rec);
                }
            }
        }
        return ans;
    }
};

���� ����Ʈ

unordered_map/unordered_set�� ����� ��� O(1) Ž��/����.

indeg�� operator[] ��� �� �ڵ� 0 �ʱ�ȭ ȿ���� �����Ƿ� ���� �ʱ�ȭ���� �ʾƵ� ��.

�ߺ� ��� ����(����): �� �������� ���� ��ᰡ ���� �� ���� ��츦 �����ϱ� ���� unordered_set���� ����ȭ.

�������� �ʿ� ��ᰡ 0����� ��� ���� �� �����Ƿ�, �ʱ⿡ ť�� ����� �־���.

����
recipes     = ["bread", "sandwich", "burger"]
ingredients = [
  ["yeast", "flour"],
  ["bread", "meat"],
  ["sandwich", "lettuce"]
]
supplies    = ["yeast", "flour", "meat", "lettuce"]


����:

supplies�� yeast, flour, meat, lettuce�� ť�� �ְ� BFS ����.

yeast, flour ó�� �� bread�� indegree�� 0 �� bread ����, ť�� bread �߰�.

bread, meat ó�� �� sandwich ����, ť�� sandwich �߰�.

sandwich, lettuce ó�� �� burger ����, ť�� burger �߰�.

���: ["bread", "sandwich", "burger"]

�ڳ� ���̽� üũ����Ʈ

������ �� ����Ŭ: �ܺ� supplies�� �ϳ��� �������� ������ ���� 0�� ���� ���� �� ����� ����.

��ᰡ �ʱ� supplies���� ����, � �����Ƿε� ���� �� ���� �� �ش� �����Ǵ� �Ұ�.

������ �̸��� �ٸ� �������� ���� �����ϴ� ��� �� BFS�� �ڿ� ó��.

(�幰��) �� ��� ������ �� ��� ���� ���� ó�� ����.

(�ɼ�) �� �����ǿ� �ߺ� ��� ���� �� ����ȭ�� ����.

���: DFS + �޸������̼�

�� ���ڿ�(���/������)�� ���� ������ �� �ִ°����� DFS�� �Ǻ��ϸ� ����� ĳ��.

����Ŭ ������ ���� �湮 ����(�̹湮/�湮��/�湮�Ϸ�) ���� �ʿ�.

������ ����������, ����Ŭ���ߺ� ȣ�� ������ ��ٷο� �� ����. ������ BFS�� ����.