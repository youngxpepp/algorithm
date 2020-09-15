#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long x = 0, y = 0;
    cin >> x >> y;

    int z = (100 * y) / x;

    if(z >= 99) {
        cout << -1;
        return 0;
    }

    long long answer = LONG_LONG_MAX;
    long long left = 1;
    long long right = 99 * x - 100 * y;

    while(left <= right) {
        long long mid = (left + right) / 2;
        int nz = (100 * y + 100 * mid) / (x + mid);

        if(nz >= z + 1) {
            answer = min(answer, mid);
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if(answer == LONG_LONG_MAX) {
        cout << -1;
    } else {
        cout << answer;
    }

    return 0;
}
