#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> split(string word, string cut) {
    vector<string> result;
    int findResult;

    do {
        findResult = word.find(cut);
        result.push_back(word.substr(0, findResult));
        word = word.substr(findResult + 1);
    } while(findResult != string::npos);

    return result;
}

vector<string> solution(vector<string> record) {
    vector<pair<string, bool>> log;
    unordered_map<string, string> users;

    for(const auto& command : record) {
        vector<string> splitted = split(command, " ");

        if(splitted[0] == "Enter") {
            log.push_back(make_pair(splitted[1], true));
            const auto itr = users.find(splitted[1]);
            if(itr != users.end()) {
                itr->second = splitted[2];
            }
            users.insert(make_pair(splitted[1], splitted[2]));
        } else if(splitted[0] == "Leave") {
            log.push_back(make_pair(splitted[1], false));
            const auto itr = users.find(splitted[1]);
        } else if(splitted[0] == "Change") {
            const auto itr = users.find(splitted[1]);
            itr->second = splitted[2];
        }
    }

    vector<string> answer;
    for(const auto& element : log) {
        string nickname = users.find(element.first)->second;
        if(element.second) {
            answer.push_back(nickname + "님이 들어왔습니다.");
        } else {
            answer.push_back(nickname + "님이 나갔습니다.");
        }
    }

    return answer;
}
