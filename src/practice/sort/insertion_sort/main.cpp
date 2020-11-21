#include <iostream>

using namespace std;

void insertion_sort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int j = i;

        while (j - 1 >= 0 && arr[j - 1] > arr[j]) {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
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

    insertion_sort(num_arr, n);

    for (int i = 0; i < n; i++) {
        cout << num_arr[i] << "\n";
    }

    return 0;
}
