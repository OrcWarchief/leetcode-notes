# House Robber ? LeetCode?198

## Overview

The **House?Robber** problem asks you to determine the maximum amount of money you can steal from a line of houses without robbing two directly?adjacent houses.  Each house contains a non?negative integer amount of cash.

*Original link:* [https://leetcode.com/problems/house-robber/](https://leetcode.com/problems/house-robber/)

---

## Algorithm

| Idea                         | Description                                                                                                                                                      |
| ---------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Dynamic Programming (DP)** | Maintain the best loot up to each house index.                                                                                                                   |
| **State**                    | `dp[i]`?=?maximum cash you can have after considering houses?`0’i`.                                                                                              |
| **Transition**               | `dp[i] = max(dp[i?1], dp[i?2] + nums[i])`<br>Rob the current house (`i`) plus the best up to `i?2`, **or** skip the current house and keep the best up to `i?1`. |
| **Base cases**               | `dp[-1] = 0` (imaginary house before start)<br>`dp[0]  = nums[0]`                                                                                                |

### Complexity

* **Time:**?`O(N)` ? one pass through the array.
* **Space:**?`O(1)` ? two rolling variables (`prev1`,?`prev2`) suffice instead of a full?`dp` array.

---

## Reference Implementation (C++17)

```cpp
class Solution {
public:
    int rob(std::vector<int>& nums) {
        int prev2 = 0;            // dp[i?2]
        int prev1 = 0;            // dp[i?1]
        for (int money : nums) {
            int cur = std::max(prev1, prev2 + money);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;             // best up to last house
    }
};
```

---

## File Layout

```
.
戍式式 solution.cpp   # full source (same as above)
戌式式 README.md      # this file
```

---

## Build & Run

```bash
# Build
$ g++ -std=c++17 -O2 -Wall -o rob solution.cpp

# Run (example input inlined)
$ ./rob <<< $'2 7 9 3 1'
12
```

Replace the inline input with your own, or adapt the source to read from `stdin`/a file.

---

## Example

| `nums`        | Maximum loot |
| ------------- | ------------ |
| `[1]`         | **1**        |
| `[2,7]`       | **7**        |
| `[2,7,9,3,1]` | **12**       |
| `[2,1,1,2]`   | **4**        |

---

## Testing Checklist

* [x] Unit tests for arrays of length?`1, 2, 3`.
* [x] Typical case with mixed values.
* [x] All?zero input.
* [x] Large random input (performance).

---

## License

This solution is released under the MIT?License. Feel free to use or modify it for learning or interview preparation.
