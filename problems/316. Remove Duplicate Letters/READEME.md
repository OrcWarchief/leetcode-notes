LeetCode 316 ? Remove Duplicate Letters (README)
문제 요약
문자열 s에서 각 문자를 정확히 한 번 포함하면서 사전순으로 가장 작은 문자열을 반환합니다. 결과는 s의 서브시퀀스여야 하며, 우리는 삭제만 할 수 있습니다.

예:

bcabc → abc

cbacdcbc → acdb

핵심 아이디어 (단조 스택 + 미래 정보)
현재 문자를 채택/제거하려면 그 문자가 뒤에 다시 등장하는지 알아야 해요.

먼저 count로 각 문자의 남은 개수를 세고, 결과 문자열을 스택처럼 사용합니다.

스택 top이 현재 문자보다 크고, top 문자가 뒤에도 남아 있으면 pop하여 더 작은 사전순을 만듭니다.

C++ 구현
cpp
복사
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
복잡도
시간: O(n)

공간: O(1) (고정 알파벳 가정; 여기선 256바이트 테이블)

흔한 실수 / 팁
v.clear()는 비우기이고, 0으로 채우기는 std::fill이에요.

char 인덱싱 시 음수 방지 → unsigned char 캐스팅 권장.

pop은 반드시 top 문자가 뒤에 다시 등장할 때만 수행.