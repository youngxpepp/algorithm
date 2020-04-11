#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<pair<int, int> > trucksOnBridge;
    int nextTruckIndex = 0;
    int totalWeight = 0;
    int time = 0;

    do {
        if(!trucksOnBridge.empty() && time - trucksOnBridge.front().second >= bridge_length) {
            totalWeight -= trucksOnBridge.front().first;
            trucksOnBridge.pop();
        }

        if(nextTruckIndex < truck_weights.size() && totalWeight + truck_weights[nextTruckIndex] <= weight) {
            trucksOnBridge.push(make_pair(truck_weights[nextTruckIndex], time));
            totalWeight += truck_weights[nextTruckIndex];
            nextTruckIndex++;
        }

        cout << "다리를 지나는 트럭: " << trucksOnBridge.front().first << " 다리에 진입한 시간: " << trucksOnBridge.front().second << " 현재 시간: " << time << endl;
        time++;
    } while(!trucksOnBridge.empty());

    return time;
}