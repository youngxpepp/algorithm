#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

bool isSubset(set<int> &a, set<int> &b) {
    for(auto itr = a.begin(); itr != a.end(); itr++) {
        if(b.find(*itr) == b.end()) {
            return false;
        }
    }

    return true;
}

class Bfs {

public:
    vector<vector<string>> table;

    Bfs(vector<vector<string>> table) {
        this->table = table;
    }

    bool isUnique(const set<int> &candidateKey) const {
        if(candidateKey.size() == 0) {
            return false;
        }

        set<string> uniqueSet;

        for(int i = 0; i < this->table.size(); i++) {
            string keyString = "";
            for(auto itr = candidateKey.begin(); itr != candidateKey.end(); itr++) {
                keyString += this->table[i][*itr];
            }
            uniqueSet.insert(keyString);
        }

        if(uniqueSet.size() == this->table.size()) {
            return true;
        }

        return false;
    }

    int travel() {
        int answer = 0;

        vector<set<int>> candidateKeys;
        queue<set<int>> bfsQueue;
        bfsQueue.push(set<int>());

        while(!bfsQueue.empty()) {
            set<int> nowSet = bfsQueue.front();
            bfsQueue.pop();

            bool subsetRelation = false;
            for(int j = 0; j < candidateKeys.size(); j++) {
                if(isSubset(nowSet, candidateKeys[j]) || isSubset(candidateKeys[j], nowSet)) {
                    subsetRelation = true;
                    continue;
                }
            }
            if(subsetRelation) {
                continue;
            }

            if(this->isUnique(nowSet)) {
                candidateKeys.push_back(nowSet);
                answer++;
                continue;
            }

            if(nowSet.size() == this->table[0].size()) {
                continue;
            }

            for(int i = 0; i < this->table[0].size(); i++) {
                if(nowSet.find(i) != nowSet.end()) {
                    continue;
                }

                set<int> copiedSet = nowSet;
                copiedSet.insert(i);
                bfsQueue.push(copiedSet);
            }
        }

        return answer;
    }
};

int solution(vector<vector<string>> relation) {
    Bfs bfs(relation);

    return bfs.travel();
}