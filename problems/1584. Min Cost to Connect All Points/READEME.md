1584. Min Cost to Connect All Points
LeetCode 1584 ? Min Cost to Connect All Points

문제 요약
2D 평면 상의 n개 점이 주어질 때, 두 점 i, j를 잇는 간선의 가중치는 맨해튼 거리
|xi - xj| + |yi - yj| 입니다. 모든 점을 연결하는 최소 스패닝 트리(MST) 의 총 비용을 구하세요.

입력: points[i] = [xi, yi], 1 <= n <= 1000

출력: 모든 점을 하나로 연결하는 최소 비용 (정수)

핵심 아이디어

이 문제는 완전 그래프(정점 n, 간선 n(n-1)/2)에서 간선 가중치가 맨해튼 거리인 경우의 MST 비용을 묻는 고전 문제입니다.
MST를 구하는 대표 알고리즘은 Prim 과 Kruskal(DSU) 입니다.

Prim (권장): 간선을 전부 만들지 않고, “현재 트리에서 가장 가까운 정점”을 매번 확장합니다.

시간복잡도: O(n^2) (간단한 배열 구현)

공간복잡도: O(n)

n ≤ 1000에서 가장 단순하고 빠릅니다.

Kruskal + DSU: 모든 간선을 만들어 정렬 후, 사이클이 생기지 않도록 유니온합니다.

시간복잡도: O(n^2 log n) (간선 수가 ~ n^2/2)

공간복잡도: O(n^2) (간선 저장)

구현은 쉽지만 메모리/시간 오버헤드가 큽니다.

왜 Prim이 유리한가?
이 문제는 인접 리스트가 아니라 완전 그래프이기 때문에, Prim을 “간선을 즉시 계산” 방식으로 구현하면 간선 목록을 만들 필요가 없습니다. n=1000에서 O(n^2)은 충분히 빠르고, 메모리도 절약됩니다.

정답 검증 스케치 (Correctness)

컷(Cut) 성질: MST에서는 임의의 컷을 가르는 모든 간선 중 최소 가중치 간선은 반드시 MST에 포함됩니다.

Prim 은 매 단계에서 “현재 트리와 바깥 정점을 잇는 간선 중 최솟값”을 선택하므로 컷 성질을 반복 적용하는 알고리즘입니다. 따라서 항상 MST를 구성합니다.

Kruskal 은 간선을 가중치 오름차순으로 보며 사이클이 생기지 않는 간선만 채택합니다. 이는 사이클 성질(사이클의 최대 간선은 MST에 포함되지 않음)에 의해 옳습니다.

구현 1: Prim ? O(n²), 간선 리스트 없음 (권장 C++)
#include <vector>
#include <climits>
#include <cstdlib>   // std::abs
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        const int n = (int)points.size();
        vector<int> minDist(n, INT_MAX);  // 각 정점이 현재 MST와 연결되는 최소 비용
        vector<char> inMST(n, 0);         // MST 포함 여부
        minDist[0] = 0;

        long long total = 0;               // 합은 overflow 방지를 위해 long long 권장

        for (int iter = 0; iter < n; ++iter) {
            // 1) 아직 MST에 포함되지 않은 정점 중 key(=minDist)가 최소인 정점 u 선택
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!inMST[v] && (u == -1 || minDist[v] < minDist[u])) {
                    u = v;
                }
            }

            inMST[u] = 1;
            total += minDist[u];

            // 2) u를 통해 다른 정점으로 가는 비용으로 minDist 갱신
            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int d = std::abs(points[u][0] - points[v][0]) +
                            std::abs(points[u][1] - points[v][1]);
                    if (d < minDist[v]) minDist[v] = d;
                }
            }
        }

        return (int)total; // LeetCode 시그니처가 int이므로 캐스팅
    }
};

복잡도

시간: O(n^2)

공간: O(n)

구현 2: Kruskal + DSU ? O(n² log n) (간선 생성)
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

        // 모든 간선 생성 (i < j)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int w = std::abs(points[i][0] - points[j][0]) +
                        std::abs(points[i][1] - points[j][1]);
                edges.push_back({i, j, w});
            }
        }

        // 가중치 오름차순 정렬
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });

        DSU dsu(n);
        long long total = 0;
        int used = 0;

        // 간선 선택
        for (const auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total += e.w;
                if (++used == n - 1) break; // MST 완성되면 조기 종료
            }
        }
        return (int)total;
    }
};

복잡도

시간: O(n^2 log n) (간선 정렬 지배)

공간: O(n^2) (간선 저장)

자주 틀리는 포인트 (Pitfalls)

맨해튼 거리 계산 실수
|xi - xj| + |yi - yj| 에서 y 차이를 x로 잘못 쓰는 경우가 잦습니다. std::abs 를 사용하세요.

자기 자신 간선 생성
i == j 간선은 필요 없습니다. (Kruskal이면 j = i + 1부터)

조기 종료 누락
MST는 간선 n-1개가 선택되면 종료할 수 있습니다.

오버플로
누적 합은 long long에 저장하는 것이 안전합니다. (리턴은 int 시그니처에 맞춰 캐스팅)

DSU 최적화
경로 압축 + rank/size 우선을 꼭 사용하세요.

예시 테스트
1) [[0,0]]                   -> 0
2) [[0,0],[2,2],[3,10],[5,2],[7,0]] -> 20
3) [[3,12],[-2,5],[-4,1]]    -> 18

알고리즘 선택 가이드
조건	추천
n ≤ 1000, 구현 단순/빠른 풀이	Prim O(n²)
DSU 연습, 모든 간선 생성이 허용될 때	Kruskal + DSU
더 빠른 이론적 한계 추구	고급 Manhattan-MST 기법(좌표 변환 + 스위핑 + Fenwick 등) ? 대회/연구용, 실전 LeetCode에선 과합니다

참고: 맨해튼 거리의 특수 구조를 이용하면 후보 간선을 선별해 O(n log n) 까지 줄일 수 있지만, 구현 난도가 높습니다.

면접에서 말할 포인트

“완전 그래프 MST + 맨해튼 거리” → Prim O(n²) 로 간선 없이 푸는 게 베스트.

컷/사이클 성질로 정당성 설명.

누적 비용 오버플로 주의, 구현에서 abs/자기 간선/조기 종료 등 버그 포인트 콕 집기.

복습 체크리스트

 Prim: 배열 기반 O(n²) 로 구현했는가?

 누적 합 long long 처리했는가?

 Manhattan 거리 계산에서 x, y 모두 정확히 abs로 처리했는가?

 Kruskal 시 i < j만 간선 생성하고, n-1개에서 종료하는가?

 DSU: 경로 압축 + rank/size 우선?