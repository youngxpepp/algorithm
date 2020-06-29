#include <string>
#include <vector>

using namespace std;

int num = 0;
int networkCount = 0;
vector<bool> visit;
vector<int> path;
vector<vector<int> > globalComputers;

void dfs() {

    for(int i = 0; i < num; i++) {
        if(path.empty() && !visit[i]) {
            networkCount++;

            visit[i] = true;
            path.push_back(i);
            dfs();
            path.pop_back();
            continue;
        }

        if(visit[i] || i == path.back() || globalComputers[path.back()][i] != 1) {
            continue;
        }

        visit[i] = true;
        path.push_back(i);
        dfs();
        path.pop_back();
    }
}

int solution(int n, vector<vector<int> > computers) {
    num = n;
    visit.assign(n, false);
    globalComputers = computers;

    dfs();

    return networkCount;
}