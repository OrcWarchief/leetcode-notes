LeetCode 316 ? Remove Duplicate Letters (README)
���� ���
���ڿ� s���� �� ���ڸ� ��Ȯ�� �� �� �����ϸ鼭 ���������� ���� ���� ���ڿ��� ��ȯ�մϴ�. ����� s�� ������������� �ϸ�, �츮�� ������ �� �� �ֽ��ϴ�.

��:

bcabc �� abc

cbacdcbc �� acdb

�ٽ� ���̵�� (���� ���� + �̷� ����)
���� ���ڸ� ä��/�����Ϸ��� �� ���ڰ� �ڿ� �ٽ� �����ϴ��� �˾ƾ� �ؿ�.

���� count�� �� ������ ���� ������ ����, ��� ���ڿ��� ����ó�� ����մϴ�.

���� top�� ���� ���ں��� ũ��, top ���ڰ� �ڿ��� ���� ������ pop�Ͽ� �� ���� �������� ����ϴ�.

C++ ����
cpp
����
#include <string>
#include <array>
using namespace std;

string removeDuplicateLetters(const string& s) {
    array<int, 256> cnt{};
    array<bool, 256> used{};
    for (unsigned char uc : s) cnt[uc]++;

    string res;
    res.reserve(s.size());

    for (unsigned char uc : s) {
        cnt[uc]--;
        if (used[uc]) continue;

        while (!res.empty() &&
               uc < static_cast<unsigned char>(res.back()) &&
               cnt[static_cast<unsigned char>(res.back())] > 0) {
            used[static_cast<unsigned char>(res.back())] = false;
            res.pop_back();
        }
        res.push_back(static_cast<char>(uc));
        used[uc] = true;
    }
    return res;
}
���⵵
�ð�: O(n)

����: O(1) (���� ���ĺ� ����; ���⼱ 256����Ʈ ���̺�)

���� �Ǽ� / ��
v.clear()�� �����̰�, 0���� ä���� std::fill�̿���.

char �ε��� �� ���� ���� �� unsigned char ĳ���� ����.

pop�� �ݵ�� top ���ڰ� �ڿ� �ٽ� ������ ���� ����.