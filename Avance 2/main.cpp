#include "futbol.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void readMatchesFromCSV(SoccerDB& db) {
    std::string filename = "../matches.csv";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, home, away, date, hour, league;
        std::getline(ss, id, ',');
        std::getline(ss, home, ',');
        std::getline(ss, away, ',');
        std::getline(ss, date, ',');
        std::getline(ss, hour, ',');
        std::getline(ss, league, ',');
        Team homeTeam(home);
        Team awayTeam(away);
        Match match(std::stoi(id), homeTeam, awayTeam, date, hour, league);
        db.addMatch(match);
    }
    file.close();
    std::cout << "Matches loaded from " << filename << std::endl;
}

int main() {
    SoccerDB db;

    // Load matches from CSV
    readMatchesFromCSV(db);

    //Mostrar los partidos
    std::cout << "Partidos:" << std::endl;
    for (const auto& m : db.getMatches()) {
        std::cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
    }

    //Busqueda
    int choice;
    std::string searchValue;
    std::vector<Match> results;

    while (true) {
        std::cout << "\nOpciones:" << std::endl;
        std::cout << "1. Buscar por Equipo" << std::endl;
        std::cout << "2. Buscar por Fecha" << std::endl;
        std::cout << "3. Buscar por Hora" << std::endl;
        std::cout << "4. Separar partidos en local y visitante" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Ingrese opcion (1-5): ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Ingrese nombre del equipo: ";
            std::cin.ignore();
            std::getline(std::cin, searchValue);
            results = db.searchByTeam(searchValue);
            std::sort(results.begin(), results.end(), [](const Match& a, const Match& b) {
                return a.date < b.date;
            });
            std::cout << "Resultados de busqueda:" << std::endl;
            for (const auto& m : results) {
                std::cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
            }
        } else if (choice == 2) {
            db.sortByDate();
            std::cout << "Partidos ordenados por fecha:" << std::endl;
            for (const auto& m : db.getMatches()) {
                std::cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
            }
        } else if (choice == 3) {
            db.sortByHour();
            std::cout << "Partidos ordenados por hora:" << std::endl;
            for (const auto& m : db.getMatches()) {
                std::cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
            }
        } else if (choice == 4) {
            if (results.empty()) {
                std::cout << "Primero debe buscar por equipo (opcion 1) para separar en local y visitante." << std::endl;
            } else {
                std::vector<Match> homeMatches;
                std::vector<Match> awayMatches;
                for (const auto& m : results) {
                    if (m.home.name == searchValue) {
                        homeMatches.push_back(m);
                    } else if (m.away.name == searchValue) {
                        awayMatches.push_back(m);
                    }
                }
                std::cout << "Partidos como local:" << std::endl;
                for (const auto& m : homeMatches) {
                    std::cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
                }
                std::cout << "Partidos como visitante:" << std::endl;
                for (const auto& m : awayMatches) {
                    std::cout << m.id << ". " << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
                }
            }
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
            continue;
        }

        if ((choice == 1 || choice == 4) && results.empty()) {
            std::cout << "No se encontraron partidos." << std::endl;
        }
    }

    return 0;
}
