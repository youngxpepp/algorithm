#include <iostream>
#include <string>

using namespace std;

int dp_arr[5000];
string input = "";

int dp(int index) {
    if (dp_arr[index] != -1) {
        return dp_arr[index];
    }

    int result = 0;
    if (input[index] != '0') {
        result += dp(index - 1);
    }
    int second = stoi(input.substr(index - 1, 2));
    if (second >= 10 && second <= 26) {
        result += dp(index - 2);
    }

    result %= 1000000;
    dp_arr[index] = result;

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> input;

    fill_n(dp_arr, 5000, -1);

    if (input[0] == '0') {
        cout << 0 << '\n';
        return 0;
    }

    if (input.size() == 1) {
        cout << 1 << '\n';
        return 0;
    }

    dp_arr[0] = 1;
    dp_arr[1] = 0;

    if (input[1] != '0') {
        dp_arr[1] = 1;
    }

    int second = stoi(input.substr(0, 2));
    if (second >= 1 && second <= 26) {
        dp_arr[1]++;
    }

    cout << dp(input.size() - 1) << '\n';

    return 0;
}
