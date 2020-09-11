#include <iostream>
#include <vector>
#include <set>

class Student {
public:
    int beginNumber;
    int endNumber;

    Student(int beginNumber, int endNumber): beginNumber(beginNumber), endNumber(endNumber) {}

    bool operator<(const Student &b) const {
        if(this->endNumber == b.endNumber) {
            return this->beginNumber <= b.beginNumber;
        }

        return this->endNumber < b.endNumber;
    }
};

using namespace std;

int main() {
    int t = 0;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int n = 0, m = 0, answer = 0;
        cin >> n >> m;

        vector<int> books(n, false);
        set<Student> studentSet;

        for(int j = 0; j < m; j++) {
            int beginNumber = 0, endNumber = 0;
            cin >> beginNumber >> endNumber;
            studentSet.insert(Student(beginNumber - 1, endNumber - 1));
        }

        for(auto itr = studentSet.begin(); itr != studentSet.end(); itr++) {
            for(int j = itr->beginNumber; j <= itr->endNumber; j++) {
                if(!books[j]) {
                    books[j] = true;
                    answer++;
                    break;
                }
            }
        }

        cout << answer << "\n";
    }

    return 0;
}
