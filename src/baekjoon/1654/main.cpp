#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int k = 0, n = 0;

    cin >> k >> n;

    vector<long long> cables(k, 0);

    for(int i = 0; i < k; i++) {
        cin >> cables[i];
    }

    sort(cables.begin(), cables.end());

    long long answer = 0;
    long long minLength = 1;
    long long maxLength = cables.back();

    while(minLength <= maxLength) {
        long long middle = (minLength + maxLength) / 2;

        int sum = 0;
        for(int i = 0; i < cables.size(); i++) {
            sum += (cables[i] / middle);
        }

        if(n <= sum) {
            answer = max(answer, middle);
            minLength = middle + 1;
        } else if(n > sum) {
            maxLength = middle - 1;
        }
    }

    cout << answer;

    return 0;
}
