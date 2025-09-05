2115. Find All Possible Recipes from Given Supplies

언어: C++
핵심 주제: 위상 정렬(Topological Sort), 그래프, BFS, 해시 테이블

문제 요약

recipes[i]는 i번째 레시피의 이름.

ingredients[i]는 i번째 레시피를 만들기 위해 필요한 재료들(문자열).

supplies는 처음에 보유하고 있는 재료(문자열) 목록.

어떤 레시피의 이름도 다른 레시피의 재료로 쓰일 수 있음. 즉, 레시피를 만들면 그 레시피 이름도 새로운 재료가 되어 다른 레시피를 만들 수 있다.

만들 수 있는 모든 레시피 이름을 반환.

단순히 ingredients[i]가 supplies에 전부 포함되는지만 체크하면 **연쇄 제작(레시피 → 재료)**을 처리하지 못하므로 오답입니다.

아이디어

레시피/재료 관계를 방향 그래프로 모델링합니다.

노드: 문자열(재료 또는 레시피 이름)

간선: ingredient → recipe (이 재료를 얻어야 해당 레시피를 만들 수 있음)

각 레시피의 진입 차수(indegree) = 필요한 고유 재료 개수

큐를 supplies로 초기화하고 BFS 진행:

큐에서 꺼낸 문자열 cur을 재료로 필요로 하는 모든 레시피의 indegree를 1씩 감소.

어떤 레시피의 indegree가 0이 되면 → 제작 가능: 결과에 추가하고, 그 레시피 이름을 새로운 재료로 큐에 넣어 연쇄 제작을 이어감.

이 방식이면

연쇄 의존(레시피가 레시피를 필요로 함)

사이클(깨지지 않는 순환 의존은 절대 0이 되지 않음)
을 자연스럽게 처리할 수 있습니다.

복잡도

N = 레시피 수, M = 모든 레시피의 재료 총합(중복 포함)

시간: O(N + M)
(간선 구성 M, 각 간선은 BFS 중 최대 한 번만 처리)

공간: O(N + M)
(그래프 인접 리스트, indegree, 큐, 해시 세트 등)

구현 (C++)
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
        // 그래프: ingredient -> recipes that need it
        unordered_map<string, vector<string>> graph;
        // 각 recipe의 남은 필요 고유 재료 수
        unordered_map<string, int> indeg;

        const int n = (int)recipes.size();

        // 각 레시피의 재료를 고유화(동일 재료 중복 등장 방지: 문제엔 잘 없지만 안전)
        for (int i = 0; i < n; ++i) {
            unordered_set<string> uniq(ingredients[i].begin(), ingredients[i].end());
            for (const string& ing : uniq) {
                graph[ing].push_back(recipes[i]);
                ++indeg[recipes[i]];
            }
        }

        // BFS 큐 초기화: 처음 보유한 supplies
        queue<string> q;
        unordered_set<string> seen; // 큐 중복 방지
        for (const string& s : supplies) {
            if (seen.insert(s).second) q.push(s);
        }

        vector<string> ans;

        // 빈 재료(필요 재료 0) 레시피가 있다면 바로 생산
        for (const string& r : recipes) {
            if (indeg[r] == 0) {        // 존재하지 않으면 0으로 취급됨
                ans.push_back(r);
                if (seen.insert(r).second) q.push(r); // r 자체도 새로운 재료가 됨
            }
        }

        // BFS: 재료/레시피를 소비하며 의존도를 깎음
        while (!q.empty()) {
            string cur = q.front(); q.pop();

            auto it = graph.find(cur);
            if (it == graph.end()) continue; // 이 재료를 필요로 하는 레시피가 없음

            for (const string& rec : it->second) {
                // rec의 남은 필요 재료 수 감소
                if (--indeg[rec] == 0) {
                    ans.push_back(rec);          // 제작 가능
                    if (seen.insert(rec).second) // 새 재료로 큐에
                        q.push(rec);
                }
            }
        }
        return ans;
    }
};

구현 포인트

unordered_map/unordered_set을 사용해 평균 O(1) 탐색/갱신.

indeg는 operator[] 사용 시 자동 0 초기화 효과가 있으므로 따로 초기화하지 않아도 됨.

중복 재료 제거(선택): 한 레시피의 동일 재료가 여러 번 나올 경우를 방지하기 위해 unordered_set으로 고유화.

레시피의 필요 재료가 0개라면 즉시 만들 수 있으므로, 초기에 큐와 결과에 넣어줌.

예시
recipes     = ["bread", "sandwich", "burger"]
ingredients = [
  ["yeast", "flour"],
  ["bread", "meat"],
  ["sandwich", "lettuce"]
]
supplies    = ["yeast", "flour", "meat", "lettuce"]


진행:

supplies로 yeast, flour, meat, lettuce를 큐에 넣고 BFS 시작.

yeast, flour 처리 → bread의 indegree가 0 → bread 제작, 큐에 bread 추가.

bread, meat 처리 → sandwich 제작, 큐에 sandwich 추가.

sandwich, lettuce 처리 → burger 제작, 큐에 burger 추가.

결과: ["bread", "sandwich", "burger"]

코너 케이스 체크리스트

레시피 간 사이클: 외부 supplies가 하나도 끊어주지 않으면 절대 0이 되지 않음 → 결과에 없음.

재료가 초기 supplies에도 없고, 어떤 레시피로도 만들 수 없음 → 해당 레시피는 불가.

레시피 이름이 다른 레시피의 재료로 등장하는 경우 → BFS로 자연 처리.

(드물게) 빈 재료 레시피 → 즉시 제작 가능 처리 포함.

(옵션) 한 레시피에 중복 재료 등장 → 고유화로 방지.

대안: DFS + 메모이제이션

각 문자열(재료/레시피)에 대해 “만들 수 있는가”를 DFS로 판별하며 결과를 캐싱.

사이클 검출을 위해 방문 상태(미방문/방문중/방문완료) 관리 필요.

구현은 간결하지만, 사이클·중복 호출 관리가 까다로울 수 있음. 성능은 BFS와 유사.