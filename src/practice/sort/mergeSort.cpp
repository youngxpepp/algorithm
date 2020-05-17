#include <iostream>
#include <vector>

using namespace std;

int* sortedArr;

void merge(int arr[], int start, int end) {
    int middle = (start + end) / 2;
    int i = start;
    int j = middle + 1;
    int k = start;

    while(i <= middle && j <= end) {
        if(arr[i] <= arr[j]) {
            sortedArr[k] = arr[i];
            i++;
        } else {
            sortedArr[k] = arr[j];
            j++;
        }
        k++;
    }

    while(i <= middle) {
        sortedArr[k] = arr[i];
        i++;
        k++;
    }
    while(j <= end) {
        sortedArr[k] = arr[j];
        j++;
        k++;
    }

    for(int t = start; t <= end; t++) {
        arr[t] = sortedArr[t];
    }
}

void mergeSort(int arr[], int start, int end) {
    if(start < end) {
        int middle = (start + end) / 2;
        mergeSort(arr, start, middle);
        mergeSort(arr, middle + 1, end);
        merge(arr, start, end);
    }
}

int main() {
    int N;
    cin >> N;

    sortedArr = new int[N];
    int arr[N];

    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, 0, N - 1);

    for(int i = 0; i < N; i++) {
        cout << arr[i] << endl;
    }

    return 0;
}