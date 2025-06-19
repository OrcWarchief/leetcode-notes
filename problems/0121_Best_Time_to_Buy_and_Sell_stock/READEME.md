# LeetCode?121???Best Time to Buy and Sell Stock

## 문제 설명

주어진 주가 배열?`prices[i]`는 *i*일 차의 주가를 의미합니다. **단 한 번**의 매수와 **단 한 번**의 매도를 통해 얻을 수 있는 최대 이익을 구하세요. 매수는 매도보다 앞선 날에만 할 수 있습니다. 이익이 없으면?`0`을 반환합니다.

## 핵심 아이디어

한 번의 선형 스캔으로 다음 두 값을 유지합니다.

1. **최저 매수가격?`minPrice`**?? 지금까지 본 가격 중 가장 낮은 값
2. **현재까지의 최대 이익?`maxProfit`**?? 오늘 팔았다고 가정했을 때의 이익(`price?-?minPrice`)과 직전?`maxProfit`?중 큰 값

이렇게 하면?O(n)?시간,?O(1)?공간으로 답을 구할 수 있습니다.

## 알고리즘

```text
minPrice??<-?+∞
maxProfit <-?0
for price in prices:
????minPrice??<-?min(minPrice,?price)
????maxProfit <-?max(maxProfit,?price?-?minPrice)
return?maxProfit
```

## 구현?(C++)

```cpp
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int minPrice  = numeric_limits<int>::max();
        int maxProfit = 0;

        for (int price : prices) {
            minPrice  = std::min(minPrice, price);
            maxProfit = std::max(maxProfit, price - minPrice);
        }
        return maxProfit;
    }
};
```

## 복잡도 분석

|           | 시간   | 공간   |
| --------- | ---- | ---- |
| **단일 스캔** | O(n) | O(1) |

## 테스트 케이스

| 입력?`prices`     | 기대 출력 | 설명                         |
| --------------- | ----- | -------------------------- |
| `[7,1,5,3,6,4]` | `5`   | 2일(가격?1)에 매수, 5일(가격?6)에 매도 |
| `[7,6,4,3,1]`   | `0`   | 하락만 하므로 거래하지 않음            |
| `[]` 또는 `[3]`   | `0`   | 거래 불가                      |

## 추가 고찰

* **다중 거래 가능(122번)**: 모든 상승 구간을 이익으로 누적.
* **거래 횟수 제한(k번, 188번)**: DP?(k-state?solution).
* **수수료 존재(714번)**: 매수 시점 가격에 수수료를 더해 상태 업데이트.
* **두 번 거래(123번)**: 4가지 상태 변수로 O(n).

## 참고 링크

* [LeetCode?121?문제 페이지](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
* \[LeetCode 공식 솔루션???One Pass]
