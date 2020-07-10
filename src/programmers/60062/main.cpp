#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

int globalN;
vector<int> globalWeak;
vector<int> globalDist;
vector<vector<int>> permutations;

void dfs(vector<int> p, vector<bool> visit, int count) {
    if(count == 0) {
        permutations.push_back(p);
        return;
    }

    for(int i = 0; i < globalDist.size(); i++) {
        if(visit[i]) {
            continue;
        }
        visit[i] = true;
        p.push_back(globalDist[i]);
        dfs(p, visit, count - 1);
        p.pop_back();
        visit[i] = false;
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    globalN = n;
    globalWeak = weak;
    globalDist = dist;

    for(int i = 0; i < dist.size(); i++) {
        dfs(vector<int>(), vector<bool>(dist.size(), false), i + 1);
    }

    vector<queue<int>> weaks;
    queue<int> weakQ;
    for(int element : weak) {
        weakQ.push(element);
    }
    weaks.push_back(weakQ);

    for(int i = 0; i < weakQ.size() - 1; i++) {
        weakQ.push(weakQ.front() + n);
        weakQ.pop();
        weaks.push_back(weakQ);
    }

    for(const auto& p : permutations) {
        for(int i = 0; i < weaks.size(); i++) {
            queue<int> q = weaks[i];
            int distIndex = 0;
            int remain = p[distIndex];
            int position = q.front();

            while(distIndex < p.size() && !q.empty()) {
                if(position == (q.front() % n)) {
                    q.pop();
                }

                position = (position + 1) % n;
                remain--;

                if(remain == -1) {
                    distIndex++;
                    if(distIndex < p.size()) {
                        remain = p[distIndex];
                    }
                    position = q.front();
                }
            }

            if(q.empty()) {
                return p.size();
            }
        }
    }

    return -1;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
