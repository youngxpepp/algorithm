#include <iostream>
#include <queue>
#include <limits>

using namespace std;

int charToInt(char character)
{
    int integer = character - '0';
    return integer;
}

long calculate(long firstOperand, char operation, long secondOperand)
{
    switch (operation)
    {
    case '+':
        return firstOperand + secondOperand;
    case '-':
        return firstOperand - secondOperand;
    case '*':
        return firstOperand * secondOperand;
    default:
        return -1;
    }
}

struct ExpUnit
{
    int lastIndex = 0;
    long sum = 0;

    ExpUnit(int _lastIndex, long _sum) : lastIndex(_lastIndex), sum(_sum) {}
};

int bfs(char expression[], int length)
{
    queue<ExpUnit> bfsQueue;

    if(length == 1)
    {
        return charToInt(expression[0]);
    }

    bfsQueue.push(ExpUnit(0, charToInt(expression[0])));
    bfsQueue.push(ExpUnit(2, calculate(charToInt(expression[0]), expression[1], charToInt(expression[2]))));

    long max = INT64_MIN;

    while (!bfsQueue.empty())
    {
        int lastIndex = bfsQueue.front().lastIndex;
        long sum = bfsQueue.front().sum;
        bfsQueue.pop();

        if (lastIndex == length - 1)
        {
            if (sum > max)
            {
                max = sum;
            }
            continue;
        }

        bfsQueue.push(ExpUnit(lastIndex + 2, calculate(sum, expression[lastIndex + 1], charToInt(expression[lastIndex + 2]))));

        if (lastIndex <= length - 5)
        {
            bfsQueue.push(ExpUnit(lastIndex + 4, calculate(sum, expression[lastIndex + 1], calculate(charToInt(expression[lastIndex + 2]), expression[lastIndex + 3], charToInt(expression[lastIndex + 4])))));
        }
    }

    return max;
}

int main()
{
    int length;
    cin >> length;

    char *expression = new char[length];
    cin >> expression;
    
    cout << bfs(expression, length) << endl;
    return 0;
}