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

void isvestEkr(const vector<Studentas> &studentai, int pasirink) {
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";
    
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    cout << "---------------------------------------------------------" << "\n";
    
    for (const auto &stud : studentai) {
        cout << left << setw(21) << stud.getPav() << left << setw(16) << stud.getVard() << left << setw(20) << fixed << setprecision(2) << stud.getGal() << "\n";
    }
    cout << "\n\n";
}

void skaicGal(vector<Studentas> &studentai, int pasirink) {
    for (auto &stud : studentai) {
        stud.setGal(stud.galBalas(pasirink));
    }
}

string rndVardas(int from, int to) {
    string vard;
    int raidSk = rand() % (to - from + 1) + from;

    vard += (char)(rand() % 26 + 65);
    for (int i=1; i<raidSk; i++) {
        vard += (char)(rand() % 26 + 97);
    }
    
    return vard;
}

void isvestIFaila(const vector<Studentas> &studentai, int pasirink, string failoPav) {
    string failoKelias = "isvestis/" + failoPav;
    create_directories("isvestis");
    ofstream file(failoKelias);
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    file << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    file << "---------------------------------------------------------";
    
    for (const auto stud : studentai) {
        file << '\n' << stud;
    }
}

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

void skirstyk(vector<Studentas> &studentai, vector<Studentas> &vargsiukai) {
    auto mid = std::stable_partition(studentai.begin(), studentai.end(), [](const Studentas &s){ return s.getGal() < 5; });

    vargsiukai.assign(studentai.begin(), mid);
    studentai.erase(studentai.begin(), mid);
}