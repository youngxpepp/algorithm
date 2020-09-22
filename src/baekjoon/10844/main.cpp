#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<vector<int>> dp;

int dpFunction(int n, int m) {
    if(n == 1) {
        return dp[1][m];
    } else {
        if(dp[n][m] != -1) {
            return dp[n][m];
        }
        if(m == 0) {
            return dp[n][m] = dpFunction(n - 1, 1) % 1000000000;
        } else if(m == 9) {
            return dp[n][m] = dpFunction(n - 1, 8) % 1000000000;
        } else {
            return dp[n][m] = (dpFunction(n - 1, m - 1) + dpFunction(n - 1, m + 1)) % 1000000000;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    dp.assign(n + 1, vector<int>(10, -1));

    dp[1][0] = 0;
    for(int i = 1; i < 10; i++) {
        dp[1][i] = 1;
    }

    int answer = 0;

    for(int i = 0; i < 10; i++) {
        answer += dpFunction(n, i);
        answer %= 1000000000;
    }

    cout << answer;

    return 0;
}
