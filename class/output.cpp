/**
 * @file output.cpp
 * @brief Išvesties ir pagalbinių funkcijų įgyvendinimai.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <filesystem> 
#include "funkcijos.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::ofstream;
using std::to_string;
using std::filesystem::create_directories;

/**
 * @brief Išveda studentų sąrašą į konsolę.
 * @param studentai Studentų vektorius.
 * @param pasirink Galutinio balo skaičiavimo metodas (1 - vid., 2 - med.).
 */
void isvestEkr(const vector<Studentas> &studentai, int pasirink) {
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";
    
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    cout << "---------------------------------------------------------" << "\n";
    
    for (const auto &stud : studentai) {
        cout << stud << '\n';
    }
    cout << "\n\n";
}

/** @brief Apskaičiuoja ir nustato kiekvieno studento galutinį balą. */
void skaicGal(vector<Studentas> &studentai, int pasirink) {
    for (auto &stud : studentai) {
        stud.setGal(stud.galBalas(pasirink));
    }
}

/**
 * @brief Sugeneruoja atsitiktinį vardą/pavardę nurodytu ilgiu.
 * @param from Minimalus simbolių skaičius.
 * @param to Maksimalus simbolių skaičius.
 * @return Sugeneruotas tekstas.
 */
string rndVardas(int from, int to) {
    string vard;
    int raidSk = rand() % (to - from + 1) + from;

    vard += (char)(rand() % 26 + 65);
    for (int i=1; i<raidSk; i++) {
        vard += (char)(rand() % 26 + 97);
    }
    
    return vard;
}

/**
 * @brief Išsaugo studentų sąrašą į nurodytą failą.
 * @param studentai Studentų vektorius.
 * @param pasirink Galutinio balo skaičiavimo metodas.
 * @param failoPav Išeities failo pavadinimas.
 */
void isvestIFaila(const vector<Studentas> &studentai, int pasirink, string failoPav) {
    string failoKelias = "isvestis/" + failoPav;
    create_directories("isvestis");
    ofstream file(failoKelias);
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    file << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    file << "---------------------------------------------------------";
    
    for (const auto &stud : studentai) {
        file << '\n' << stud;
    }
}

/**
 * @brief Rūšiuoja studentus pagal pasirinkimą.
 * @param rusBudas 1-vardas, 2-pavardė, 3-galutinis balas
 */
void rusiuok(vector<Studentas> &studentai, int rusBudas) {
    if (rusBudas == 1) {
        sort(studentai.begin(), studentai.end(), compare);
    }
    else if (rusBudas == 2) {
        sort(studentai.begin(), studentai.end(), comparePagalPavarde);
    }
    else {
        sort(studentai.begin(), studentai.end(), comparePagalGal);
    }
}

/**
 * @brief Sugeneruoja įvesties failą su atsitiktiniais duomenimis.
 * @param studSk Studentų skaičius.
 * @param pazSk Pažymių skaičius kiekvienam studentui.
 * @return Sugeneruoto failo kelias.
 */
string kurkFaila(int studSk, int pazSk) {
    string failoPav = "stud" + to_string(studSk) + ".txt";
    string failoKelias = "ivestis/" + failoPav;
    create_directories("ivestis");
    ofstream file(failoKelias);

    file << left << setw(16) << "Vardas" << right << setw(16) << "Pavarde" << setw(13) << " ";
    for (int i=0; i<pazSk; i++) {
        file << right << setw(10) << "ND" + to_string(i + 1);
    }
    file << right << setw(10) << "Egz." << "\n"; 

    for (int i=0; i<studSk; i++) {
        file << left << setw(16) << "Vardas" + to_string(i + 1) << right << setw(16) << "Pavarde" + to_string(i + 1);
        file << setw(13) << " ";
        for (int j=0; j<pazSk; j++) {
            file << right << setw(10) << to_string(rand() % 10 + 1);
        }
        file << right << setw(10) << to_string(rand() % 10 + 1) << "\n";
    }

    return failoKelias;
}

/** @brief Atskiria silpniausius studentus į atskirą vektorių `vargsiukai`. */
void skirstyk(vector<Studentas> &studentai, vector<Studentas> &vargsiukai) {
    auto mid = std::stable_partition(studentai.begin(), studentai.end(), [](const Studentas &s){ return s.getGal() < 5; });

    vargsiukai.assign(studentai.begin(), mid);
    studentai.erase(studentai.begin(), mid);
}