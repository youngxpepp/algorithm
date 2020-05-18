#include <iostream>
#include <vector>

using namespace std;

void siftDown(vector<int>& v, int current, int last) {
    while((current * 2) + 1 <= last) {
        int leftChild = (current * 2) + 1;
        int rightChild = (current * 2) + 2;
        int max = current;

        if(v[leftChild] > v[max]) {
            max = leftChild;
        }

        if(rightChild <= last && v[rightChild] > v[max]) {
            max = rightChild;
        }

        if(max != current) {
            int temp = v[current];
            v[current] = v[max];
            v[max] = temp;
            current = max;
        } else {
            return;
        }
    }
}

void heapifyBottomUp(vector<int>& v) {
    int lastIndex = v.size() - 1;
    int current = (lastIndex - 1) / 2;
    while(current >= 0) {
        siftDown(v, current, lastIndex);
        current--;
    }
}

void siftUp(vector<int>& v, int current) {
    int parent = (current - 1) / 2;
    while(current > 0 && v[current] > v[parent]) {
        int temp = v[current];
        v[current] = v[parent];
        v[parent] = temp;
        current = parent;
        parent = (current - 1) / 2;
    }
}

void heapifyTopDown(vector<int>& v) {
    for(int i = 1; i < v.size(); i++) {
        siftUp(v, i);
    }
}

void heapSort(vector<int>& v) {
    heapifyTopDown(v);

    for(int i = v.size() - 1; i > 0; i--) {
        int temp = v[0];
        v[0] = v[i];
        v[i] = temp;

        siftDown(v, 0, i - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N = 0;
    cin >> N;

    vector<int> v(N, 0);

    for(int i = 0; i < N; i++) {
        cin >> v[i];
    }

    heapSort(v);

    for(const auto& element : v) {
        cout << element << "\n";
    }
    
    return 0;
}