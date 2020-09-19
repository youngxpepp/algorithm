#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;
    vector<int> numbers(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    vector<int> dp(n, 0);
    dp[0] = numbers[0];
    int maxSum = dp[0];

    for(int i = 1; i < n; i++) {
        dp[i] = max(dp[i - 1] + numbers[i], numbers[i]);
        maxSum = max(maxSum, dp[i]);
    }

    cout << maxSum;

    return 0;
}
