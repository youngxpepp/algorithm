#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    vector<int> numbers(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end());

    int answer = 0;
    for(int i = 0; i < numbers.size(); i++) {
        for(int j = 0; j <= i; j++) {
            answer += numbers[j];
        }
    }

    cout << answer;

    return 0;
}
