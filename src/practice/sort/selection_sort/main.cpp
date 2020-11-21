#include <iostream>

using namespace std;

void selection_sort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
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

    selection_sort(num_arr, n);

    for (int i = 0; i < n; i++) {
        cout << num_arr[i] << "\n";
    }

    return 0;
}
