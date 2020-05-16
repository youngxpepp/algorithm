#include <iostream>
#include <vector>

using namespace std;

// 오름차순 정렬
bool insertionSort(vector<int>& v) {
    if(v.size() < 1) {
        return false;
    }

    for(int i = 1; i < v.size(); i++) {
        int j = i;
        while(v[j - 1] > v[j] || j == 0) {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
            j--;
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

    insertionSort(test);

    for(const auto& element : test) {
        cout << element << endl;
    }


    return 0;
}