# 리트코드?238???Product?of?Array?Except?Self

## 문제 설명

정수 배열 `nums`가 주어졌을 때, `output[i]`는 **자신을 제외한** 나머지 요소들의 곱을 의미합니다. **나눗셈을 사용하지 않고**, 전체 알고리즘이 `O(n)` 시간 복잡도와 `O(1)` 추가 공간(결과 배열 제외)을 만족해야 합니다.

## 예시

| 입력             | 출력               |
| -------------- | ---------------- |
| `[1, 2, 3, 4]` | `[24, 12, 8, 6]` |

## 제약 사항

* `2 ≤ nums.length ≤ 10^5`
* `-30 ≤ nums[i] ≤ 30`
* 배열에는 최소 하나 이상의 0이 아닌 값이 존재합니다.

## 해결 전략

### 1. 왼쪽 누적 곱(prefix product)

`left[i] = nums[0] × … × nums[i?1]` 로 정의합니다. 이 값을 결과 배열 `res`에 저장합니다.

### 2. 오른쪽 누적 곱(suffix product)

뒤에서부터 `right` 변수를 유지하며 `right *= nums[i+1]` 식으로 갱신하고 `res[i] *= right` 를 수행합니다.

### 3. 공간 최적화

왼쪽 누적 곱은 `res` 자체에 저장하고, 오른쪽 누적 곱은 단일 변수 `right` 로 처리하여 추가 배열을 쓰지 않습니다.

## 알고리즘 단계별 요약

1. `res[0] = 1` 로 초기화합니다.
2. **왼쪽 누적 곱**

   ```cpp
   for (int i = 1; i < n; ++i)
       res[i] = res[i - 1] * nums[i - 1];
   ```
3. **오른쪽 누적 곱**

   ```cpp
   long long right = 1;
   for (int i = n - 1; i >= 0; --i) {
       res[i] *= right;
       right *= nums[i];
   }
   ```

## 시간 및 공간 복잡도

* **시간** `O(n)`
* **공간** `O(1)` (출력 배열 `res` 외 추가 메모리 없음)

## C++ 구현 예시

```cpp
#include <vector>
using namespace std;

vector<int> productExceptSelf(const vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);

    // 왼쪽 누적 곱
    for (int i = 1; i < n; ++i)
        res[i] = res[i - 1] * nums[i - 1];

    // 오른쪽 누적 곱
    long long right = 1;
    for (int i = n - 1; i >= 0; --i) {
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}
```

## 참고 자료

* LeetCode 공식 문제 설명 및 토론
* Prefix/Suffix Product 아이디어를 활용한 기타 배열 문제들
