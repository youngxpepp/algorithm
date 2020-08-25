#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Stage {
public:
    int stageNumber;
    int passCount = 0;
    int failCount = 0;

    Stage(int stageNumber) {
        this->stageNumber = stageNumber;
    }

    double getFailureRate() const {
        if(passCount + failCount == 0) {
            return 0;
        }

        return (double) failCount / (passCount + failCount);
    }
};

struct StageComparator {
    bool operator()(const Stage &a, const Stage &b) const {
        if(a.getFailureRate() == b.getFailureRate()) {
            return a.stageNumber < b.stageNumber;
        }
        return a.getFailureRate() > b.getFailureRate();
    }
};

vector<int> solution(int N, vector<int> stages) {
    vector<Stage> stageVector;

    for(int i = 1; i <= N; i++) {
        stageVector.push_back(Stage(i));
    }

    for(const int stageNumber : stages) {
        for(int i = 0; i < stageNumber - 1; i++) {
            stageVector[i].passCount++;
        }
        if(stageNumber == N + 1) {
            continue;
        }
        stageVector[stageNumber - 1].failCount++;
    }

    sort(stageVector.begin(), stageVector.end(), StageComparator());

    vector<int> answer;

    for(const auto &element : stageVector) {
        answer.push_back(element.stageNumber);
    }

    return answer;
}