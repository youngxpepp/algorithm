#include <iostream>

using namespace std;

int temp_arr[1000000] = {0,};

void merge(int *arr, int left, int right) {
    int mid = (left + right) / 2;
    int i = left;
    int j = mid + 1;
    int now = left;

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp_arr[now++] = arr[i++];
        } else {
            temp_arr[now++] = arr[j++];
        }
    }

    if (i <= mid) {
        for (int t = i; t <= mid; t++) {
            temp_arr[now++] = arr[i++];
        }
    }

    if (j <= right) {
        for (int t = j; t <= right; t++) {
            temp_arr[now++] = arr[j++];
        }
    }

    for (int t = left; t <= right; t++) {
        arr[t] = temp_arr[t];
    }
}

void merge_sort(int *arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    int num_arr[1000000] = {0,};
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> num_arr[i];
    }

    merge_sort(num_arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << num_arr[i] << "\n";
    }

    return 0;
}
