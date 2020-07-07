#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

bool answer = false;
vector<vector<vector<bool>>> visit;
vector<vector<int>> globalKey;
vector<vector<int>> globalLock;
vector<vector<vector<int>>> rotations;

class Key {
public:
    int x = 0;
    int y = 0;
    int direction = 0;

    Key(int _x, int _y, int _direction): x(_x), y(_y), direction(_direction) {}
};

vector<vector<int>> turnClockwise(vector<vector<int>> key) {
    vector<vector<int>> returnKey(key.size(), vector<int>(key.size(), 0));

    for(int i = 0; i < key.size(); i++) {
        for(int j = 0; j < key.size(); j++) {
            returnKey[j][key.size() - 1 - i] = key[i][j];
        }
    }

    return returnKey;
}

void setRotations(const vector<vector<int>>& key) {
    rotations[0] = key;
    rotations[1] = turnClockwise(rotations[0]);
    rotations[2] = turnClockwise(rotations[1]);
    rotations[3] = turnClockwise(rotations[2]);
}

bool bfs() {
    queue<Key> bfsQueue;
    bfsQueue.push(Key(0, 0, 0));

    while(!bfsQueue.empty()) {
        Key key = bfsQueue.front();
        int x = key.x;
        int y = key.y;
        int direction = key.direction;

        bfsQueue.pop();

        if(x >= (int)globalLock.size() + 1
        || y >= (int)globalLock.size() + 1
        || x + (int)globalKey.size() - 1 < -1
        || y + (int)globalKey.size() - 1 < -1) {

            continue;
        }

        if(visit[x + globalKey.size()][y + globalKey.size()][direction]) {
            continue;
        }
        visit[x + globalKey.size()][y + globalKey.size()][direction] = true;

        vector<vector<int>> keyArr = rotations[direction];
        vector<vector<int>> lockSizeKey(globalLock.size(), vector<int>(globalLock.size(), 0));
        for(int i = 0; i < lockSizeKey.size(); i++) {
            for(int j = 0; j < lockSizeKey.size(); j++) {
                if(i - y >= 0 && j - x >= 0
                   && i - y < (int)keyArr.size() && j - x < (int)keyArr.size()
                   && keyArr[i - y][j - x] == 1) {
                    lockSizeKey[i][j] = 1;
                }
            }
        }

        bool correct = true;
        for(int i = 0; i < globalLock.size(); i++) {
            for(int j = 0; j < globalLock.size(); j++) {
                if(globalLock[i][j] != lockSizeKey[i][j]) {
                    continue;
                }
                correct = false;
                break;
            }
            if(!correct) {
                break;
            }
        }
        if(correct) {
            return true;
        }


        bfsQueue.push(Key(x - 1, y, direction));
        bfsQueue.push(Key(x + 1, y, direction));
        bfsQueue.push(Key(x, y - 1, direction));
        bfsQueue.push(Key(x, y + 1, direction));
        bfsQueue.push(Key(x, y, (direction + 1) % 4));
        bfsQueue.push(Key(x, y, (direction + 3) % 4));
    }

    return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    globalKey = key;
    globalLock = lock;

    visit.assign(lock.size() * 3, vector<vector<bool>>(lock.size() * 3, vector<bool>(4, false)));

    rotations.assign(4, vector<vector<int>>(key.size(), vector<int>(key.size(), 0)));
    setRotations(key);

    return bfs();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
