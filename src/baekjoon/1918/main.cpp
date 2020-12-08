#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool is_operator(const char &c) {
    return c == '+' || c== '-' || c == '*' || c == '/';
}

string convert_to_postfix_notation(const string &original_expression) {
    string expression = "";
    stack<char> expression_stack;
    for (int i = 0; i < original_expression.size(); i++) {
        switch (original_expression[i]) {
            case '*':
            case '/':
                if (!expression_stack.empty() && (expression_stack.top() == '*' || expression_stack.top() == '/')) {
                    expression += expression_stack.top();
                    expression_stack.pop();
                }
                expression_stack.push(original_expression[i]);
                break;
            case '+':
            case '-':
                while (!expression_stack.empty() && is_operator(expression_stack.top())) {
                    expression += expression_stack.top();
                    expression_stack.pop();
                }
                expression_stack.push(original_expression[i]);
                break;
            case '(':
                expression_stack.push(original_expression[i]);
                break;
            case ')':
                while (!expression_stack.empty() && expression_stack.top() != '(') {
                    expression += expression_stack.top();
                    expression_stack.pop();
                }
                expression_stack.pop();
                break;
            default:
                if (original_expression[i] >= 'A' && original_expression[i] <= 'Z') {
                    expression += original_expression[i];
                }
                break;
        }

        if (i == original_expression.size() - 1) {
            while (!expression_stack.empty()) {
                expression += expression_stack.top();
                expression_stack.pop();
            }
        }
    }

    return expression;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string expression = "";

    cin >> expression;

    cout << convert_to_postfix_notation(expression) << "\n";

    return 0;
}
