#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_min(const string &str) {
    int result = 0;
    string num_string = "";
    char prev_operator = '+';
    for (const char &c : str) {
        if (c == '+') {
            int num = stoi(num_string);
            num_string = "";
            if (prev_operator == '+') {
                result += num;
            } else if (prev_operator == '-') {
                result -= num;
            }
        } else if (c == '-') {
            int num = stoi(num_string);
            num_string = "";
            if (prev_operator == '+') {
                result += num;
                prev_operator = '-';
            } else if (prev_operator == '-') {
                result -= num;
            }
        } else {
            num_string += c;
        }
    }

    int num = stoi(num_string);
    if (prev_operator == '+') {
        result += num;
    } else if (prev_operator == '-') {
        result -= num;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string input = "";
    cin >> input;

    cout << get_min(input) << '\n';

    return 0;
}
