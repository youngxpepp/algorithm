#include <iostream>
#include <vector>

using namespace std;

int divide(vector<int> &num_vector, const int left, const int right) {
    int mid = (left + right) / 2;
    int pivot = num_vector[mid];
    int i = left;
    int j = right;

    while (i <= j) {
        while (num_vector[i] < pivot) {
            i++;
        }
        while (num_vector[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(num_vector[i], num_vector[j]);
            i++;
            j--;
        }
    }

    return i;
}

void quick_sort(vector<int> &num_vector, const int left, const int right) {
    if (left < right) {
        int mid = divide(num_vector, left, right);
        quick_sort(num_vector, left, mid - 1);
        quick_sort(num_vector, mid, right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;
    vector<int> num_vector(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> num_vector[i];
    }

    quick_sort(num_vector, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << num_vector[i] << "\n";
    }

    return 0;
}
