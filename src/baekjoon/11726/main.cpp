#include <iostream>
#include <vector>

using namespace std;

vector<int> dp_arr;

int dp(int i) {
    if (dp_arr[i] != -1) {
        return dp_arr[i];
    }

    if (i == 1) {
        return 1;
    } else if (i == 2) {
        return 2;
    }

    int left = dp(i - 2);
    int right = dp(i - 1);
    int value = (left + right) % 10007;
    dp_arr[i] = value;
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0;
    cin >> n;
    dp_arr.assign(n + 1, -1);

    cout << dp(n) << '\n';

    return 0;
}
