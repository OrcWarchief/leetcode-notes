# LeetCode 217 ? Contains Duplicate

## ���� ���
���� �迭 `nums`�� �־��� ��, �迭 �ȿ� **�ߺ��� ���� �ϳ��� ����**�ϸ�?`true`��,  
��� **���� �ٸ� ��**�̶��?`false`�� ��ȯ�Ͻÿ�.

- **�Է�**  
  - `nums`: ���� *n*?(1?��?*n*?��?10?)�� ���� �迭  
  - �� ���Ҵ� 32?bit?���� ����  
- **���**  
  - `boolean` ? �ߺ� ���� ����

## ����
| �Է� | ��� | ���� |
|------|------|------|
| `[1,2,3,1]` | `true`  | ��?1�� �� �� ���� |
| `[1,2,3,4]` | `false` | ��� ���� ���� �ٸ� |
| `[1,1,1,3,3,4,3,2,4,2]` | `true` | 1,?3,?4,?2�� �ߺ� |

---

## �ذ� ���̵��

| ���� | �ٽ� ���� | ����� |
|------|-----------|--------|
| **HashSet ��� (����)** | ���Ҹ� �ϳ��� ��ȸ�ϸ� HashSet�� ���� �� �̹� �����ϸ� ��� `true` | O(n)?�ð�, O(n)?����<br>���� �������̰� ���� |
| ���� �� ���� �� | �迭�� ������ �� ������ �� ���� �� | O(n?log?n)?�ð�, O(1)~O(n)?����<br>���� �ڷᱸ���� �ʿ� ������ �ؽú��� ���� |
| ��Ʈ��/ī����(���� ���� ��) | �� ������ ���� �� ī���� �迭�̳� ��Ʈ�� ��� | O(n)?�ð�, O(K)?���� (*K*?= �� ����)<br>������ Ŭ �� ��ȿ���� |

> �Ϲ����� LeetCode?217 Ǯ�̿����� **HashSet**�� ǥ�� �ع��Դϴ�.

---

## ���⵵ �м�

| ��� | �ð� ���⵵ | ���� ���⵵ |
|------|-------------|-------------|
| HashSet | O(n) | O(n) |
| ����   | O(n?log?n) | O(1)?(���ڸ� ����) �Ǵ� O(n) |
| ��Ʈ��/ī���� | O(n) | O(K) |

`n?=?nums.length`, `K` = �� ����

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

---��Ʈ��/ī����
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <unordered_set>

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        if (nums.size() <= 1) return false;

        // 1) ��ü �� ���� ���
        int minVal = *std::min_element(nums.begin(), nums.end());
        int maxVal = *std::max_element(nums.begin(), nums.end());
        long long range = 1LL + static_cast<long long>(maxVal) - minVal;  // (max - min) + 1

        // 2) �޸� �Ѱ� üũ: ��Ʈ ���� �ʹ� ũ�� �ؽü����� ��ȸ
        //    ��: 10^7 ��Ʈ ~= 1.25 MB, 5*10^7 ��Ʈ ~= 6.25 MB
        constexpr long long BIT_LIMIT = 50'000'000;  // �ʿ� ��Ʈ���� �̺��� ũ�� skip
        if (range > BIT_LIMIT) {
            return hashSetFallback(nums);  // ������ �Ϲ� Ǯ��
        }

        // 3) ��Ʈ�� ũ�� ��� �� �ʱ�ȭ (64��Ʈ ������ ����)
        size_t wordCount = static_cast<size_t>((range + 63) / 64);  // �ø� ������
        std::vector<uint64_t> bitmap(wordCount, 0ULL);

        // 4) ������ ��Ʈ üũ
        for (int v : nums) {
            size_t idx  = static_cast<size_t>(static_cast<long long>(v) - minVal);  // 0?based ������
            size_t word = idx >> 6;          // idx / 64
            uint64_t bit = 1ULL << (idx & 63); // idx % 64

            if (bitmap[word] & bit) {
                return true;                 // �̹� ���� ���� ������
            }
            bitmap[word] |= bit;             // ��Ʈ ����
        }
        return false;                        // �ߺ� ����
    }

private:
    // �� ������ Ŭ �� ����ϴ� �ؽü� ����
    static bool hashSetFallback(const std::vector<int>& nums) {
        std::unordered_set<int> seen;
        seen.reserve(nums.size());
        for (int v : nums) {
            if (!seen.insert(v).second) return true;
        }
        return false;
    }
};