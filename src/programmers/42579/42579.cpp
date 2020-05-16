#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

struct Song {
    int index;
    int plays;

    Song(int _index, int _plays): index(_index), plays(_plays) {}

    bool operator<(const Song& a) const {
        if(this->plays == a.plays) {
            return this->index < a.index;
        }
        return a.plays < this->plays;
    }
};

struct Genre {
    string name;
    int totalPlays;
    set<Song, less<Song> > songs;

    Genre(string _name, int _totalPlays): name(_name), totalPlays(_totalPlays) {}

    bool operator<(const Genre& a) const {
        return a.totalPlays < this->totalPlays;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    if(genres.size() == 1) {
        return vector<int>(1, 0);
    }
    
    vector<Genre> genreArr;
    map<string, int> genreMap;
    
    for(int i = 0; i < genres.size(); i++) {
        const auto& itr = genreMap.find(genres[i]);
        if(itr != genreMap.end()) {
            genreArr[itr->second].totalPlays += plays[i];
            genreArr[itr->second].songs.insert(Song(i, plays[i]));
        } else {
            Genre genre(genres[i], plays[i]);
            genre.songs.insert(Song(i, plays[i]));
            genreArr.push_back(genre);
            genreMap.insert(make_pair(genres[i], genreArr.size() - 1));
        }
    }

    sort(genreArr.begin(), genreArr.end());

    vector<int> answer;
    for(const auto& element : genreArr) {
        int size = 0;
        for(const auto& song : element.songs) {
            if(size == 2) {
                break;
            }
            answer.push_back(song.index);
            size++;
        }
    }
    
    return answer;
}