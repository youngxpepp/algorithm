#include <iostream>
#include <vector>

using namespace std;

int answer = 0;
vector<vector<bool>> bakery;
vector<vector<int>> visit;
vector<bool> finished;
const vector<pair<int, int>> directions{{1, -1}, {1, 0}, {1, 1}};

void dfs(pair<int, int> position, int startNumber) {
    if(position.first == bakery.front().size() - 1) {
        finished[startNumber] = true;
        answer++;
        return;
    }

    for(int i = 0; i < directions.size(); i++) {
        pair<int, int> nextPosition = position;
        nextPosition.first += directions[i].first;
        nextPosition.second += directions[i].second;

        if(finished[startNumber]) {
            return;
        }

        if(nextPosition.first < 0 || nextPosition.first >= bakery.front().size() ||
        nextPosition.second < 0 || nextPosition.second >= bakery.size()) {
            continue;
        }

        if(!bakery[nextPosition.second][nextPosition.first]) {
            continue;
        }

        if(visit[nextPosition.second][nextPosition.first] > -1) {
            continue;
        }

        visit[nextPosition.second][nextPosition.first] = startNumber;
        dfs(nextPosition, startNumber);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r = 0, c = 0;
    cin >> r >> c;

    bakery.assign(r, vector<bool>(c, false));
    visit.assign(r, vector<int>(c, -1));
    finished.assign(r, false);

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            char input = ' ';
            cin >> input;
            if(input == '.') {
                bakery[i][j] = true;
            }
        }
    }

    for(int i = 0; i < bakery.size(); i++) {
        visit[i][0] = i;
        dfs({0, i}, i);
    }

    cout << answer;

//    for(int i = 0; i < c; i++) {
//        for(int j = 0; j < r; j++) {
//            cout << visit[i][j] << "   ";
//        }
//        cout << "\n";
//    }

    return 0;
}
