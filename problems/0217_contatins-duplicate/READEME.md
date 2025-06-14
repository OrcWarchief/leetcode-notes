# LeetCode 217 ? Contains Duplicate

## 문제 요약
정수 배열 `nums`가 주어질 때, 배열 안에 **중복된 값이 하나라도 존재**하면?`true`를,  
모두 **서로 다른 값**이라면?`false`를 반환하시오.

- **입력**  
  - `nums`: 길이 *n*?(1?≤?*n*?≤?10?)의 정수 배열  
  - 각 원소는 32?bit?정수 범위  
- **출력**  
  - `boolean` ? 중복 존재 여부

## 예시
| 입력 | 출력 | 설명 |
|------|------|------|
| `[1,2,3,1]` | `true`  | 값?1이 두 번 등장 |
| `[1,2,3,4]` | `false` | 모든 값이 서로 다름 |
| `[1,1,1,3,3,4,3,2,4,2]` | `true` | 1,?3,?4,?2가 중복 |

---

## 해결 아이디어

| 전략 | 핵심 개념 | 장단점 |
|------|-----------|--------|
| **HashSet 사용 (권장)** | 원소를 하나씩 순회하며 HashSet에 삽입 → 이미 존재하면 즉시 `true` | O(n)?시간, O(n)?공간<br>가장 직관적이고 빠름 |
| 정렬 후 인접 비교 | 배열을 정렬한 뒤 인접한 두 값을 비교 | O(n?log?n)?시간, O(1)~O(n)?공간<br>별도 자료구조가 필요 없지만 해시보다 느림 |
| 비트맵/카운팅(범위 제한 시) | 값 범위가 작을 때 카운팅 배열이나 비트셋 사용 | O(n)?시간, O(K)?공간 (*K*?= 값 범위)<br>범위가 클 땐 비효율적 |

> 일반적인 LeetCode?217 풀이에서는 **HashSet**이 표준 해법입니다.

---

## 복잡도 분석

| 방법 | 시간 복잡도 | 공간 복잡도 |
|------|-------------|-------------|
| HashSet | O(n) | O(n) |
| 정렬   | O(n?log?n) | O(1)?(제자리 정렬) 또는 O(n) |
| 비트맵/카운팅 | O(n) | O(K) |

`n?=?nums.length`, `K` = 값 범위

---**HashSet**
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int n : nums) {
            if (seen.count(n)) return true;
            seen.insert(n);
        }
        return false;
    }
};

---비트맵/카운팅
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <unordered_set>

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        if (nums.size() <= 1) return false;

        // 1) 전체 값 범위 계산
        int minVal = *std::min_element(nums.begin(), nums.end());
        int maxVal = *std::max_element(nums.begin(), nums.end());
        long long range = 1LL + static_cast<long long>(maxVal) - minVal;  // (max - min) + 1

        // 2) 메모리 한계 체크: 비트 수가 너무 크면 해시셋으로 우회
        //    예: 10^7 비트 ~= 1.25 MB, 5*10^7 비트 ~= 6.25 MB
        constexpr long long BIT_LIMIT = 50'000'000;  // 필요 비트수가 이보다 크면 skip
        if (range > BIT_LIMIT) {
            return hashSetFallback(nums);  // 안전한 일반 풀이
        }

        // 3) 비트맵 크기 계산 및 초기화 (64비트 단위로 묶음)
        size_t wordCount = static_cast<size_t>((range + 63) / 64);  // 올림 나눗셈
        std::vector<uint64_t> bitmap(wordCount, 0ULL);

        // 4) 값마다 비트 체크
        for (int v : nums) {
            size_t idx  = static_cast<size_t>(static_cast<long long>(v) - minVal);  // 0?based 오프셋
            size_t word = idx >> 6;          // idx / 64
            uint64_t bit = 1ULL << (idx & 63); // idx % 64

            if (bitmap[word] & bit) {
                return true;                 // 이미 같은 값이 등장함
            }
            bitmap[word] |= bit;             // 비트 세팅
        }
        return false;                        // 중복 없음
    }

private:
    // 값 범위가 클 때 사용하는 해시셋 버전
    static bool hashSetFallback(const std::vector<int>& nums) {
        std::unordered_set<int> seen;
        seen.reserve(nums.size());
        for (int v : nums) {
            if (!seen.insert(v).second) return true;
        }
        return false;
    }
};