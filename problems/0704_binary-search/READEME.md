# 0704. Binary Search

## ?? Problem
> Given a sorted (ascending) integer array **nums** and an integer **target**,  
> return the index of *target* if it exists. Otherwise, return -1. (LeetCode #704)

## ? Idea
- **Binary search**: �ݺ��ؼ� �迭�� �ݾ� �߶󰡸� `target`�� ã�´�.  
- �߰� �ε��� `mid = left + (right - left) / 2`  
  - `nums[mid] == target` �� ����  
  - `nums[mid] < target` �� ���� ���� ������ ���������� `left = mid + 1`  
  - `nums[mid] > target` �� ������ ���� ������ �������� `right = mid - 1`

## ??? Complexity
| Case  | Time          | Space     |
|------ |---------------|-----------|
| Worst | **O(log N)**  | **O(1)**  |

## ? Related
- 35. Search Insert Position (easy ����)  
- 162. Find Peak Element (binary-search ���� ����)

## ? Review Notes
- ������ ������ �򰥷��� `left`/`right`�� �ݴ�� �����ߴٰ� ���� ���� ���� �� **�ݴ� �ڸ��� ��Ģ** �ϱ�.  
- `mid` ����� overflow ������ ���� �׻� `left + (right - left) / 2` ���.  

//������ README ���� ���� ����Ƽ� AI�� ������ ����.