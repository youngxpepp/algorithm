#include <iostream>

using namespace std;

int divide(int *arr, const int left, const int right) {
    int pivot = left;
    int i = left + 1;
    int j = right;

    while(i <= j) {
        while(i <= right && arr[i] <= arr[pivot]) {
            i++;
        }
        while(j > left && arr[j] >= arr[pivot]) {
            j--;
        }

        if(i > j) {
            swap(arr[left], arr[j]);
        } else {
            swap(arr[i], arr[j]);
        }
    }

    return i;
}

void quick_sort(int *arr, const int left, const int right) {
    if (left < right) {
        int pivot = divide(arr, left, right);
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot, right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    int num_arr[1000] = {0,};
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> num_arr[i];
    }

    quick_sort(num_arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << num_arr[i] << "\n";
    }

    return 0;
}
