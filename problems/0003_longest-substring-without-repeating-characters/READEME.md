# 0003 Longest Substring Without Repeating Characters  

LeetCode 문제 번호 3번에 대한 README입니다.  
주어진 문자열 `s` 에서 **중복 문자가 없는 가장 긴 부분 문자열** 길이를 구하는 문제입니다.

---

## ? 문제 정의

> 주어진 문자열 `s`(길이 `0 ≤ |s| ≤ 5 × 10⁴`, ASCII 문자만 포함)에서  
> **같은 문자가 두 번 이상 등장하지 않는** 가장 긴 부분 문자열(substring)의 길이를 반환하라.

- 부분 문자열은 **연속**되어야 한다.  
- 대소문자는 다른 문자로 취급한다.  
- 빈 문자열의 답은 0이다.

---

## ? 접근 방법 ? 슬라이딩 윈도우

1. **두 개의 포인터** `left`, `right`로 현재 윈도우(부분 문자열)를 나타낸다.  
2. `right` 를 0 → `n-1`까지 이동하며 문자를 확장한다.  
3. 확장 중 **중복**이 발견되면, 해당 문자가 마지막으로 나타난 위치 + 1로 `left`를 옮겨 윈도우를 축소한다.  
4. 이동할 때마다 `ans = max(ans, right - left + 1)`으로 최장 길이를 갱신한다.  
5. 각 문자의 **마지막 인덱스**를 `last[c]`(길이 128의 배열)로 저장하면 O(1) 조회가 가능하다.

### 핵심 아이디어
- “중복을 만나면 윈도우 전체를 지우지 말고, **겹치는 부분까지만** 잘라낸다.”
- 이미 처리한 구간을 다시 확인하지 않으므로 O(n)으로 해결된다.

---

## ?? 복잡도

| 항목      |       값                      |
|----------|----                            |
| **시간**  | O(n) ? 각 문자를 한 번씩만 살핀다 |
| **공간**  | O(1) ? 고정 크기 128 배열       |

---

## ??? C++17 참고 구현

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(const string& s) {
        vector<int> last(128, -1);   // ASCII
        int left = 0, ans = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            char c = s[right];

            if (last[c] >= left)           // 중복이 윈도우 안에 있으면
                left = last[c] + 1;        // left를 옮긴다
            last[c] = right;               // 마지막 위치 갱신
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};