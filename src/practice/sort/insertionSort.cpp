#include <iostream>
#include <vector>

using namespace std;

// 오름차순 정렬
bool insertionSort(vector<int>& v) {
    if(v.size() < 1) {
        return false;
    }

    vector<int> _v;
    _v.push_back(v[0]);
    
    for(int i = 1; i < v.size(); i++) {
        bool pushBack = true;
        for(int j = 0; j < _v.size(); j++) {
            if(v[i] <= _v[j]) {
                _v.insert(_v.begin() + j, v[i]);
                pushBack = false;
                break;
            }
        }
        if(pushBack) {
            _v.push_back(v[i]);
        }
    }

    v.clear();
    v.assign(_v.begin(), _v.end());

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