#ifndef Futbol_H_
#define Futbol_H_

#include <vector>
#include <string>
#include <algorithm>

struct Team {
    std::string name;
    Team(std::string n) : name(n) {}
};

struct Match {
    Team home;
    Team away;
    std::string date;  
    std::string hour;  
    std::string league;
    Match(Team h, Team a, std::string dt, std::string hr, std::string lg) : home(h), away(a), date(dt), hour(hr), league(lg) {}
};

class SoccerDB {
private:
    std::vector<Match> matches;
public:
    void addMatch(const Match& m) {
        matches.push_back(m);
    }

    std::vector<Match> getMatches() const {
        return matches;
    }

    std::vector<Match> searchByTeam(const std::string& teamName) {
        std::vector<Match> result;
        for (const auto& match : matches) {
            if (match.home.name == teamName || match.away.name == teamName) {
                result.push_back(match);
            }
        }
        return result;
    }

    std::vector<Match> searchByHour(const std::string& hour) {
        std::vector<Match> result;
        for (const auto& match : matches) {
            if (match.hour == hour) {
                result.push_back(match);
            }
        }
        return result;
    }

    std::vector<Match> searchByLeague(const std::string& league) {
        std::vector<Match> result;
        for (const auto& match : matches) {
            if (match.league == league) {
                result.push_back(match);
            }
        }
        return result;
    }

    std::vector<Match> searchByDate(const std::string& date) {
        std::vector<Match> result;
        for (const auto& match : matches) {
            if (match.date == date) {
                result.push_back(match);
            }
        }
        return result;
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
