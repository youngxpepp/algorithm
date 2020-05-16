#include <iostream>
#include <vector>

using namespace std;

// 오름차순 정렬
bool selectionSort(vector<int>& v) {
    if(v.size() < 1) {
        return false;
    }

    for(int i = 0; i < v.size(); i++) {
        int minValue = v[i];
        int minIndex = i;
        for(int j = i; j < v.size(); j++) {
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

    selectionSort(test);

    for(const auto& element : test) {
        cout << element << endl;
    }


    return 0;
}