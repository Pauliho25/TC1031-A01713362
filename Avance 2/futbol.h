#ifndef Futbol_H_
#define Futbol_H_

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

struct Team {
    std::string name;
    Team(std::string n) : name(n) {}
};

struct Match {
    int id;
    Team home;
    Team away;
    std::string date;
    std::string hour;
    std::string league;
    Match(int i, Team h, Team a, std::string dt, std::string hr, std::string lg) : id(i), home(h), away(a), date(dt), hour(hr), league(lg) {}
};

class SoccerDB {
private:
    std::vector<Match> matches;
    std::unordered_map<std::string, std::vector<Match>> teamMatches;
    std::unordered_map<std::string, std::vector<Match>> leagueMatches;
    std::unordered_map<std::string, std::vector<Match>> dateMatches;
    std::unordered_map<std::string, std::vector<Match>> hourMatches;
public:
    void addMatch(const Match& m) {
        matches.push_back(m);
        teamMatches[m.home.name].push_back(m);
        teamMatches[m.away.name].push_back(m);
        leagueMatches[m.league].push_back(m);
        dateMatches[m.date].push_back(m);
        hourMatches[m.hour].push_back(m);
    }

    std::vector<Match> getMatches() const {
        return matches;
    }

    std::vector<Match> searchByTeam(const std::string& teamName) {
        auto it = teamMatches.find(teamName);
        if (it != teamMatches.end()) {
            return it->second;
        }
        return {};
    }

    std::vector<Match> searchByHour(const std::string& hour) {
        auto it = hourMatches.find(hour);
        if (it != hourMatches.end()) {
            return it->second;
        }
        return {};
    }

    std::vector<Match> searchByLeague(const std::string& league) {
        auto it = leagueMatches.find(league);
        if (it != leagueMatches.end()) {
            return it->second;
        }
        return {};
    }

    std::vector<Match> searchByDate(const std::string& date) {
        auto it = dateMatches.find(date);
        if (it != dateMatches.end()) {
            return it->second;
        }
        return {};
    }

    void sortByHour() {
        std::sort(matches.begin(), matches.end());
    }

    void sortByDate() {
        std::sort(matches.begin(), matches.end(), [](const Match& a, const Match& b) {
            return a.date < b.date;
        });
    }
};

bool operator<(const Match& a, const Match& b) {
    return a.hour < b.hour;
}

#endif 
