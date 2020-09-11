#include <iostream>
#include <vector>
#include <functional>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, k = 0;
    cin >> n >> k;

    string input = "";
    cin >> input;

    int count = 0;
    vector<char> myStack;

    for(int i = 0; i < input.size(); i++) {
        if(myStack.empty()) {
            myStack.push_back(input[i]);
            continue;
        }

        while(!myStack.empty() && myStack.back() < input[i] && count < k) {
            myStack.pop_back();
            count++;
        }

        if(myStack.size() >= n - k) {
            continue;
        }

        myStack.push_back(input[i]);
    }

    string answer = "";
    for(int i = 0; i < myStack.size(); i++) {
        answer += myStack[i];
    }

    cout << answer;

    return 0;
}
