# 0704. Binary Search

## ?? Problem
> Given a sorted (ascending) integer array **nums** and an integer **target**,  
> return the index of *target* if it exists. Otherwise, return -1. (LeetCode #704)

## ? Idea
- **Binary search**: 반복해서 배열을 반씩 잘라가며 `target`을 찾는다.  
- 중간 인덱스 `mid = left + (right - left) / 2`  
  - `nums[mid] == target` → 정답  
  - `nums[mid] < target` → 왼쪽 절반 버리고 오른쪽으로 `left = mid + 1`  
  - `nums[mid] > target` → 오른쪽 절반 버리고 왼쪽으로 `right = mid - 1`

## ??? Complexity
| Case  | Time          | Space     |
|------ |---------------|-----------|
| Worst | **O(log N)**  | **O(1)**  |

## ? Related
- 35. Search Insert Position (easy 변형)  
- 162. Find Peak Element (binary-search 패턴 응용)

## ? Review Notes
- 포인터 방향을 헷갈려서 `left`/`right`를 반대로 갱신했다가 무한 루프 경험 → **반달 자르기 규칙** 암기.  
- `mid` 계산은 overflow 방지를 위해 항상 `left + (right - left) / 2` 사용.  

//아직은 README 파일 감을 못잡아서 AI의 도움을 받음.