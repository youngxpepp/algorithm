#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string LEFT = "left";
const string RIGHT = "right";
const vector<pair<int, int>> keypad = {{1, 0}, {0, 3}, {1, 3}, {2, 3}, {0, 2}, {1, 2}, {2, 2}, {0, 1}, {1, 1}, {2, 1}};

string solution(vector<int> numbers, string hand) {
    pair<int, int> leftHand{0, 0};
    pair<int, int> rightHand{2, 0};

    string answer = "";

    for(const auto number : numbers) {
        switch(number) {
            case 1:
            case 4:
            case 7:
                leftHand.first = keypad[number].first;
                leftHand.second = keypad[number].second;
                answer += 'L';
                break;
            case 3:
            case 6:
            case 9:
                rightHand.first = keypad[number].first;
                rightHand.second = keypad[number].second;
                answer += 'R';
                break;
            default:
                const int leftDistance = abs(leftHand.first - keypad[number].first) + abs(leftHand.second - keypad[number].second);
                const int rightDistance = abs(rightHand.first - keypad[number].first) + abs(rightHand.second - keypad[number].second);
                if(leftDistance == rightDistance) {
                    if(hand == LEFT) {
                        leftHand.first = keypad[number].first;
                        leftHand.second = keypad[number].second;
                        answer += 'L';
                    } else if(hand == RIGHT) {
                        rightHand.first = keypad[number].first;
                        rightHand.second = keypad[number].second;
                        answer += 'R';
                    }
                } else if(leftDistance > rightDistance) {
                    rightHand.first = keypad[number].first;
                    rightHand.second = keypad[number].second;
                    answer += 'R';
                } else if(leftDistance < rightDistance) {
                    leftHand.first = keypad[number].first;
                    leftHand.second = keypad[number].second;
                    answer += 'L';
                }

                break;
        };
    }

    return answer;
}

int main() {

    return 0;
}
