#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Meeting {
public:
    int beginTime;
    int endTime;

    Meeting(int beginTime, int endTime): beginTime(beginTime), endTime(endTime) {}

    int getTime() const {
        return (this->endTime - this->beginTime);
    }

    bool operator<(const Meeting &target) const {
        if(this->endTime == target.endTime) {
            return this->beginTime <= target.beginTime;
        }

        return this->endTime <= target.endTime;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    vector<Meeting> meetings;

    for(int i = 0; i < n; i++) {
        int beginTime = 0, endTime = 0;
        cin >> beginTime >> endTime;
        meetings.emplace_back(beginTime, endTime);
    }

    sort(meetings.begin(), meetings.end());

    int count = 1;
    int index = 0;
    for(int i = 1; i < meetings.size(); i++) {
        if(meetings[i].beginTime < meetings[index].endTime) {
            continue;
        }

        index = i;
        count++;
    }

    cout << count;

    return 0;
}
