#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int>& v, int size) {
    if(size < 1) {
        return;
    }
    
    for(int i = 1; i < size; i++) {
        int current = i;
        int root = (current - 1) / 2;

        while(v[current] > v[root] && current != 0) {
            int temp = v[current];
            v[current] = v[root];
            v[root] = temp;
            current = root;
            root = (current - 1) / 2;
        }
    }
}

void heapSort(vector<int>& v) {
    int lastIndex = v.size() - 1;
    while(lastIndex != 0) {
        int temp = v[lastIndex];
        v[lastIndex] = v[0];
        v[0] = temp;

        heapify(v, lastIndex);
        lastIndex--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> v;

    for(int i = 0; i < N; i++) {
        int input;
        cin >> input;
        v.push_back(input);
    }

    heapify(v, v.size());
    heapSort(v);

    for(const auto& element : v) {
        cout << element << " ";
    }

    return 0;
}