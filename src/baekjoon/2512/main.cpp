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

    int limit = arr.back();
    while (limit >= 0) {
        int sum = 0;
        for (int e : arr) {
            if (e > limit) {
                sum += limit;
                continue;
            }
            sum += e;
        }
        if (sum <= total) {
            cout << limit << '\n';
            break;
        }
        limit--;
    }

    return 0;
}
