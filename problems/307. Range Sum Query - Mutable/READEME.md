307. Range Sum Query ? Mutable (README)
����

nums �迭�� ���� �� ������ �ټ� ó���մϴ�.

update(i, val): nums[i] = val �� ����

sumRange(l, r): ���� [l, r]�� �� ��ȯ

�ٽ� ����Ʈ:

����(Update)�� ������(Query)�� ��� ������ ó���ؾ� �ϹǷ� ���� Ž��/�ܼ� prefix sum�����δ� �����մϴ�.

��ǥ �ع��� ���׸�Ʈ Ʈ��(Segment Tree) �Ǵ� ���� Ʈ��(Fenwick/BIT) �Դϴ�.

���⼭�� Ư�� ���׸�Ʈ Ʈ���� �ݺ���(2��n) �� �����(4��n) �� ���� ������ �����մϴ�.

�� ���׸�Ʈ Ʈ���ΰ�?

���� ����(��/�ּ�/�ִ� ��)�� �� ������Ʈ�� O(log n) �� ó�� ����

���� O(n), �޸� O(n)

���� ��� ���
1) �ݺ���(Iterative) ? 2��n �迭

������ tree[n..2n-1]�� �ΰ�, ���� ���� tree[1..n-1]�� ����

sumRange�� �ݿ��� ���� [l, r) ������� ���� �� ���� ��� ������

����: ª�� ������ �޸� ����� ��Ȯ�� 2��n

����: Lazy propagation �� ��� ��� Ȯ�强�� ������

2) �����(Recursive) ? 4��n �迭

������/��������. ��� v�� ���� [tl, tr] ���

build, update_point, query_sum ��ͷ� ����

����: �Ϲݼ�/Ȯ�强 ����(�ּ�/�ִ�/GCD, Lazy propagation ��)

����: 2��n ��� �޸� ���� �� ���

C++ �ڵ�
A. �ݺ���(2��n) ? �ݿ��� ���� [l, r)
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
        // ���� ä���
        for (int i = 0; i < n; ++i) tree[n + i] = nums[i];
        // ���� ��� ä���
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
            if (l & 1) res += tree[l++];   // l�� ������ �ڽ��̸� �ش� ��� ����
            if (r & 1) res += tree[--r];   // r�� ������ �ڽ� ��ġ�� r-1(���� �ڽ�) ����
            l >>= 1; r >>= 1;              // �θ�� �̵�
        }
        return res;
    }
};

B. �����(4��n) ? ���� ���� [l, r]
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

�ð������� ���⵵

����: O(n)

�� ������Ʈ: O(log n)

���� �� ����: O(log n)

����: O(n) (�ݺ��� �� 2��n, ����� ���������� 4��n)

���� �ϴ� �Ǽ� üũ����Ʈ

sumRange ���� ����(res) �ʱ�ȭ ����

l >> 1; / r >> 1; ó�� ���� ���� ����Ʈ (�� l >>= 1; r >>= 1;)

�ݿ��� [l, r) vs ���� [l, r] ȥ��

������ �켱����:

pos << 1 | 1 �� (pos << 1) | 1�� �ؼ��˴ϴ�.

pos << 1 + 1 �� pos << (1 + 1)(= pos << 2)�̹Ƿ� ���� �ٸ� �ǹ�!

�����÷� ���ɼ� �� �Է� �Ը� ũ�� long long ���

�׽�Ʈ ����
�Է�:  nums = [1,3,5]
����:  sumRange(0,2) -> 9
       update(1,2)   -> nums = [1,2,5]
       sumRange(0,2) -> 8

��

������ �ð�ȭ�� ���� ���ذ� �������ϴ�.
�ݺ������� l�� Ȧ��(������ �ڽ�)�� �� ��带 ���ϰ� l++;
r�� Ȧ��(������ �ڽ� ��ġ)�� --r �� �� ��带 ���մϴ�.
���� �� �� >>= 1�� �θ�� �ø��ϴ�(�ݿ��� [l, r) ����).

���� 4��n(�����)�� ����?

Lazy propagation(���� ������Ʈ), ���� �ּ�/�ִ�, ��Ÿ Ŀ���� ���� �� �Ϲݼ�/Ȯ�强�� �ʿ��� ��

�ڵ尡 ���� ���� �ǹ�(��� v�� [tl,tr] ���)�� �巯�� �������̶� ������Ȯ�忡 �����մϴ�.