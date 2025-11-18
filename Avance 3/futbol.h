#ifndef Futbol_H_
#define Futbol_H_

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cctype>

using namespace std;

struct Team {
    string name;
    Team(string n) : name(n) {}
};

struct Match {
    int id;
    Team home;
    Team away;
    string date;
    string hour;
    string league;
    int home_score;
    int away_score;
    Match(int i, Team h, Team a, string dt, string hr, string lg, int hs = -1, int as = -1) : id(i), home(h), away(a), date(dt), hour(hr), league(lg), home_score(hs), away_score(as) {}
};

class SoccerDB {
private:
    vector<Match> matches;
    unordered_map<string, vector<Match>> teamMatches;
    unordered_map<string, vector<Match>> leagueMatches;
    unordered_map<string, vector<Match>> dateMatches;
    unordered_map<string, vector<Match>> hourMatches;
public:
    void addMatch(const Match& m) {
        matches.push_back(m);
        string lowerHome = m.home.name;
        transform(lowerHome.begin(), lowerHome.end(), lowerHome.begin(), [](unsigned char c){ return tolower(c); });
        teamMatches[lowerHome].push_back(m);
        string lowerAway = m.away.name;
        transform(lowerAway.begin(), lowerAway.end(), lowerAway.begin(), [](unsigned char c){ return tolower(c); });
        teamMatches[lowerAway].push_back(m);
        leagueMatches[m.league].push_back(m);
        dateMatches[m.date].push_back(m);
        hourMatches[m.hour].push_back(m);
    }

    vector<Match> getMatches() const {
        return matches;
    }

    vector<Match> searchByTeam(const string& teamName) {
        string lower = teamName;
        transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return tolower(c); });
        auto it = teamMatches.find(lower);
        if (it != teamMatches.end()) {
            return it->second;
        }
        return {};
    }

    vector<Match> searchByHour(const string& hour) {
        auto it = hourMatches.find(hour);
        if (it != hourMatches.end()) {
            return it->second;
        }
        return {};
    }

    vector<Match> searchByLeague(const string& league) {
        auto it = leagueMatches.find(league);
        if (it != leagueMatches.end()) {
            return it->second;
        }
        return {};
    }

    vector<Match> searchByDate(const string& date) {
        auto it = dateMatches.find(date);
        if (it != dateMatches.end()) {
            return it->second;
        }
        return {};
    }

    void sortByHour() {
        sort(matches.begin(), matches.end());
    }

    void sortByDate() {
        sort(matches.begin(), matches.end(), [](const Match& a, const Match& b) {
            return a.date < b.date;
        });
    }
};

bool operator<(const Match& a, const Match& b) {
    return a.hour < b.hour;
}

class Predictor {
public:
    string predictWinner(const Match& match, const vector<Match>& homeLast5, const vector<Match>& awayLast5) {
        double homeStrength = calculateStrength(homeLast5, match.home.name);
        double awayStrength = calculateStrength(awayLast5, match.away.name);
        if (homeStrength > awayStrength) {
            return match.home.name;
        } else if (awayStrength > homeStrength) {
            return match.away.name;
        } else {
            return "Draw";
        }
    }

private:
    double calculateStrength(const vector<Match>& lastMatches, const string& teamName) {
        if (lastMatches.empty()) return 0.5;
        double totalPoints = 0.0;
        for (const auto& m : lastMatches) {
            int teamScore = (m.home.name == teamName) ? m.home_score : m.away_score;
            int oppScore = (m.home.name == teamName) ? m.away_score : m.home_score;
            if (teamScore > oppScore) totalPoints += 3.0;
            else if (teamScore == oppScore) totalPoints += 1.0;
        }
        return totalPoints / (lastMatches.size() * 3.0);
    }
};

#endif
