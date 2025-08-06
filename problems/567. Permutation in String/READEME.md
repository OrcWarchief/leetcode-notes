README ? LeetCode?567 Permutation?in?String (C++)

1. ���� ���
�Է�

s1: ���� n ��?10?000�� �ҹ��� ���ڿ�

s2: ���� m ��?10?000�� �ҹ��� ���ڿ�

���

true?/?false �� s2 �ȿ� s1�� ����(permutation) �� ���� �κй��ڿ��� �����ϸ� true, �ƴϸ� false.

�ٽ�

s1�� ��� ���� �󵵸� ��Ȯ�� ���� ���� n¥�� ������ s2�� �����ϴ��� �˻�.

2. �˰��� �Ѵ��� ����
���	����
�����̵� ������	���� n ���� ������ �� ĭ�� �̵��ϸ� �˻�
���� ũ�� �� �迭(26)	���ĺ��� �ٷ�Ƿ� unordered_map���� ������ �޸𸮵� ����
���� �� O(1)	���� �̵� �� ������ ���� +1, ���� ���� ?1�� ������ ��� ��ġ ���� �Ǵ�

��������� O(m) �ð�, O(1) ���� �޼�.

3. �ܰ躰 ����
���� �˻�
n > m �̸� ���� �Ұ� �� ��� false.

�ʿ� ��(need)������ ����(window) �迭 �ʱ�ȭ

cpp
����
int need[26] = {0}, window[26] = {0};
for (char c : s1) need[c - 'a']++;
for (int i = 0; i < n; ++i) window[s2[i] - 'a']++;
�� �迭 ��

�� �迭�� ������ ������ ��ٷ� true.

�����̵� (i = n �� m-1)

������ �� ���� +1

���� ���� ������ ���� -1

��ȭ �� �� �迭�� ��ġ�ϸ� true.

������ �����ٸ� false.

4. �ٽ� �ڵ� ������
cpp
����
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        if (n > m) return false;

        int need[26] = {0}, window[26] = {0};
        for (char c : s1) need[c - 'a']++;
        for (int i = 0; i < n; ++i) window[s2[i] - 'a']++;

        auto same = [&](){
            for (int k = 0; k < 26; ++k)
                if (need[k] != window[k]) return false;
            return true;
        };
        if (same()) return true;

        for (int i = n; i < m; ++i) {
            window[s2[i] - 'a']++;          // in
            window[s2[i - n] - 'a']--;      // out
            if (same()) return true;
        }
        return false;
    }
};
5. �ð������� ���⵵
���⵵
�ð�	`O(
����	O(26) �� ���

6. ���� Ʋ���� ����Ʈ
�հ�(sum)�� ��

'ab'(0?+?1) vs 'c'(2): �浹 ���� �� X

vector �ʱⰪ ���� �ε��� ����

Segfault ���� �� �ݵ�� resize �Ǵ� push_back ���.

���ʿ��� ��ü ����

������ �̵��� ������ �迭�� ���� ����� ���� O(n��m)�̹Ƿ� ����.

7. ���� �����ε� üũ����Ʈ
 n > m? �� ��� false

 ���ĺ��� 26�� �� ���� �迭 ���

 �ʱ� ���� ä��� �ٷ� ��

 ������ ���� +1, ���� ���� ?1�� �� ��� ��

8. ���� & �׽�Ʈ ����
bash
����
g++ -std=c++17 -O2 solution.cpp -o perm
./perm          # �׽�Ʈ�ڵ�(main) ���� ��
���� �׽�Ʈ
s1	s2	���
"ab"	"eidbaooo"	true
"ab"	"eidboaoo"	false
"adc"	"dcda"	true

9. Ȯ�� ���̵��
�ٸ� ���� ���� �� unordered_map<char,int>���� �Ϲ�ȭ.

�ǽð� ��Ʈ������ ���� ���� ������ �� ���� ���� ���� ����.

�� ū ���ĺ�(M ��?256) �� �迭�� ������ ȿ����.

��.