#include <iostream>
#include <vector>

using namespace std;

// 오름차순 정렬
void quickSort(vector<int>& v, int start, int end) {
    if(start >= end) {
        return;
    }

    int pivot = start;
    int i = start + 1;
    int j = end;

    while(i <= j) {
        while(i <= end && v[i] <= v[pivot]) {
            i++;
        }
        while(j > start && v[j] >= v[pivot]) {
            j--;
        }

        if(i > j) {
            int temp = v[j];
            v[j] = v[start];
            v[start] = temp;
        } else {
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }
    quickSort(v, start, j - 1);
    quickSort(v, j + 1, end);
}

int main() {
    vector<int> test;
    test.push_back(1);
    test.push_back(5);
    test.push_back(10);
    test.push_back(8);
    test.push_back(9);
    test.push_back(7);
    test.push_back(2);
    test.push_back(4);
    test.push_back(3);
    test.push_back(6);

    quickSort(test, 0, test.size() - 1);

    for(const auto& element : test) {
        cout << element << endl;
    }


    return 0;
}