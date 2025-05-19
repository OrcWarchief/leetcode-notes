# 0200. Number of Islands

## ?? Problem  
> Given an `m × n` 2-D grid map of `'1'`s (land) and `'0'`s (water),  
> return **the number of islands**. An island is surrounded by water and is formed by
> connecting adjacent lands **horizontally or vertically**.  
> (Diagonal connections do **not** count.)?? LeetCode #200  

## ? Idea  
- **그래프 탐색(DFS / BFS)** : 육지(`'1'`)를 발견할 때마다 전체를 방문 표시하면,
  그 탐색이 끝날 때 하나의 섬(count ++)이 완성된다.  
- 구현 방법 두 가지  
  1. **DFS 재귀**  
     ```cpp
     void dfs(int r,int c){
         if(outOfRange || grid[r][c]=='0') return;
         grid[r][c]='0';               // 방문표시
         for(auto [dr,dc]: dirs) dfs(r+dr,c+dc);
     }
     ```  
  2. **BFS(큐)** ? 스택 오버플로 걱정 없이 대규모 입력 처리 가능.  
- 방문 처리  
  - 가장 간단한 방법은 **`grid[r][c] = '0'`** 로 바로 뒤집기.  
  - 또는 `vector<vector<bool>> visited` 별도 배열 사용.

## ??? Complexity
| Case | Time | Space |
|------|------|-------|
| All | **O(N × M)** | **O(N × M)** <br>(BFS 큐 또는 DFS 재귀 스택) |

## ? Related
- 695 Max Area of Island ? “섬 크기 구하기”  
- 463 Island Perimeter ? “섬 둘레”  
- 130 Surrounded Regions ? “물로 둘러싸인 영역 뒤집기”  
- 1254 Number of Closed Islands ? “폐쇄 섬”  
- 1020 Number of Enclaves ? “경계 밖으로 못 나가는 땅”  

## ? Review Notes
- **dirs = {{1,0},{-1,0},{0,1},{0,-1}}** 네 방향 벡터를 재사용해 코드 간결화.  
- DFS 재귀 깊이 ? `N × M`; 입력이 10? 이상일 땐 **BFS** 권장(재귀 스택 제한 회피).  
- `grid[i][j] == '1'` 확인 후 즉시 `'0'`으로 바꿔야 **중복 방문**이 안 생긴다.  
- 여러 테스트케이스를 한꺼번에 돌릴 때, **방문 배열을 재활용**하거나
  **`grid`를 그대로 수정**해야 메모리 재할당 비용이 없다.