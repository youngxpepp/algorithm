#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

struct Job {
    int requestedAt = 0;
    int throughput = 0;

    bool operator>(const Job& a) const {
        if(this->throughput == a.throughput) {
            return this->requestedAt > a.requestedAt;
        }
        return this->throughput > a.throughput;
    }

    Job(int _requestedAt, int _throughput): requestedAt(_requestedAt), throughput(_throughput) {}
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int maxTime = 0;

    vector<pair<int, int> > sortedJobs;
    for(const auto& element : jobs) {
        maxTime += element[1];
        sortedJobs.push_back(make_pair(element[0], element[1]));
    }
    sort(sortedJobs.begin(), sortedJobs.end());

    int busy = 0;
    int time = 0;
    int startIndex = 0;
    priority_queue<Job, vector<Job>, greater<Job> > q;
    while(time <= maxTime) {
        if(startIndex < sortedJobs.size()) {
            for(int i = startIndex; i < sortedJobs.size(); i++) {
                if(sortedJobs[i].first == time) {
                    q.push(Job(sortedJobs[i].first, sortedJobs[i].second));
                    startIndex = i + 1;
                }
            }
        }

        if(time < busy || q.empty()) {
            time++;
            continue;
        }

        answer += time + q.top().throughput - q.top().requestedAt;
        busy = time + q.top().throughput;
        q.pop();
        
        time++;
    }

    answer /= jobs.size();

    return answer;
}