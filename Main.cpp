#include "futbol.h"
#include <iostream>

int main() {
    SoccerDB db;

    //Crea los equipos
    Team team1("Barcelona");
    Team team2("Real Madrid");
    Team team3("Atletico Madrid");

    //Crea los Partidos
    Match match1(team1, team2, "2025-10-04", "20:00", "LaLiga");
    Match match2(team3, team1, "2025-10-18", "18:00", "LaLiga");
    Match match3(team2, team3, "2025-10-12", "16:00", "LaLiga");

    //Agrega los Partidos
    db.addMatch(match1);
    db.addMatch(match2);
    db.addMatch(match3);

    //Mostrar los partidos
    std::cout << "Partidos:" << std::endl;
    for (const auto& m : db.getMatches()) {
        std::cout << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
    }

    //Busqueda
    int choice;
    std::string searchValue;
    std::vector<Match> results;

    std::cout << "\nOpciones:" << std::endl;
    std::cout << "1. Buscar por Equipo" << std::endl;
    std::cout << "2. Buscar por Fecha" << std::endl;
    std::cout << "3. Buscar por Hora" << std::endl;
    std::cout << "4. Buscar por Liga" << std::endl;
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
            std::cout << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
        }
    } else if (choice == 2) {
        db.sortByDate();
        std::cout << "Partidos ordenados por fecha:" << std::endl;
        for (const auto& m : db.getMatches()) {
            std::cout << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
        }
    } else if (choice == 3) {
        db.sortByHour();
        std::cout << "Partidos ordenados por hora:" << std::endl;
        for (const auto& m : db.getMatches()) {
            std::cout << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
        }
    } else if (choice == 4) {
        std::cout << "Ingrese liga: ";
        std::cin.ignore(); 
        std::getline(std::cin, searchValue);
        results = db.searchByLeague(searchValue);
        std::sort(results.begin(), results.end(), [](const Match& a, const Match& b) {
            return a.date < b.date;
        });
        std::cout << "Resultados de busqueda:" << std::endl;
        for (const auto& m : results) {
            std::cout << m.home.name << " vs " << m.away.name << " (" << m.date << ", " << m.hour << ") (" << m.league << ")" << std::endl;
        }
    } else {
        return 0;
    }

    if ((choice == 1 || choice == 4) && results.empty()) {
        std::cout << "No se encontraron partidos." << std::endl;
    }

    return 0;
}
