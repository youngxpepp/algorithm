#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool findNumber(int number, vector<int> &numbers) {
    int beginIndex = 0;
    int endIndex = numbers.size() - 1;

    while(true) {
        if(beginIndex > endIndex) {
            break;
        }

        int middleIndex = (beginIndex + endIndex) / 2;

        if(number > numbers[middleIndex]) {
            beginIndex = middleIndex + 1;
        } else if(number < numbers[middleIndex]) {
            endIndex = middleIndex - 1;
        } else {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, m = 0;

    cin >> n;

    vector<int> firstNums(n , 0);

    for(int i = 0; i < n; i++) {
        cin >> firstNums[i];
    }

    cin >> m;

    vector<int> secondNums(m, 0);

    for(int i = 0; i < m; i++) {
        cin >> secondNums[i];
    }

    sort(firstNums.begin(), firstNums.end());

    for(const auto element : secondNums) {
        if(findNumber(element, firstNums)) {
            cout << 1 << "\n";
            continue;
        }
        cout << 0 << "\n";
    }

    return 0;
}
