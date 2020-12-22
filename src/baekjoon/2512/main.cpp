#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, total = 0;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> total;
    sort(arr.begin(), arr.end());

    int total_sum = 0;
    for (int e : arr) {
        total_sum += e;
    }
    if (total_sum <= total) {
        cout << arr.back() << '\n';
        return 0;
    }

    int answer = 0;
    int left = 0;
    int right = arr.back();
    while (left <= right) {
        int mid = (left + right) / 2;
        int sum = 0;
        for (int e : arr) {
            if (e > mid) {
                sum += mid;
                continue;
            }
            sum += e;
        }

        if (sum > total) {
            right = mid - 1;
        } else {
            answer = mid;
            left = mid + 1;
        }
    }

    cout << answer << '\n';

    return 0;
}
