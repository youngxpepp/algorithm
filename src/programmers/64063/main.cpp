#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_map<long long, long long> roomMap;

long long findRoom(long long roomNumber) {
    if(roomMap.find(roomNumber) == roomMap.end()) {
        roomMap[roomNumber] = roomNumber + 1;
        return roomNumber;
    }
    roomMap[roomNumber] = findRoom(roomMap[roomNumber]);
    return roomMap[roomNumber];
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;

    for(int i = 0; i < room_number.size(); i++) {
        answer.push_back(findRoom(room_number[i]));
    }

    return answer;
}
