#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

bool queryWords(const string &word, const string &query) {
    if(word.size() != query.size()) {
        return false;
    }

    if(query.front() == '?' && query.back() == '?') {
        return true;
    } else if(query.front() == '?') {
        const int lastIndex = query.find_last_of('?');

        for(int i = lastIndex + 1; i < word.size(); i++) {
            if(word[i] != query[i]) {
                return false;
            }
        }
        return true;
    } else if(query.back() == '?') {
        const int firstIndex = query.find_first_of('?');

        for(int i = 0; i < firstIndex; i++) {
            if(word[i] != query[i]) {
                return false;
            }
        }

        return true;
    }

    return false;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    map<string, int> queryMap;

    for(int i = 0; i < queries.size(); i++) {
        if(queryMap.find(queries[i]) != queryMap.end()) {
            continue;
        }

        const auto itr = queryMap.insert(make_pair(queries[i], 0)).first;

        for(int j = 0; j < words.size(); j++) {
            if(queryWords(words[j], queries[i])) {
                itr->second++;
            }
        }
    }

    vector<int> answer;

    for(int i = 0; i < queries.size(); i++) {
        const auto targetQuery = queryMap.find(queries[i]);
        answer.push_back(targetQuery->second);
    }

    return answer;
}

int main() {

    return 0;
}