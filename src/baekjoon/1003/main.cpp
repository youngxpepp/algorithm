#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, pair<int, int>> memoization;

pair<int, int> fibo(int n) {
    if(n == 0) {
        return {1, 0};
    } else if(n == 1) {
        return {0, 1};
    } else {
        pair<int, int> left = {0, 0};
        pair<int, int> right = {0, 0};

        auto leftItr = memoization.find(n - 2);
        if(leftItr == memoization.end()) {
            left = fibo(n - 2);
        } else {
            left = leftItr->second;
        }

        auto rightItr = memoization.find(n - 1);
        if(rightItr == memoization.end()) {
            right = fibo(n - 1);
        } else {
            right = rightItr->second;
        }

        pair<int, int> result = {left.first + right.first, left.second + right.second};
        memoization[n] = result;

        return result;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 0;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int n = 0;
        cin >> n;

        auto itr = memoization.find(n);
        if(itr == memoization.end()) {
            pair<int, int> answer = fibo(n);
            cout << answer.first << " " << answer.second << "\n";
        } else {
            cout << itr->second.first << " " << itr->second.second << "\n";
        }
    }

    return 0;
}
