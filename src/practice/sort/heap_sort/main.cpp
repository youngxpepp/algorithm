#include <iostream>

using namespace std;

void sift_down(int *arr, int n, int node_num) {
    int i = node_num;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    while (left < n) {
        int min_node = i;

        if (arr[left] > arr[min_node]) {
            min_node = left;
        }

        if (right < n && arr[right] > arr[min_node]) {
            min_node = right;
        }

        if (i != min_node) {
            swap(arr[i], arr[min_node]);
            i = min_node;
            left = 2 * i + 1;
            right = 2 * i + 2;
        } else {
            break;
        }
    }
}

void sift_up(int *arr, int node_num) {
    int i = node_num;
    int parent = (node_num - 1) / 2;
    while (i != 0 && arr[i] > arr[parent]) {
        swap(arr[i], arr[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void heapify(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        sift_up(arr, i);
    }
}

void heap_sort(int *arr, int n) {
    heapify(arr, n);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[i], arr[0]);
        sift_down(arr, i, 0);
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

    heap_sort(num_arr, n);

    for (int i = 0; i < n; i++) {
        cout << num_arr[i] << "\n";
    }

    return 0;
}
