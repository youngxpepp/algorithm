#include <iostream>
#include <cmath>

using namespace std;

int dfs(int number, int count) {
    if(number == 3) {
        if(count == 2) {
            return 1;
        }
        return 0;
    } else if(number < 3) {
        return 0;
    }

    int e = 0;
    int three = 0;

    if(2 * log(number) / log(3) < count) {
        return 0;
    }

    int value = 0;

    if(number % 3 == 0 && count >= 2) {
        value += dfs(number / 3, count - 2);
    }

    if(number - 1 >= 3) {
        value += dfs(number - 1, count + 1);
    }

    return value;
}

int solution(int n) {
    return dfs(n - 2, 2);
}

int main() {
    cout << solution(15) << endl;
    return 0;
}
