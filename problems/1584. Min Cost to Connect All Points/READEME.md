1584. Min Cost to Connect All Points
LeetCode 1584 ? Min Cost to Connect All Points

���� ���
2D ��� ���� n�� ���� �־��� ��, �� �� i, j�� �մ� ������ ����ġ�� ����ư �Ÿ�
|xi - xj| + |yi - yj| �Դϴ�. ��� ���� �����ϴ� �ּ� ���д� Ʈ��(MST) �� �� ����� ���ϼ���.

�Է�: points[i] = [xi, yi], 1 <= n <= 1000

���: ��� ���� �ϳ��� �����ϴ� �ּ� ��� (����)

�ٽ� ���̵��

�� ������ ���� �׷���(���� n, ���� n(n-1)/2)���� ���� ����ġ�� ����ư �Ÿ��� ����� MST ����� ���� ���� �����Դϴ�.
MST�� ���ϴ� ��ǥ �˰����� Prim �� Kruskal(DSU) �Դϴ�.

Prim (����): ������ ���� ������ �ʰ�, ������ Ʈ������ ���� ����� �������� �Ź� Ȯ���մϴ�.

�ð����⵵: O(n^2) (������ �迭 ����)

�������⵵: O(n)

n �� 1000���� ���� �ܼ��ϰ� �����ϴ�.

Kruskal + DSU: ��� ������ ����� ���� ��, ����Ŭ�� ������ �ʵ��� ���Ͽ��մϴ�.

�ð����⵵: O(n^2 log n) (���� ���� ~ n^2/2)

�������⵵: O(n^2) (���� ����)

������ ������ �޸�/�ð� ������尡 Ů�ϴ�.

�� Prim�� �����Ѱ�?
�� ������ ���� ����Ʈ�� �ƴ϶� ���� �׷����̱� ������, Prim�� �������� ��� ��ꡱ ������� �����ϸ� ���� ����� ���� �ʿ䰡 �����ϴ�. n=1000���� O(n^2)�� ����� ������, �޸𸮵� ����˴ϴ�.

���� ���� ����ġ (Correctness)

��(Cut) ����: MST������ ������ ���� ������ ��� ���� �� �ּ� ����ġ ������ �ݵ�� MST�� ���Ե˴ϴ�.

Prim �� �� �ܰ迡�� ������ Ʈ���� �ٱ� ������ �մ� ���� �� �ּڰ����� �����ϹǷ� �� ������ �ݺ� �����ϴ� �˰����Դϴ�. ���� �׻� MST�� �����մϴ�.

Kruskal �� ������ ����ġ ������������ ���� ����Ŭ�� ������ �ʴ� ������ ä���մϴ�. �̴� ����Ŭ ����(����Ŭ�� �ִ� ������ MST�� ���Ե��� ����)�� ���� �ǽ��ϴ�.

���� 1: Prim ? O(n��), ���� ����Ʈ ���� (���� C++)
#include <vector>
#include <climits>
#include <cstdlib>   // std::abs
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        const int n = (int)points.size();
        vector<int> minDist(n, INT_MAX);  // �� ������ ���� MST�� ����Ǵ� �ּ� ���
        vector<char> inMST(n, 0);         // MST ���� ����
        minDist[0] = 0;

        long long total = 0;               // ���� overflow ������ ���� long long ����

        for (int iter = 0; iter < n; ++iter) {
            // 1) ���� MST�� ���Ե��� ���� ���� �� key(=minDist)�� �ּ��� ���� u ����
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!inMST[v] && (u == -1 || minDist[v] < minDist[u])) {
                    u = v;
                }
            }

            inMST[u] = 1;
            total += minDist[u];

            // 2) u�� ���� �ٸ� �������� ���� ������� minDist ����
            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int d = std::abs(points[u][0] - points[v][0]) +
                            std::abs(points[u][1] - points[v][1]);
                    if (d < minDist[v]) minDist[v] = d;
                }
            }
        }

        return (int)total; // LeetCode �ñ״�ó�� int�̹Ƿ� ĳ����
    }
};

���⵵

�ð�: O(n^2)

����: O(n)

���� 2: Kruskal + DSU ? O(n�� log n) (���� ����)
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct Edge { int u, v, w; };

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = (int)points.size();
        vector<Edge> edges;
        edges.reserve(n * (n - 1) / 2);

        // ��� ���� ���� (i < j)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int w = std::abs(points[i][0] - points[j][0]) +
                        std::abs(points[i][1] - points[j][1]);
                edges.push_back({i, j, w});
            }
        }

        // ����ġ �������� ����
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });

        DSU dsu(n);
        long long total = 0;
        int used = 0;

        // ���� ����
        for (const auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total += e.w;
                if (++used == n - 1) break; // MST �ϼ��Ǹ� ���� ����
            }
        }
        return (int)total;
    }
};

���⵵

�ð�: O(n^2 log n) (���� ���� ����)

����: O(n^2) (���� ����)

���� Ʋ���� ����Ʈ (Pitfalls)

����ư �Ÿ� ��� �Ǽ�
|xi - xj| + |yi - yj| ���� y ���̸� x�� �߸� ���� ��찡 ����ϴ�. std::abs �� ����ϼ���.

�ڱ� �ڽ� ���� ����
i == j ������ �ʿ� �����ϴ�. (Kruskal�̸� j = i + 1����)

���� ���� ����
MST�� ���� n-1���� ���õǸ� ������ �� �ֽ��ϴ�.

�����÷�
���� ���� long long�� �����ϴ� ���� �����մϴ�. (������ int �ñ״�ó�� ���� ĳ����)

DSU ����ȭ
��� ���� + rank/size �켱�� �� ����ϼ���.

���� �׽�Ʈ
1) [[0,0]]                   -> 0
2) [[0,0],[2,2],[3,10],[5,2],[7,0]] -> 20
3) [[3,12],[-2,5],[-4,1]]    -> 18

�˰��� ���� ���̵�
����	��õ
n �� 1000, ���� �ܼ�/���� Ǯ��	Prim O(n��)
DSU ����, ��� ���� ������ ���� ��	Kruskal + DSU
�� ���� �̷��� �Ѱ� �߱�	��� Manhattan-MST ���(��ǥ ��ȯ + ������ + Fenwick ��) ? ��ȸ/������, ���� LeetCode���� ���մϴ�

����: ����ư �Ÿ��� Ư�� ������ �̿��ϸ� �ĺ� ������ ������ O(n log n) ���� ���� �� ������, ���� ������ �����ϴ�.

�������� ���� ����Ʈ

������ �׷��� MST + ����ư �Ÿ��� �� Prim O(n��) �� ���� ���� Ǫ�� �� ����Ʈ.

��/����Ŭ ������ ���缺 ����.

���� ��� �����÷� ����, �������� abs/�ڱ� ����/���� ���� �� ���� ����Ʈ �� ����.

���� üũ����Ʈ

 Prim: �迭 ��� O(n��) �� �����ߴ°�?

 ���� �� long long ó���ߴ°�?

 Manhattan �Ÿ� ��꿡�� x, y ��� ��Ȯ�� abs�� ó���ߴ°�?

 Kruskal �� i < j�� ���� �����ϰ�, n-1������ �����ϴ°�?

 DSU: ��� ���� + rank/size �켱?