# LeetCode?139?· Word Break

## 문제 설명

문자열 `s`(길이?*n*)와 문자열 배열 `wordDict`(사전) 이 주어졌을 때,
`wordDict`의 단어들을 공백 없이 여러 번 이어 붙여 **문자열 전체**를 정확히 구성할 수 있는지 여부를?`true` / `false`로 반환하라.

> 예시
>
> *입력*??`"leetcode"`,?`["leet", "code"]`  →?`true`
>
> *입력*??`"catsandog"`,?`["cats","dog","sand","and","cat"]`  →?`false`

## 핵심 아이디어

* **DP(동적 계획법)**?: `dp[i]`?를?`0?≤?i?≤?n` 구간 중 *앞부분* `s[0..i?1]`?가?사전 단어로 완전히 분할 가능한지 여부로 정의한다.
* `dp[0] = true`?(빈 문자열은 항상 가능). 이후 인덱스?`i`에 대해 앞선 분할점?`j`(0?≤?`j`?<?`i`)를 모두 검사하며

  * `dp[j] == true`?이고

  * `s.substr(j, i?j)`?가 사전에 존재하면

  > `dp[i] = true` → 더 긴 분할의 기반이 됨

## 알고리즘 단계

1. **사전 해시화**?: `unordered_set<string> dict(wordDict.begin(), wordDict.end())` ?→ 조회?`O(1)`.
2. **DP 테이블 초기화**?: 길이?`n+1`?배열 `dp`, `dp[0] = true`.
3. **두 인덱스 루프**

   ```cpp
   for (int i = 1; i <= n; ++i) {
       for (int j = 0; j < i; ++j) {
           if (dp[j] && dict.count(s.substr(j, i - j))) {
               dp[i] = true;
               break;   // i 위치 확정 → 다음 i 로 이동
           }
       }
   }
   ```
4. **결과**?: `return dp[n];`

## 복잡도 분석

| 항목 | 복잡도                      |   |                    |
| -- | ------------------------     | - | ------------------ |
| 시간 | ?`O(n²)`?(이중 루프?`j < i`) |   |                    |
| 공간 | ?\`O(n +                 | D | )`?(`dp\`?+?해시 사전) |

> **최적화**
>
> * 사전 단어 최대 길이 `Lmax`를 미리 구해 `j` 루프 범위를 `i?Lmax`까지로 제한?→ 평균 시간 단축.
> * C++20?`std::string_view`를 사용하면 `substr` 복사를 회피할 수 있음.

## 대안 접근

| 방법           | 개념                           | 시간         | 공간        | 특징                       |     |                |
| ------------ | ---------------------------- | ---------- | --------- | ------------------------ | --- | -------------- |
| BFS?(Queue)  | 각 인덱스를 그래프 노드로 보고 단어 길이만큼 점프 | `O(n²)`    | `O(n)`    | DP와 유사하지만 visited?배열만 사용 |     |                |
| DFS?+?메모이제이션 | 재귀로 분할 & 캐싱                  | 평균?`O(n²)` | `O(n)`    | 짧은 코드, 호출 스택 주의          |     |                |
| Trie?+?DP    | 사전을 Trie에 저장 후 한 번의 스캔       | 최악?`O(n²)` | \`O(n + Σ | w                        | )\` | 동일 접두사 공유 시 빠름 |

## 참고 구현 (C++)

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        const int n = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break; // 다음 i
                }
            }
        }
        return dp[n];
    }
};
```

## 요약

* `dp[i]`?의미를 **“앞부분 분할 가능 여부”** 로 잡으면 자연스럽게 `dp[0]` → `dp[…]` 로 true 가 전파된다.
* 이중 루프 + 해시 사전은 입력 제약이 커도 안정적인 `O(n²)` 풀이.
* 사전이 작거나 단어 길이가 짧다면 사전 순회 방식(`for w in wordDict`)도 실용적이다.

---

> 작성?: 2025?07?19
