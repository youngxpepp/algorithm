#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

class TrieNode {
public:
    bool terminal = false;
    bool word = false;
    vector<TrieNode*> children;
    map<int, int> wordLengthMap;

    TrieNode() {
        children.assign(26, nullptr);
    }

    ~TrieNode() {
        for(const auto &child : children) {
            delete child;
        }
    }

    int getChildrenCount() {
        int count = 0;
        for(const auto &child : children) {
            if(child != nullptr) {
                count++;
            }
        }

        return count;
    }
};

class TrieTree {
public:
    TrieNode *head;

    TrieTree() {
        head = new TrieNode();
    }

    ~TrieTree() {
        delete head;
    }

    void insertNode(string word) {
        const auto wordLengthMapItr = this->head->wordLengthMap.find(word.size());
        if(wordLengthMapItr == this->head->wordLengthMap.end()) {
            this->head->wordLengthMap[word.size()] = 1;
        } else {
            this->head->wordLengthMap[word.size()]++;
        }

        TrieNode *now = this->head;

        for(int i = 0; i < word.size(); i++) {
            const int index = word[i] - 'a';

            if(now->children[index] == nullptr) {
                now->children[index] = new TrieNode();

                if(i == word.size() - 1) {
                    now->children[index]->terminal = true;
                }
            }

            now = now->children[index];

            const auto itr = now->wordLengthMap.find(word.size());
            if(itr == now->wordLengthMap.end()) {
                now->wordLengthMap[word.size()] = 1;
            } else {
                now->wordLengthMap[word.size()]++;
            }

            if(i == word.size() - 1) {
                now->word = true;
            }
        }
    }

    TrieNode* findNode(string word) {
        TrieNode *now = this->head;

        for(int i = 0; i < word.size(); i++) {
            const int index = word[i] - 'a';

            if(now->children[index] == nullptr) {
                return nullptr;
            }

            now = now->children[index];
        }

        return now;
    }
};

vector<int> solution(vector<string> words, vector<string> queries) {
    set<string> wordSet;
    map<string, int> queryMap;
    TrieTree trieTree;
    TrieTree reversedTrieTree;

    for(const auto word : words) {
        wordSet.insert(word);
    }

    for(const auto word : wordSet) {
        string reversedWord = word;
        reverse(reversedWord.begin(), reversedWord.end());

        trieTree.insertNode(word);
        reversedTrieTree.insertNode(reversedWord);
    }

    vector<int> answer;
    for(const auto query : queries) {
        const auto queryMapItr = queryMap.find(query);
        if(queryMapItr != queryMap.end()) {
            answer.push_back(queryMapItr->second);
            continue;
        }

        int matchCount = 0;
        if(query.front() == '?' && query.back() == '?') {
            const auto wordLengthMapItr = trieTree.head->wordLengthMap.find(query.size());
            if(wordLengthMapItr != trieTree.head->wordLengthMap.end()) {
                matchCount = wordLengthMapItr->second;
            }
        } else if(query.front() == '?') {
            const int index = query.find_last_of('?') + 1;
            string reversedQuery = query.substr(index);
            reverse(reversedQuery.begin(), reversedQuery.end());

            const TrieNode *node = reversedTrieTree.findNode(reversedQuery);
            if(node != nullptr) {
                const auto wordLengthMapItr = node->wordLengthMap.find(query.size());
                if(wordLengthMapItr != node->wordLengthMap.end()) {
                    matchCount = wordLengthMapItr->second;
                }
            }
        } else if(query.back() == '?') {
            const int index = query.find_first_of('?');
            string targetQuery = query.substr(0, index);

            const TrieNode *node = trieTree.findNode(targetQuery);
            if(node != nullptr) {
                const auto wordLengthMapItr = node->wordLengthMap.find(query.size());
                if(wordLengthMapItr != node->wordLengthMap.end()) {
                    matchCount = wordLengthMapItr->second;
                }
            }
        }

        queryMap.insert(make_pair(query, matchCount));
        answer.push_back(matchCount);
    }

    return answer;
}

int main() {

    return 0;
}