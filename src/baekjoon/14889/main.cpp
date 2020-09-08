#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void dfs(vector<int> players, vector<vector<int>> &scores, vector<bool> &visit, int &minScore) {
    if(players.size() == scores.size() / 2) {
        int aScore = 0;
        int bScore = 0;

        vector<int> aTeam;
        vector<int> bTeam;

        for(int i = 0; i < visit.size(); i++) {
            if(visit[i]) {
                aTeam.push_back(i);
            } else {
                bTeam.push_back(i);
            }
        }

        for(int i = 0; i < visit.size() / 2; i++) {
            for(int j = 0; j < visit.size() / 2; j++) {
                if(i == j) {
                    continue;
                }

                aScore += scores[aTeam[i]][aTeam[j]];
                bScore += scores[bTeam[i]][bTeam[j]];
            }
        }

        minScore = min(minScore, abs(aScore - bScore));
    }

    int beginIndex = 0;
    if(players.empty()) {
        beginIndex = 0;
    } else {
        beginIndex = players.back();
    }

    for(int i = beginIndex; i < scores.size(); i++) {
        if(visit[i]) {
            continue;
        }

        vector<int> nextPlayers = players;
        nextPlayers.push_back(i);

        visit[i] = true;
        dfs(nextPlayers, scores, visit, minScore);
        visit[i] = false;
    }
}

int getScoreDifference(vector<int> &playerSet, vector<vector<int>> &scores) {
    int n = scores.size() - 1;
    int aScore = 0;
    int bScore = 0;
    for(int i = 0; i < playerSet.size(); i++) {
        for(int j = 0; j < playerSet.size(); j++) {
            if(i == j) {
                continue;
            }

            aScore += scores[playerSet[i]][playerSet[j]];
            bScore += scores[n - playerSet[i]][n - playerSet[j]];
        }
    }

    return abs(aScore - bScore);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    vector<vector<int>> scores(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> scores[i][j];
        }
    }

    vector<bool> visit(n, false);
    int minScore = INT_MAX;

    dfs({}, scores, visit, minScore);

    cout << minScore << "\n";

    return 0;
}
