307. Range Sum Query ? Mutable (README)
개요

nums 배열에 대해 두 연산을 다수 처리합니다.

update(i, val): nums[i] = val 로 갱신

sumRange(l, r): 구간 [l, r]의 합 반환

핵심 포인트:

변경(Update)와 구간합(Query)을 모두 빠르게 처리해야 하므로 선형 탐색/단순 prefix sum만으로는 부족합니다.

대표 해법은 세그먼트 트리(Segment Tree) 또는 펜윅 트리(Fenwick/BIT) 입니다.

여기서는 특히 세그먼트 트리의 반복형(2·n) 과 재귀형(4·n) 두 가지 구현을 정리합니다.

왜 세그먼트 트리인가?

구간 질의(합/최소/최대 등)와 점 업데이트를 O(log n) 에 처리 가능

빌드 O(n), 메모리 O(n)

구현 방식 요약
1) 반복형(Iterative) ? 2·n 배열

리프를 tree[n..2n-1]에 두고, 내부 노드는 tree[1..n-1]에 저장

sumRange는 반열린 구간 [l, r) 기법으로 구현 → 우측 경계 미포함

장점: 짧고 빠르며 메모리 사용이 정확히 2·n

단점: Lazy propagation 등 고급 기능 확장성이 떨어짐

2) 재귀형(Recursive) ? 4·n 배열

전통적/교과서형. 노드 v가 구간 [tl, tr] 담당

build, update_point, query_sum 재귀로 구현

장점: 일반성/확장성 좋음(최소/최대/GCD, Lazy propagation 등)

단점: 2·n 대비 메모리 조금 더 사용

C++ 코드
A. 반복형(2·n) ? 반열린 구간 [l, r)
#include <vector>
using namespace std;

class NumArray {
    vector<int> tree;
    int n;

public:
    NumArray(vector<int>& nums) {
        n = (int)nums.size();
        if (n == 0) return;
        tree.assign(2 * n, 0);
        // 리프 채우기
        for (int i = 0; i < n; ++i) tree[n + i] = nums[i];
        // 내부 노드 채우기
        for (int i = n - 1; i >= 1; --i)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void update(int index, int val) {
        if (n == 0) return;
        int pos = n + index;
        tree[pos] = val;
        while (pos > 1) {
            pos >>= 1;
            tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
        }
    }

    int sumRange(int left, int right) {
        if (n == 0) return 0;
        int l = left + n;
        int r = right + n + 1;   // [l, r)
        int res = 0;
        while (l < r) {
            if (l & 1) res += tree[l++];   // l이 오른쪽 자식이면 해당 블록 포함
            if (r & 1) res += tree[--r];   // r이 오른쪽 자식 위치면 r-1(왼쪽 자식) 포함
            l >>= 1; r >>= 1;              // 부모로 이동
        }
        return res;
    }
};

B. 재귀형(4·n) ? 닫힌 구간 [l, r]
#include <vector>
using namespace std;

class NumArray {
    int n;
    vector<int> seg;
    vector<int> a;

    void build(int v, int tl, int tr) {
        if (tl == tr) { seg[v] = a[tl]; return; }
        int tm = (tl + tr) >> 1;
        build(v<<1, tl, tm);
        build(v<<1|1, tm+1, tr);
        seg[v] = seg[v<<1] + seg[v<<1|1];
    }

    void update_point(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) { seg[v] = val; return; }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) update_point(v<<1, tl, tm, pos, val);
        else           update_point(v<<1|1, tm+1, tr, pos, val);
        seg[v] = seg[v<<1] + seg[v<<1|1];
    }

    int query_sum(int v, int tl, int tr, int l, int r) const {
        if (l > r) return 0;
        if (l == tl && r == tr) return seg[v];
        int tm = (tl + tr) >> 1;
        return query_sum(v<<1, tl, tm, l, min(r, tm))
             + query_sum(v<<1|1, tm+1, tr, max(l, tm+1), r);
    }

public:
    NumArray(vector<int>& nums) {
        n = (int)nums.size();
        a = nums;
        seg.assign(max(1, 4*n), 0);
        if (n) build(1, 0, n-1);
    }

    void update(int index, int val) {
        if (n == 0) return;
        a[index] = val;
        update_point(1, 0, n-1, index, val);
    }

    int sumRange(int left, int right) {
        if (n == 0) return 0;
        return query_sum(1, 0, n-1, left, right);
    }
};

시간·공간 복잡도

빌드: O(n)

점 업데이트: O(log n)

구간 합 질의: O(log n)

공간: O(n) (반복형 약 2·n, 재귀형 관례적으로 4·n)

자주 하는 실수 체크리스트

sumRange 누적 변수(res) 초기화 누락

l >> 1; / r >> 1; 처럼 대입 없는 시프트 (→ l >>= 1; r >>= 1;)

반열린 [l, r) vs 닫힌 [l, r] 혼용

연산자 우선순위:

pos << 1 | 1 는 (pos << 1) | 1로 해석됩니다.

pos << 1 + 1 은 pos << (1 + 1)(= pos << 2)이므로 전혀 다른 의미!

오버플로 가능성 → 입력 규모 크면 long long 고려

테스트 예시
입력:  nums = [1,3,5]
쿼리:  sumRange(0,2) -> 9
       update(1,2)   -> nums = [1,2,5]
       sumRange(0,2) -> 8

팁

연산을 시각화해 보면 이해가 빨라집니다.
반복형에서 l이 홀수(오른쪽 자식)면 그 노드를 더하고 l++;
r이 홀수(오른쪽 자식 위치)면 --r 후 그 노드를 더합니다.
이후 둘 다 >>= 1로 부모로 올립니다(반열린 [l, r) 기준).

언제 4·n(재귀형)을 쓰나?

Lazy propagation(구간 업데이트), 구간 최소/최대, 기타 커스텀 연산 등 일반성/확장성이 필요할 때

코드가 구간 단위 의미(노드 v가 [tl,tr] 담당)를 드러내 직관적이라 유지·확장에 유리합니다.