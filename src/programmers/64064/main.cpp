#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <limits.h>

using namespace std;

bool filterBanned(const string &userId, const string &bannedId);
bool compareSets(const unordered_set<string> &a, const unordered_set<string> &b);

class DFS {
public:
    vector<unordered_set<string>> visitList;
    vector<vector<string>> bannedList;

    DFS(vector<vector<string>> bannedList): bannedList(bannedList) {}

    void travel(int index, unordered_set<string> visit) {
        if(index == bannedList.size()) {
            if(visit.size() != this->bannedList.size()) {
                return;
            }

            for(int i = 0; i < this->visitList.size(); i++) {
                if(compareSets(visit, this->visitList[i])) {
                    return;
                }
            }

            this->visitList.push_back(visit);

            return;
        }

        for(int i = 0; i < this->bannedList[index].size(); i++) {
            if(visit.find(this->bannedList[index][i]) != visit.end()) {
                continue;
            }
            unordered_set<string> nextVisit = visit;
            nextVisit.insert(this->bannedList[index][i]);
            travel(index + 1, nextVisit);
        }
    }
};

bool compareSets(const unordered_set<string> &a, const unordered_set<string> &b) {
    if(a.size() != b.size()) {
        return false;
    }

    for(auto itr = a.begin(); itr != a.end(); itr++) {
        if(b.find(*itr) == b.end()) {
            return false;
        }
    }

    return true;
}

bool filterBanned(const string &userId, const string &bannedId) {
    if(userId.size() != bannedId.size()) {
        return false;
    }

    for(int i = 0; i < bannedId.size(); i++) {
        if(bannedId[i] == '*') {
            continue;
        }

        if(userId[i] != bannedId[i]) {
            return false;
        }
    }

    return true;
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    vector<vector<string>> bannedList(banned_id.size(), vector<string>());
    unordered_set<string> visit;

    for(int i = 0; i < banned_id.size(); i++) {
        for(int j = 0; j < user_id.size(); j++) {
            if(filterBanned(user_id[j], banned_id[i])) {
                bannedList[i].push_back(user_id[j]);
            }
        }
    }

    DFS dfs(bannedList);
    dfs.travel(0, unordered_set<string>());

    return dfs.visitList.size();
}