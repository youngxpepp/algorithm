#include <iostream>
#include <vector>

using namespace std;

vector<int> stairs;
vector<vector<int>> cache_map;

int dp(int i, int is_right_below) {
    if (cache_map[i][is_right_below] != -1) {
        return cache_map[i][is_right_below];
    }

    if (i == 0) {
        return stairs[0];
    } else if (i == 1) {
        if (is_right_below == 1) {
            return stairs[1];
        } else if (is_right_below == 0) {
            return stairs[0] + stairs[1];
        }
    }

    if (is_right_below == 1) {
        int second = dp(i - 2, 0);
        cache_map[i][is_right_below] = second + stairs[i];
        return second + stairs[i];
    } else if (is_right_below == 0) {
        int second = dp(i - 2, 0);
        int first = dp(i - 1, 1);
        if (second <= first) {
            cache_map[i][is_right_below] = first + stairs[i];
            return first + stairs[i];
        } else {
            cache_map[i][is_right_below] = second + stairs[i];
            return second + stairs[i];
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0;
    cin >> n;

    stairs.assign(n, 0);
    cache_map.assign(n, vector<int>(2, -1));

    for (int i = 0; i < n; i++) {
        cin >> stairs[i];
    }

    cout << dp(n - 1, 0) << '\n';

    return 0;
}
