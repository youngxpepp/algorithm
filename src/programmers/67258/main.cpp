#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class ShowTable {
public:
    int beginIndex;
    int endIndex;

    ShowTable(int beginIndex, int endIndex): beginIndex(beginIndex), endIndex(endIndex) {}

    int getLength() const {
        return this->endIndex - this->beginIndex + 1;
    }

    bool operator<(const ShowTable &operand) {
        if(this->getLength() == operand.getLength()) {
            return this->beginIndex < operand.beginIndex;
        }

        return this->getLength() < operand.getLength();
    }
};

vector<int> solution(vector<string> gems) {
    vector<ShowTable> showTables;
    unordered_set<string> twoPointerSet;
    unordered_map<string, int> twoPointerMap;

    for(const auto &gem : gems) {
        twoPointerSet.insert(gem);
    }

    int endIndex = 0;
    ShowTable showTable(100000, 200000);

    for(int i = 0; i < gems.size(); i++) {
        while(endIndex < gems.size() && twoPointerMap.size() < twoPointerSet.size()) {
            twoPointerMap[gems[endIndex]]++;
            endIndex++;
        }

        if(twoPointerMap.size() == twoPointerSet.size()) {
            ShowTable operandShowTable(i, endIndex - 1);

            if(operandShowTable < showTable) {
                showTable = operandShowTable;
            }

            if(i == endIndex) {
                break;
            }
        }

        twoPointerMap[gems[i]]--;
        if(twoPointerMap[gems[i]] == 0) {
            twoPointerMap.erase(gems[i]);
        }
    }

    return {showTable.beginIndex + 1, showTable.endIndex + 1};
}
