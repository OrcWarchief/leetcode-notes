# LeetCode?121???Best Time to Buy and Sell Stock

## ���� ����

�־��� �ְ� �迭?`prices[i]`�� *i*�� ���� �ְ��� �ǹ��մϴ�. **�� �� ��**�� �ż��� **�� �� ��**�� �ŵ��� ���� ���� �� �ִ� �ִ� ������ ���ϼ���. �ż��� �ŵ����� �ռ� ������ �� �� �ֽ��ϴ�. ������ ������?`0`�� ��ȯ�մϴ�.

## �ٽ� ���̵��

�� ���� ���� ��ĵ���� ���� �� ���� �����մϴ�.

1. **���� �ż�����?`minPrice`**?? ���ݱ��� �� ���� �� ���� ���� ��
2. **��������� �ִ� ����?`maxProfit`**?? ���� �ȾҴٰ� �������� ���� ����(`price?-?minPrice`)�� ����?`maxProfit`?�� ū ��

�̷��� �ϸ�?O(n)?�ð�,?O(1)?�������� ���� ���� �� �ֽ��ϴ�.

## �˰���

```text
minPrice??<-?+��
maxProfit <-?0
for price in prices:
????minPrice??<-?min(minPrice,?price)
????maxProfit <-?max(maxProfit,?price?-?minPrice)
return?maxProfit
```

## ����?(C++)

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

## ���⵵ �м�

|           | �ð�   | ����   |
| --------- | ---- | ---- |
| **���� ��ĵ** | O(n) | O(1) |

## �׽�Ʈ ���̽�

| �Է�?`prices`     | ��� ��� | ����                         |
| --------------- | ----- | -------------------------- |
| `[7,1,5,3,6,4]` | `5`   | 2��(����?1)�� �ż�, 5��(����?6)�� �ŵ� |
| `[7,6,4,3,1]`   | `0`   | �϶��� �ϹǷ� �ŷ����� ����            |
| `[]` �Ǵ� `[3]`   | `0`   | �ŷ� �Ұ�                      |

## �߰� ����

* **���� �ŷ� ����(122��)**: ��� ��� ������ �������� ����.
* **�ŷ� Ƚ�� ����(k��, 188��)**: DP?(k-state?solution).
* **������ ����(714��)**: �ż� ���� ���ݿ� �����Ḧ ���� ���� ������Ʈ.
* **�� �� �ŷ�(123��)**: 4���� ���� ������ O(n).

## ���� ��ũ

* [LeetCode?121?���� ������](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
* \[LeetCode ���� �ַ��???One Pass]
