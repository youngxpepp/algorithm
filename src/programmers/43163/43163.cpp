#include <string>
#include <vector>

using namespace std;

int SIZE = 0;
int ANSWER = 51;
string TARGET;
vector<string> WORDS;
vector<string> WORD_PATH;
vector<bool> VISIT;

void dfs() {
    if(WORD_PATH.back() == TARGET) {
        int num = WORD_PATH.size() - 1;
        if(num < ANSWER) {
            ANSWER = num;
        }

        return;
    }

    for(int i = 0; i < SIZE; i++) {
        if(VISIT[i]) {
            continue;
        }

        int howManyDifferent = 0;
        for(int j = 0; j < WORD_PATH.back().size(); j++) {
            if(howManyDifferent > 1) {
                break;
            }

            if(WORD_PATH.back()[j] != WORDS[i][j]) {
                howManyDifferent++;
            }
        }

        if(howManyDifferent == 1) {
            WORD_PATH.push_back(WORDS[i]);
            VISIT[i] = true;
            dfs();
            VISIT[i] = false;
            WORD_PATH.pop_back();
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    TARGET = target;

    SIZE = words.size();
    WORDS.assign(words.begin(), words.end());
    VISIT.assign(words.size(), false);

    WORD_PATH.push_back(begin);
    dfs();

    return ANSWER == 51 ? 0 : ANSWER;
}