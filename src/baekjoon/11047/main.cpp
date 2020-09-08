#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0, k = 0;
    cin >> n >> k;

    vector<int> coinValues(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> coinValues[i];
    }

    int count = 0;
    int remain = k;
    for(int i = coinValues.size() - 1; i >= 0; i--) {
        int quotent = remain / coinValues[i];

        if(quotent == 0) {
            continue;
        }

        remain -= coinValues[i] * quotent;
        count += quotent;
    }

    cout << count << endl;

    return 0;
}
