#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int main() {
    int n = 0, k = 0;

    cin >> n >> k;

    long long minNumber = 1;
    long long maxNumber = k;
    long long answer = LONG_LONG_MAX;
    while(minNumber <= maxNumber) {
        long long middleNumber = (minNumber + maxNumber) / 2;

        long long count = 0;
        for(int i = 1; i <= n; i++) {
            count += min(middleNumber / i, (long long)n);
        }

        if(count >= k) {
            maxNumber = middleNumber - 1;
            answer = middleNumber;
        } else {
            minNumber = middleNumber + 1;
        }
    }

    cout << answer << endl;

    return 0;
}
