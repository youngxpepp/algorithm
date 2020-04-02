#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int bfs(int conyPosition, int brownPosition)
{
    vector<bool> visit(200001, false);
    queue<pair<int, int> > bfsQueue;
    bfsQueue.push(make_pair(brownPosition, 0));

    while (!bfsQueue.empty())
    {
        int nowPosition = bfsQueue.front().first;
        int nowTime = bfsQueue.front().second + 1;
        bfsQueue.pop();

        int leftPosition = nowPosition - 1;
        if (leftPosition <= 200000 && leftPosition >= 0 && !visit[leftPosition])
        {
            bfsQueue.push(make_pair(leftPosition, nowTime));
            visit[leftPosition] = true;
        }

        int rightPosition = nowPosition + 1;
        if (rightPosition <= 200000 && rightPosition >= 0 && !visit[rightPosition])
        {
            bfsQueue.push(make_pair(rightPosition, nowTime));
            visit[rightPosition] = true;
        }

        int doublePosition = nowPosition * 2;
        if (doublePosition <= 200000 && doublePosition >= 0 && !visit[doublePosition])
        {
            bfsQueue.push(make_pair(doublePosition, nowTime));
            visit[doublePosition] = true;
        }

        int newConyPosition = conyPosition + (nowTime * (nowTime + 1) / 2);
        if(newConyPosition > 200000) {
            return -1;
        } else if (visit[newConyPosition])
        {
            return nowTime;
        }
    }

    return -1;
}

int main()
{
    int cony, brown;
    cin >> cony >> brown;
    cout << bfs(cony, brown) << endl;

    return 0;
}
