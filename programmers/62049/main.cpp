#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> foldPaper(int n) {
    if(n == 1) {
        return vector<int>(1, 0);
    }
    
    vector<int> prevArray = foldPaper(n - 1);
    vector<int> array;
    
    int prevArrayIndex = 0;
    bool isArrayTurn = false;
    bool isZeroTurn = true;
    int rounds = pow(2, n) - 1;
    for(int i = 0; i < rounds; i++) {
        if(isArrayTurn) {
            array.push_back(prevArray[prevArrayIndex]);
            prevArrayIndex++;
            isArrayTurn = !isArrayTurn;
        } else {
            if(isZeroTurn) {
                array.push_back(0);
            } else {
                array.push_back(1);
            }
            isZeroTurn = !isZeroTurn;
            isArrayTurn = !isArrayTurn;
        }
    }

    return array;
}

vector<int> solution(int n) {
    return foldPaper(n);
}

int main() {
    int n;
    cin >> n;

    vector<int> output = solution(n);

    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    
    return 0;
}