#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, s = 0;
    cin >> n >> s;

    vector<int> numbers(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    long long sum = 0;
    int endIndex = 0;
    int minLength = INT_MAX;
    for(int i = 0; i < n; i++) {
        while(sum < s && endIndex < n) {
            sum += numbers[endIndex];
            endIndex++;
        }

        if(sum >= s) {
            minLength = min(minLength, endIndex - i);
        }

        sum -= numbers[i];
    }

    if(minLength == INT_MAX) {
        cout << 0;
    } else {
        cout << minLength;
    }

    return 0;
}
