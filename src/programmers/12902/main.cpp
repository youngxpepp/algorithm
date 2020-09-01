#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    if(n % 2 == 1) {
        return 0;
    }

    vector<long long> dpArr(n / 2 + 1, -1);
    dpArr[1] = 3;

    for(int i = 2; i < dpArr.size(); i++) {
        dpArr[i] = 3 * dpArr[i - 1] + 2;
        for(int j = 1; j < i - 1; j++) {
            dpArr[i] += 2 * dpArr[j];
        }

        dpArr[i] %= 1000000007;
    }

    return dpArr.back();
}