#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    
    if(phone_book.size() == 1) {
        return true;
    }
    
    map<string, string> mapPhoneBook;
    for(const auto element : phone_book) {
        int moreSize = 20 - element.length();
        string phoneNumFillZero = element;
        for(int i = 0; i < moreSize; i++) {
            phoneNumFillZero += "0";
        }

        mapPhoneBook.insert(make_pair(phoneNumFillZero, element));
    }

    for(auto itr = mapPhoneBook.begin(); itr != mapPhoneBook.end(); ++itr) {
        auto nextItr = itr;
        if(++nextItr == mapPhoneBook.end()) {
            break;
        }

        bool prefix = true;
        for(int i = 0; i < itr->second.size(); i++) {
            if(itr->second[i] != nextItr->second[i]) {
                prefix = false;
                break;
            }
        }

        if(prefix) {
            answer = false;
            break;
        }
    }
    
    
    return answer;
}