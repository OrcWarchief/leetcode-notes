LeetCode 20 ? Valid Parentheses (유효한 괄호)
문자열 s가 주어졌을 때, (), [], {} 괄호들이 올바르게 짝을 이루고 있는지 판별하는 문제입니다.

문제 요약
여는 괄호는 반드시 같은 종류의 닫는 괄호로 닫혀야 합니다.

여는 괄호는 올바른 순서로 닫혀야 합니다.

빈 문자열 ""도 유효한 것으로 간주합니다.

예시:

s = "()" → true

s = "()[]{}" → true

s = "(]" → false

s = "([)]" → false

s = "{[]}" → true

풀이 아이디어 (Stack)
문자 하나씩 순회

여는 괄호 (, [, { → 스택에 push

닫는 괄호 ), ], } →

스택이 비어있으면 잘못된 케이스 → false

스택 top과 종류가 일치하면 pop, 아니면 false

순회 종료 후 스택이 비어있으면 true, 아니면 false

핵심 포인트
닫는 괄호를 만났을 때 항상 먼저 st.empty() 확인하기
(스택이 비어있는데 top()을 호출하면 런타임 오류!)

정답 코드 (C++)
cpp
복사
편집
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                char open = st.top(); st.pop();
                if ((c == ')' && open != '(') ||
                    (c == ']' && open != '[') ||
                    (c == '}' && open != '{')) {
                    return false;
                }
            }
        }
        return st.empty();
    }
};
시간·공간 복잡도
시간복잡도: O(n) ? 각 문자를 한 번씩 처리

공간복잡도: O(n) ? 최악의 경우 전부 여는 괄호일 때 스택 크기 n

엣지 케이스 체크리스트
첫 문자가 닫는 괄호: ")(", "]" → false

종류 불일치: "(]", "([)]" → false

순서는 맞지만 남는 여는 괄호가 있음: "(((" → false

빈 문자열: "" → true

한 쌍만 있는 기본 케이스: "()", "[]", "{}" → true

자주 하는 실수
스택 비어있을 때 top() 호출 → 런타임 오류
→ 닫는 괄호 처리 시 먼저 st.empty() 검사

모든 괄호를 처리한 뒤 스택 비었는지 확인 누락
→ 마지막에 반드시 st.empty() 반환

빠른 테스트 (예시)
cpp
복사
편집
// 간단한 수동 테스트 아이디어
// 기대값: T T F F T F T
vector<string> cases = {
    "()", "()[]{}", "(]", "([)]", "{[]}", "(((", ""
};
for (auto& s : cases) {
    cout << boolalpha << Solution().isValid(s) << " ";
}
확장 아이디어
입력에 괄호 외 문자 섞임 → 괄호만 필터링 후 검사

새로운 괄호 쌍 추가(예: < > ) → 매핑만 확장

매핑을 unordered_map<char,char>로 관리하면 가독성 향상

