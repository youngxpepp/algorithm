#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<int> &numbers, int n, int m) {
    if(numbers.size() == m) {
        for(int i = 0; i < numbers.size(); i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
        return;
    }

    int beginNumber = 1;
    if(!numbers.empty()) {
        beginNumber = numbers.back();
    }

    for(int i = beginNumber; i <= n; i++) {
        numbers.push_back(i);
        dfs(numbers, n, m);
        numbers.pop_back();
    }
}

int main() {
    int n = 0, m = 0;

    cin >> n >> m;

    vector<int> numbers;
    dfs(numbers, n, m);

    return 0;
}
