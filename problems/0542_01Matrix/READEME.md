# 01?��Ʈ���� (LeetCode?542)

## ���� ����

`n?��?m` ũ���� ���� ���?`mat`�� �־��� ��, �� ĭ?`(i,?j)`���� **���� �����?0**������ ����ư �Ÿ��� ������ ���?`dist`�� ��ȯ�մϴ�.

```
�Է�  : [[0,0,0],
         [0,1,0],
         [1,1,1]]
���  : [[0,0,0],
         [0,1,0],
         [1,2,1]]
```

---

## �˰��� ���ٹ�

| ���              | �ٽ� ���̵��                                                      | �ð����⵵| �������⵵ |
| --------------    | ---------------------------------------------                   | -------- | -------- |
| **���� BFS**      | 0?�� �ִ� ��� ĭ�� ���ÿ� BFS?���������� �ְ�, �� �������� ���̾ Ȯ�� | `O(N��M)` | `O(N��M)` |
| **2?�н� DP ��ĵ** | ��?����, ��?���� �� ���� ��ĵ���� ��� ������ �� ����?relax            | `O(N��M)` | `O(N��M)` |

### 1. ����?BFS?(���� ������)

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat){
    int n = mat.size(), m = n ? mat[0].size() : 0;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q;
    constexpr int dx[4] = {1,-1,0,0};
    constexpr int dy[4] = {0,0,1,-1};

    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(mat[i][j]==0){
                dist[i][j]=0;
                q.emplace(i,j);
            }

    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        for(int d=0; d<4; ++d){
            int nx = x + dx[d], ny = y + dy[d];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.emplace(nx,ny);
        }
    }
    return dist;
}
```

### 2. 2?�н� DP ��ĵ

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat){
    int n = mat.size(), m = n ? mat[0].size() : 0;
    const int INF = n + m + 5;          // ����� ū ��
    vector<vector<int>> dist(n, vector<int>(m, INF));

    // 1) ��?���� (��������)
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j){
            if(mat[i][j]==0){ dist[i][j]=0; continue; }
            if(i) dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
            if(j) dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
        }

    // 2) ��?���� (�Ʒ���������)
    for(int i=n-1;i>=0;--i)
        for(int j=m-1;j>=0;--j){
            if(i+1 < n) dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
            if(j+1 < m) dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
        }
    return dist;
}
```

#### ������ ���� ���

* **ù ��° ��ĵ**: �������ʿ��� ���� ��θ� ��� ���.
* **�� ��° ��ĵ**: �Ʒ��������ʿ��� ���� ��θ� �߰��� ���.
* �� ���� ������ ��Ȯ�� �� ���� relax �ǹǷ�, ���� ����ġ ���ڿ��� �ִ� �Ÿ��� Ȯ���˴ϴ�.

---

## ���� & ����

```bash
# C++17 �ʿ�
g++ -std=c++17 update_matrix.cpp -o update_matrix
./update_matrix < input.txt > output.txt
```

### �Է� ����

1. ù ��: `n m`?(��, ��)
2. ����?`n`��: �������� ���е�?`m`���� 0/1

### ����

```
3 3
0 0 0
0 1 0
1 1 1
```

���

```
0 0 0
0 1 0
1 2 1
```

---

## �׽�Ʈ ���̽� ����

1. ��� ĭ�� 0
2. ��� ĭ�� 1
3. `1��1`, `1��N`, `N��1` ��� ���
4. ���� 80��80 ��� (���� �Է�)

---

## ���⵵ ���

* **�ð�**: `O(N��M)`
* **����**: `O(N��M)` (�Է�?`mat`�� ��Ȱ���ϸ� �߰� ����?`O(1)`)

---

## ���� ����

* LeetCode?542 ? *01 Matrix*
* CLRS?��22.2 ? Breadth?First Search

---

??2025?Ryu?Soungmin.?MIT?License