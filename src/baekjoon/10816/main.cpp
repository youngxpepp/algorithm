#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int get_number_begin_index(int *arr, int size, int target_number) {
    int begin_index = 0;
    int end_index = size - 1;

    while (begin_index <= end_index) {
        int mid_index = (begin_index + end_index) / 2;

        if (target_number < arr[mid_index]) {
            end_index = mid_index - 1;
        } else if (target_number > arr[mid_index]) {
            begin_index = mid_index + 1;
        } else {
            int left = mid_index;
            while (left > 0 && arr[left - 1] == target_number) {
                left--;
            }
            return left;
        }
    }

    return -1;
}

int get_number_end_index(int *arr, int size, int target_number) {
    int begin_index = 0;
    int end_index = size - 1;

    while (begin_index <= end_index) {
        int mid_index = (begin_index + end_index) / 2;

        if (target_number < arr[mid_index]) {
            end_index = mid_index - 1;
        } else if (target_number > arr[mid_index]) {
            begin_index = mid_index + 1;
        } else {
            int right = mid_index;
            while (right < size - 1 && arr[right + 1] == target_number) {
                right++;
            }
            return right;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int arr[500000] = {0,};
    int _arr[500000] = {0,};
    unordered_map<int, int> cache;

    int n = 0, m = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> _arr[i];
    }

    for (int i = 0; i < m; i++) {
        auto itr = cache.find(_arr[i]);

        if (itr != cache.end()) {
            cout << itr->second << " ";
            continue;
        }

        int start_index = get_number_begin_index(arr, n, _arr[i]);
        int end_index = get_number_end_index(arr, n, _arr[i]);

        if (start_index == -1) {
            cout << 0 << " ";
            cache[_arr[i]] = 0;
            continue;
        }

        cout << end_index - start_index + 1 << " ";
        cache[_arr[i]] = end_index - start_index + 1;
    }

    return 0;
}
