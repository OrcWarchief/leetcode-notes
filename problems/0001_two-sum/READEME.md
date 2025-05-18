# 0001. Two Sum 

## ?? Problem
> Given an array of integers **nums** and an integer **target**, return indices of the two numbers such that they add up to `target`. (LeetCode #1)

## ? Idea
- **해시맵**로 “필요한 값 = target - nums[i]” 를 바로 찾아 O(N) 시간.
- 이미 해시맵에 존재하면 (필요한 값, 현재 인덱스) 쌍을 반환.
- 없으면 `nums[i]`를 `(값 → 인덱스)`로 저장하고 다음 숫자로.

## ??? Complexity
- Time `O(N)`
- Space `O(N)`

## ? Related
- Two Sum II (Input Array Is Sorted) #167
- 3Sum #15

## ? Review Notes
- 배열이 클 때는 **unordered_map** 대신 **vector<int>(100001, -1)** 같은 직접 해시가 더 빠를 수 있다.
- 다른 사람 풀이: **two-pointer**는 정렬이 필요해 O(N log N).

//아직은 README 파일 감을 못잡아서 AI의 도움을 받음.