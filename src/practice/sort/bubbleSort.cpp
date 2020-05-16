#include <iostream>
#include <vector>

using namespace std;

// 오름차순 정렬
bool bubbleSort(vector<int>& v) {
    if(v.size() < 1) {
        return false;
    }

    for(int i = v.size() - 1; i >= 0; i--) {
        for(int j = 0; j < i; j++) {
            if(v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
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

    bubbleSort(test);

    for(const auto& element : test) {
        cout << element << endl;
    }


    return 0;
}