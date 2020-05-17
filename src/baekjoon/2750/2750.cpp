#include <iostream>
#include <vector>

using namespace std;

bool selectionSort(vector<int>& v) {
    if(v.empty()) {
        return false;
    }
    
    for(int i = 0; i < v.size(); i++) {
        int minValue = v[i];
        int minIndex = i;
        for(int j = i + 1; j < v.size(); j++) {
            if(v[j] < minValue) {
                minValue = v[j];
                minIndex = j;
            }
        }
        if(minIndex != i) {
            v[minIndex] = v[i];
            v[i] = minValue;
        }
    }

    return true;
}

bool bubbleSort(vector<int>& v) {
    if(v.empty()) {
        return false;
    }

    int nowIndex = v.size();
    while(nowIndex != 0) {
        for(int i = 0; i < nowIndex - 1; i++) {
            if(v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
            }
        }
        nowIndex--;
    }

    return true;
}

bool insertionSort(vector<int>& v) {
    if(v.empty()) {
        return false;
    }

    for(int i = 1; i < v.size(); i++) {
        int nowIndex = i;
        while(nowIndex != 0 && v[nowIndex] < v[nowIndex - 1]) {
            int temp = v[nowIndex];
            v[nowIndex] = v[nowIndex - 1];
            v[nowIndex - 1] = temp;
            nowIndex--;
        }
    }

    return true;
}

int main() {
    int N = 0;
    cin >> N;

    vector<int> v;

    for(int i = 0; i < N; i++) {
        int input;
        cin >> input;
        v.push_back(input);
    }

    // selectionSort(v);
    // bubbleSort(v);
    insertionSort(v);

    for(const auto& element : v) {
        cout << element << endl;
    }
    
    return 0;
}