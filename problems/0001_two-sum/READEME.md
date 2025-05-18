# 0001. Two Sum 

## ?? Problem
> Given an array of integers **nums** and an integer **target**, return indices of the two numbers such that they add up to `target`. (LeetCode #1)

## ? Idea
- **�ؽø�**�� ���ʿ��� �� = target - nums[i]�� �� �ٷ� ã�� O(N) �ð�.
- �̹� �ؽøʿ� �����ϸ� (�ʿ��� ��, ���� �ε���) ���� ��ȯ.
- ������ `nums[i]`�� `(�� �� �ε���)`�� �����ϰ� ���� ���ڷ�.

## ??? Complexity
- Time `O(N)`
- Space `O(N)`

## ? Related
- Two Sum II (Input Array Is Sorted) #167
- 3Sum #15

## ? Review Notes
- �迭�� Ŭ ���� **unordered_map** ��� **vector<int>(100001, -1)** ���� ���� �ؽð� �� ���� �� �ִ�.
- �ٸ� ��� Ǯ��: **two-pointer**�� ������ �ʿ��� O(N log N).

//������ README ���� ���� ����Ƽ� AI�� ������ ����.