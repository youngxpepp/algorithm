#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <functional>

using namespace std;

long long calculate(long long a, long long b, char stringOperator) {
    switch (stringOperator) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        default:
            break;
    }

    return 0;
}

long long caculateAsPriorities(vector<long long> numbers, vector<char> operators, vector<char> priority) {
    int priorityIndex = 0;
    while(!operators.empty()) {
        const auto itr = find(operators.begin(), operators.end(), priority[priorityIndex]);
        if(itr == operators.end()) {
            priorityIndex++;
            continue;
        }

        const int index = itr - operators.begin();
        long long a = numbers[index];
        long long b = numbers[index + 1];
        long long result = calculate(a, b, operators[index]);

        operators.erase(itr);
        numbers.erase(numbers.begin() + index + 1);
        numbers.erase(numbers.begin() + index);

        numbers.insert(numbers.begin() + index, result);
    }

    return *numbers.begin();
}

long long solution(string expression) {
    string buffer = "";
    vector<long long> numbers;
    vector<char> operators;

    for(int i = 0; i < expression.size(); i++) {
        if(expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            numbers.push_back(stoi(buffer));
            operators.push_back(expression[i]);
            buffer = "";
            continue;
        }
        buffer += expression[i];

        if(i == expression.size() - 1) {
            numbers.push_back(stoi(buffer));
        }
    }

    vector<char> operatorChars{'+', '-', '*'};
    vector<vector<char>> priorities;
    queue<vector<char>> operatorQueue;
    operatorQueue.push({'+'});
    operatorQueue.push({'-'});
    operatorQueue.push({'*'});

    while(!operatorQueue.empty()) {
        vector<char> now = operatorQueue.front();
        operatorQueue.pop();

        if(now.size() == 3) {
            priorities.push_back(now);
            continue;
        }

        for(const auto operatorChar : operatorChars) {
            bool pass = false;
            for(const auto nowChar : now) {
                if(nowChar == operatorChar) {
                    pass = true;
                    break;
                }
            }
            if(pass) {
                continue;
            }
            now.push_back(operatorChar);
            operatorQueue.push(now);
            now.pop_back();
        }
    }

    set<long long, greater<long long>> resultSet;

    for(const auto priority : priorities) {
        resultSet.insert(abs(caculateAsPriorities(numbers, operators, priority)));
    }

    return *resultSet.begin();
}

int main() {
    cout << solution("100-200*300-500+20"	);

    return 0;
}
