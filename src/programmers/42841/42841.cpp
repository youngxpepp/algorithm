#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int> > baseball) {
    int answer = 0;

    for(int i = 100; i < 1000; i++) {
        vector<int> numbers;
        // 1의 자리
        numbers.push_back(i % 10);
        // 10의 자리
        numbers.push_back((i % 100) / 10);
        // 100의 자리
        numbers.push_back(i / 100);

        bool containsZero = false;
        bool duplicate = false;
        for(int j = 0; j < numbers.size(); j++) {
            if(numbers[j] == 0) {
                containsZero = true;
            }
            for(int k = 0; k < numbers.size(); k++) {
                if(j != k && numbers[j] == numbers[k]) {
                    duplicate = true;
                }
            }
        }

        if(containsZero || duplicate) {
            continue;
        }

        bool correct = true;
        for(const auto& game : baseball) {
            int gameNumber = game[0];
            int strikes = game[1];
            int balls = game[2];

            vector<int> gameNumbers;
            gameNumbers.push_back(gameNumber % 10);
            gameNumbers.push_back((gameNumber % 100) / 10);
            gameNumbers.push_back(gameNumber / 100);

            int _balls = 0;
            int _strikes = 0;
            for(int j = 0; j < gameNumbers.size(); j++) {
                for(int k = 0; k < numbers.size(); k++) {
                    if(gameNumbers[j] == numbers[k]) {
                        if(j == k) {
                            _strikes++;
                        } else {
                            _balls++;
                        }
                        break;
                    }
                }
            }

            if(balls != _balls || strikes != _strikes) {
                correct = false;
                break;
            }
        }

        if(correct) {
            answer++;
        }
    }

    return answer;
}