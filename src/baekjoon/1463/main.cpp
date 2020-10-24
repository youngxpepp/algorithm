#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int x = 0;
vector<int> dp_table;

int get_min_count(int x) {
    if (dp_table[x] != -1) {
        return dp_table[x];
    }

    int value = INT_MAX;
    if (x % 3 == 0) {
        value = min(value, get_min_count(x / 3));
    }
    if (x % 2 == 0) {
        value = min(value, get_min_count(x / 2));
    }
    value = min(value, get_min_count(x - 1));

    value++;
    dp_table[x] = value;

    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> x;

    dp_table.assign(x + 1, -1);
    dp_table[1] = 0;

    for (int i = 2; i <= x; i++) {
        get_min_count(i);
    }

    cout << dp_table[x] << '\n';

    return 0;
}
