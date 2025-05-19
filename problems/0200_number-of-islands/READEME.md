# 0200. Number of Islands

## ?? Problem  
> Given an `m �� n` 2-D grid map of `'1'`s (land) and `'0'`s (water),  
> return **the number of islands**. An island is surrounded by water and is formed by
> connecting adjacent lands **horizontally or vertically**.  
> (Diagonal connections do **not** count.)?? LeetCode #200  

## ? Idea  
- **�׷��� Ž��(DFS / BFS)** : ����(`'1'`)�� �߰��� ������ ��ü�� �湮 ǥ���ϸ�,
  �� Ž���� ���� �� �ϳ��� ��(count ++)�� �ϼ��ȴ�.  
- ���� ��� �� ����  
  1. **DFS ���**  
     ```cpp
     void dfs(int r,int c){
         if(outOfRange || grid[r][c]=='0') return;
         grid[r][c]='0';               // �湮ǥ��
         for(auto [dr,dc]: dirs) dfs(r+dr,c+dc);
     }
     ```  
  2. **BFS(ť)** ? ���� �����÷� ���� ���� ��Ը� �Է� ó�� ����.  
- �湮 ó��  
  - ���� ������ ����� **`grid[r][c] = '0'`** �� �ٷ� ������.  
  - �Ǵ� `vector<vector<bool>> visited` ���� �迭 ���.

## ??? Complexity
| Case | Time | Space |
|------|------|-------|
| All | **O(N �� M)** | **O(N �� M)** <br>(BFS ť �Ǵ� DFS ��� ����) |

## ? Related
- 695 Max Area of Island ? ���� ũ�� ���ϱ⡱  
- 463 Island Perimeter ? ���� �ѷ���  
- 130 Surrounded Regions ? ������ �ѷ����� ���� �����⡱  
- 1254 Number of Closed Islands ? ����� ����  
- 1020 Number of Enclaves ? ����� ������ �� ������ ����  

## ? Review Notes
- **dirs = {{1,0},{-1,0},{0,1},{0,-1}}** �� ���� ���͸� ������ �ڵ� ����ȭ.  
- DFS ��� ���� ? `N �� M`; �Է��� 10? �̻��� �� **BFS** ����(��� ���� ���� ȸ��).  
- `grid[i][j] == '1'` Ȯ�� �� ��� `'0'`���� �ٲ�� **�ߺ� �湮**�� �� �����.  
- ���� �׽�Ʈ���̽��� �Ѳ����� ���� ��, **�湮 �迭�� ��Ȱ��**�ϰų�
  **`grid`�� �״�� ����**�ؾ� �޸� ���Ҵ� ����� ����.