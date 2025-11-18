   #include "futbol.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void readMatchesFromCSV(SoccerDB& db) {
    string filename = "new_matches.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        string id, home, away, date, hour, league, homeScore, awayScore;
        getline(ss, id, ',');
        getline(ss, home, ',');
        getline(ss, away, ',');
        getline(ss, date, ',');
        getline(ss, hour, ',');
        getline(ss, league, ',');
        getline(ss, homeScore, ',');
        getline(ss, awayScore, ',');
        int hs = homeScore.empty() ? -1 : atoi(homeScore.c_str());
        int as = awayScore.empty() ? -1 : atoi(awayScore.c_str());
        int mid = atoi(id.c_str());
        if (mid <= 0) continue; // skip invalid line
        Team homeTeam(home);
        Team awayTeam(away);
        Match match(mid, homeTeam, awayTeam, date, hour, league, hs, as);
        db.addMatch(match);
    }
    file.close();
    cout << "Matches loaded from " << filename << endl;
}

int main() {
    SoccerDB db;

    // Cargar partidos del CSV
    readMatchesFromCSV(db);

    //Mostrar los partidos
    cout << "Partidos:" << endl;
    for (const auto& m : db.getMatches()) {
        cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << endl;
    }

    //Busqueda
    int choice;
    string searchValue;
    vector<Match> results;

    while (true) {
        cout << "\nOpciones:" << endl;
        cout << "1. Buscar por Equipo" << endl;
        cout << "2. Buscar por Fecha" << endl;
        cout << "3. Buscar por Hora" << endl;
        cout << "4. Separar partidos en local y visitante" << endl;
        cout << "5. Predecir ganador de un partido" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese opcion (1-6): ";
        cin >> choice;

        if (choice == 1) {
            cout << "Ingrese nombre del equipo: ";
            cin.ignore();
            getline(cin, searchValue);
            results = db.searchByTeam(searchValue);
            sort(results.begin(), results.end(), [](const Match& a, const Match& b) {
                return a.date < b.date;
            });
            cout << "Resultados de busqueda:" << endl;
            for (const auto& m : results) {
                cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << endl;
            }
        } else if (choice == 2) {
            db.sortByDate();
            cout << "Partidos ordenados por fecha:" << endl;
            for (const auto& m : db.getMatches()) {
                cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << endl;
            }
        } else if (choice == 3) {
            db.sortByHour();
            cout << "Partidos ordenados por hora:" << endl;
            for (const auto& m : db.getMatches()) {
                cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << endl;
            }
        } else if (choice == 4) {
            if (results.empty()) {
                cout << "Primero debe buscar por equipo (opcion 1) para separar en local y visitante." << endl;
            } else {
                vector<Match> homeMatches;
                vector<Match> awayMatches;
                string lowerSearch = searchValue;
                transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), [](unsigned char c){ return tolower(c); });
                for (const auto& m : results) {
                    string lowerHome = m.home.name;
                    transform(lowerHome.begin(), lowerHome.end(), lowerHome.begin(), [](unsigned char c){ return tolower(c); });
                    string lowerAway = m.away.name;
                    transform(lowerAway.begin(), lowerAway.end(), lowerAway.begin(), [](unsigned char c){ return tolower(c); });
                    if (lowerHome == lowerSearch) {
                        homeMatches.push_back(m);
                    } else if (lowerAway == lowerSearch) {
                        awayMatches.push_back(m);
                    }
                }
                cout << "Partidos como local:" << endl;
                for (const auto& m : homeMatches) {
                    cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << endl;
                }
                cout << "Partidos como visitante:" << endl;
                for (const auto& m : awayMatches) {
                    cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << endl;
                 }
            }
        //predicion de partidos 
        } else if (choice == 5) {
            cout << "Ingrese ID del partido a predecir: ";
            int matchId;
            cin >> matchId;
            auto matches = db.getMatches();
            auto it = find_if(matches.begin(), matches.end(), [matchId](const Match& m) { return m.id == matchId; });
            if (it != matches.end()) {
                const Match& match = *it;
                string lowerHome = match.home.name;
                transform(lowerHome.begin(), lowerHome.end(), lowerHome.begin(), ::tolower);
                vector<Match> homeTeamMatches = db.searchByTeam(lowerHome);
                sort(homeTeamMatches.begin(), homeTeamMatches.end(), [](const Match& a, const Match& b) { return a.date < b.date; });
                vector<Match> homeLast5;
                for (auto mit = homeTeamMatches.rbegin(); mit != homeTeamMatches.rend() && homeLast5.size() < 5; ++mit) {
                    if (mit->date < match.date) homeLast5.push_back(*mit);
                }
                string lowerAway = match.away.name;
                transform(lowerAway.begin(), lowerAway.end(), lowerAway.begin(), ::tolower);
                vector<Match> awayTeamMatches = db.searchByTeam(lowerAway);
                sort(awayTeamMatches.begin(), awayTeamMatches.end(), [](const Match& a, const Match& b) { return a.date < b.date; });
                vector<Match> awayLast5;
                for (auto mit = awayTeamMatches.rbegin(); mit != awayTeamMatches.rend() && awayLast5.size() < 5; ++mit) {
                    if (mit->date < match.date) awayLast5.push_back(*mit);
                }
                Predictor predictor;
                string prediction = predictor.predictWinner(match, homeLast5, awayLast5);
                cout << "Prediccion para " << match.home.name << " vs " << match.away.name << ": " << prediction << endl;
            } else {
                cout << "Partido no encontrado." << endl;
            }
        } else if (choice == 6) {
            break;
        } else {
            cout << "Opcion invalida. Desea volver al menu (1) o salir (2)? ";
            int subChoice;
            cin >> subChoice;
            if (subChoice == 2) {
                break;
            } else {
                continue;
            }
        }

        if ((choice == 1 || choice == 4) && results.empty()) {
            cout << "No se encontraron partidos." << endl;
        }
    }

    return 0;
}
