# ��Ʈ�ڵ�?238???Product?of?Array?Except?Self

## ���� ����

���� �迭 `nums`�� �־����� ��, `output[i]`�� **�ڽ��� ������** ������ ��ҵ��� ���� �ǹ��մϴ�. **�������� ������� �ʰ�**, ��ü �˰����� `O(n)` �ð� ���⵵�� `O(1)` �߰� ����(��� �迭 ����)�� �����ؾ� �մϴ�.

## ����

| �Է�             | ���               |
| -------------- | ---------------- |
| `[1, 2, 3, 4]` | `[24, 12, 8, 6]` |

## ���� ����

* `2 �� nums.length �� 10^5`
* `-30 �� nums[i] �� 30`
* �迭���� �ּ� �ϳ� �̻��� 0�� �ƴ� ���� �����մϴ�.

## �ذ� ����

### 1. ���� ���� ��(prefix product)

`left[i] = nums[0] �� �� �� nums[i?1]` �� �����մϴ�. �� ���� ��� �迭 `res`�� �����մϴ�.

### 2. ������ ���� ��(suffix product)

�ڿ������� `right` ������ �����ϸ� `right *= nums[i+1]` ������ �����ϰ� `res[i] *= right` �� �����մϴ�.

### 3. ���� ����ȭ

���� ���� ���� `res` ��ü�� �����ϰ�, ������ ���� ���� ���� ���� `right` �� ó���Ͽ� �߰� �迭�� ���� �ʽ��ϴ�.

## �˰��� �ܰ躰 ���

1. `res[0] = 1` �� �ʱ�ȭ�մϴ�.
2. **���� ���� ��**

   ```cpp
   for (int i = 1; i < n; ++i)
       res[i] = res[i - 1] * nums[i - 1];
   ```
3. **������ ���� ��**

   ```cpp
   long long right = 1;
   for (int i = n - 1; i >= 0; --i) {
       res[i] *= right;
       right *= nums[i];
   }
   ```

## �ð� �� ���� ���⵵

* **�ð�** `O(n)`
* **����** `O(1)` (��� �迭 `res` �� �߰� �޸� ����)

## C++ ���� ����

```cpp
#include <vector>
using namespace std;

vector<int> productExceptSelf(const vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);

    // ���� ���� ��
    for (int i = 1; i < n; ++i)
        res[i] = res[i - 1] * nums[i - 1];

    // ������ ���� ��
    long long right = 1;
    for (int i = n - 1; i >= 0; --i) {
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}
```

## ���� �ڷ�

* LeetCode ���� ���� ���� �� ���
* Prefix/Suffix Product ���̵� Ȱ���� ��Ÿ �迭 ������
