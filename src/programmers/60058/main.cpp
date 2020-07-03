#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isRight(string s) {
    if(s.front() != '(' || s.back() != ')') {
        return false;
    }

    int open = 0;
    while(s.size() != 0) {
        char str = s.front();
        s.erase(s.begin());

        if(str == '(') {
            open++;
        } else if(str == ')') {
            if(open == 0) {
                return false;
            }
            open--;
        }
    }

    return true;
}

string process(string w) {
    if(w == "") {
        return "";
    }

    string u = "", v = "";

    stack<int> wStack;
    for(int i = w.size() - 1; i >= 0; i--) {
        wStack.push(w[i]);
    }

    int open = 0;
    int close = 0;
    int index = -1;
    int uSize = 0;

    while(!wStack.empty()) {
        index++;
        if(wStack.top() == '(') {
            open++;
        } else if(wStack.top() == ')') {
            close++;
        }

        if(open == close && uSize == 0) {
            uSize = index + 1;
            u = w.substr(0, uSize);
            v = w.substr(uSize);
            break;
        }

        wStack.pop();
    }

    if(isRight(u)) {
        return u + process(v);
    }

    string returned = "(";
    returned += process(v);
    returned += ')';

    u.erase(u.begin());
    u.pop_back();

    for(int i = 0; i < u.size(); i++) {
        if(u[i] == '(') {
            u[i] = ')';
        } else if(u[i] == ')') {
            u[i] = '(';
        }
    }

    returned += u;

    return returned;
}

string solution(string p) {
    return process(p);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/*
1. 입력이 빈 문자열인 경우, 빈 문자열을 반환합니다.
2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리합니다. 단, u는 "균형잡힌 괄호 문자열"로 더 이상 분리할 수 없어야 하며, v는 빈 문자열이 될 수 있습니다.
3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다.
3-1. 수행한 결과 문자열을 u에 이어 붙인 후 반환합니다.
4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다.
4-1. 빈 문자열에 첫 번째 문자로 '('를 붙입니다.
4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다.
4-3. ')'를 다시 붙입니다.
4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다.
4-5. 생성된 문자열을 반환합니다.
*/
