#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0;
    int arr[10001] = {0,};
    int max_num = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int num = 0;
        cin >> num;
        arr[num]++;
        if (num > max_num) {
            max_num = num;
        }
    }

    for (int i = 1; i <= max_num ; i++) {
        for (int j = 0; j < arr[i]; j++) {
            cout << i << "\n";
        }
    }

    return 0;
}
