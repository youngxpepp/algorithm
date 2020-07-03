#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int answer = 1001;

    for(int i = 1; i <= s.size(); i++) {
        int count = 0;
        string piece = s.substr(0, i);
        string compressed = "";

        for(int j = 0; j < s.size(); j += i) {
            if(s.substr(j, i) == piece) {
                count++;
                continue;;
            }

            if(count == 1) {
                compressed += piece;
            } else {
                compressed += to_string(count) + piece;
            }

            count = 1;
            piece = s.substr(j, i);
        }

        if(count == 1) {
            compressed += piece;
        } else {
            compressed += to_string(count) + piece;
        }

        if(compressed.size() < answer) {
            answer = compressed.size();
        }
    }

    return answer;
}

int main() {
    string s;
    cin >> s;

    cout << solution(s) << endl;

    return 0;
}
