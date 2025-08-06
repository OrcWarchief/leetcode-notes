README ??LeetCode?269?: Alien Dictionary
본 문서는 “나중에 이것만 읽어도 문제와 해법을 바로 떠올릴 수 있도록”
핵심 아이디어와 구현 요령을 요약합니다. 풀이 언어는 C++17 기준입니다.

1. 문제 요약
배경?: 불규칙한 외계 언어 단어 목록이 ‘사전 순’으로 정렬돼 있다.

목표?: 알파벳(소문자 a?z) 간의 상대적 순서를 추론하여 모든 글자를 나열하라.

조건?

목록에 등장한 문자만 결과에 포함.

가능한 순서가 여러 개면 아무 것이나 반환.

불가능하거나 모순이 있으면 빈 문자열 "" 반환.

입력	출력
vector<string> words (N ≤ 1???10⁴,	string order ? 유효한 알파벳 순서 또는
각 길이 ≤ 1???10³)	빈 문자열

2. 핵심 아이디어???“위상 정렬(Topological Sort)”
그래프 모델링

각 문자를 노드로, 첫 번째 불일치 글자 쌍 (c1,?c2) 에 대해 c1 → c2 유향 간선을 추가.

동일 접두사가 더 긴 단어 앞에 오면("abc", "ab") 모순?→?invalid.

위상 정렬 수행

진입 차수(indegree) 가 0인 노드를 큐에 삽입 → BFS(Kahn) 진행.

방문한 순서가 곧 알파벳 순서.

최종적으로 방문 노드 수 == 등장 문자 수 여야 유효.

3. 알고리즘 단계별 정리
단계	설명	복잡도
1	등장한 모든 문자 추출, 노드 초기화	O(Σ
2	인접 리스트 & indegree 구축	O(Σ
3	Kahn 위상 정렬	O(V?+?E) ≤ 26?+?E
4	결과 길이 검증	O(1)

전체?O(Σ|word|) (E ≤ 25?×?25 최악) ? 입력 크기에 선형.

4. 자주 틀리는 포인트 ?
케이스	원인	대응
["abc","ab"]	접두사 모순	길이 비교 후 즉시 fail
중복 간선	같은 (c1,c2) 반복	unordered_set 로 dedup
고립 문자	간선 0개	indegree 0 → 큐 초기에 삽입
사이클	indegree 소진 안 됨	방문 수 mismatch 로 검출

5. 정당성 증명 스케치
간선 생성의 soundness

사전 순 배열에서 첫 불일치 글자만 순서를 결정함은 문자열 비교 정의에 부합.

위상 정렬의 completeness

DAG 에 대해 Kahn 은 모든 가능한 topological ordering 중 하나를 반환.

모순 검출

접두사 예외 및 사이클 검출 조건이 문제의 “불가능” 경우와 정확히 대응.

6. C++17 구현 핵심 코드
cpp
복사
string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> g;
    array<int, 26> indeg{};              // 0?init
    array<bool, 26> seen{};              // 등장한 문자
    // 1. 모든 문자 등록
    for (auto& w : words)
        for (char c : w) seen[c - 'a'] = true;

    // 2. 간선 구축
    for (int i = 0; i + 1 < words.size(); ++i) {
        string &a = words[i], &b = words[i + 1];
        if (a.size() > b.size() && a.rfind(b,0) == 0) return ""; // 접두사 모순
        int len = min(a.size(), b.size());
        for (int k = 0; k < len; ++k)
            if (a[k] != b[k]) {
                if (g[a[k]].insert(b[k]).second)        // 새 간선
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
    // 4. 검증
    for (int i = 0; i < 26; ++i)
        if (seen[i]) { if (order.find('a'+i) == string::npos) return ""; }

    return order;
}
Tip?: unordered_map<char, unordered_set<char>> 로 중복 간선을 자동 제거.

7. 빌드 & 실행
bash
복사
g++ -std=c++17 -O2 alien_dictionary.cpp -o alien
./alien < input.txt
8. 회고 & 확장 아이디어
DFS + 색칠법 으로도 위상 정렬 가능 (post?order 역순).

추가 제약 조건(예: 알파벳 52개, 유니코드) 도 동일 로직 확장 가능.

실제 언어 모델링 시 확률적 순서(edge weight) →?Kahn 대신 위상 정렬 + 우선순위 큐 고려.

? 기억해야 할 한 문장
“첫 불일치 글자를 간선으로 ? DAG 인지 확인 후 위상 정렬로 순서 도출!”

작성?: 2025?08?06, 성민 Ryu