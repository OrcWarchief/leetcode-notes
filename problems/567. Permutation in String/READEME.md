README ? LeetCode?567 Permutation?in?String (C++)

1. 문제 요약
입력

s1: 길이 n ≤?10?000인 소문자 문자열

s2: 길이 m ≤?10?000인 소문자 문자열

출력

true?/?false ― s2 안에 s1의 순열(permutation) 이 연속 부분문자열로 존재하면 true, 아니면 false.

핵심

s1의 모든 문자 빈도를 정확히 갖는 길이 n짜리 구간이 s2에 존재하는지 검사.

2. 알고리즘 한눈에 보기
기법	이유
슬라이딩 윈도우	길이 n 고정 구간을 한 칸씩 이동하며 검사
고정 크기 빈도 배열(26)	알파벳만 다루므로 unordered_map보다 빠르고 메모리도 작음
차이 비교 O(1)	윈도 이동 시 “들어온 문자 +1, 나간 문자 ?1” 만으로 즉시 일치 여부 판단

결과적으로 O(m) 시간, O(1) 공간 달성.

3. 단계별 로직
사전 검사
n > m 이면 절대 불가 ⇒ 즉시 false.

필요 빈도(need)·현재 윈도(window) 배열 초기화

cpp
복사
int need[26] = {0}, window[26] = {0};
for (char c : s1) need[c - 'a']++;
for (int i = 0; i < n; ++i) window[s2[i] - 'a']++;
빈도 배열 비교

두 배열이 완전히 같으면 곧바로 true.

슬라이딩 (i = n … m-1)

오른쪽 새 문자 +1

왼쪽 가장 오래된 문자 -1

변화 후 두 배열이 일치하면 true.

끝까지 없었다면 false.

4. 핵심 코드 스니펫
cpp
복사
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        if (n > m) return false;

        int need[26] = {0}, window[26] = {0};
        for (char c : s1) need[c - 'a']++;
        for (int i = 0; i < n; ++i) window[s2[i] - 'a']++;

        auto same = [&](){
            for (int k = 0; k < 26; ++k)
                if (need[k] != window[k]) return false;
            return true;
        };
        if (same()) return true;

        for (int i = n; i < m; ++i) {
            window[s2[i] - 'a']++;          // in
            window[s2[i - n] - 'a']--;      // out
            if (same()) return true;
        }
        return false;
    }
};
5. 시간·공간 복잡도
복잡도
시간	`O(
공간	O(26) ⇒ 상수

6. 자주 틀리는 포인트
합계(sum)만 비교

'ab'(0?+?1) vs 'c'(2): 충돌 가능 → X

vector 초기값 없이 인덱스 접근

Segfault 유발 → 반드시 resize 또는 push_back 사용.

불필요한 전체 재계산

윈도를 이동할 때마다 배열을 새로 만드는 것은 O(n·m)이므로 지양.

7. 빠른 리마인드 체크리스트
 n > m? → 즉시 false

 알파벳이 26개 → 고정 배열 사용

 초기 윈도 채우고 바로 비교

 “들어온 문자 +1, 나간 문자 ?1” 후 즉시 비교

8. 빌드 & 테스트 예시
bash
복사
g++ -std=c++17 -O2 solution.cpp -o perm
./perm          # 테스트코드(main) 포함 시
간단 테스트
s1	s2	결과
"ab"	"eidbaooo"	true
"ab"	"eidboaoo"	false
"adc"	"dcda"	true

9. 확장 아이디어
다른 문자 집합 → unordered_map<char,int>으로 일반화.

실시간 스트림에서 순열 패턴 감지할 때 동일 로직 적용 가능.

더 큰 알파벳(M ≤?256) 도 배열이 여전히 효율적.

끝.