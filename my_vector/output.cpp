/**
 * @file output.cpp (my_vector kopija)
 */

#include <iostream>
#include "Vector.h"
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <chrono>
#include "funkcijos.h"

using std::string;
using mystl::Vector;
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

void isvestEkr(const Vector<Studentas> &studentai, int pasirink) {
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";
    
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    cout << "---------------------------------------------------------" << "\n";
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    for (const auto &stud : studentai) {
        cout << stud << '\n';
    }
    auto t1 = steady_clock::now();
    duration<double> elapsed = t1 - t0;
    cout << "isvestEkr: isvedimo iteracija uztruko: " << elapsed.count() << " s\n";
    cout << "\n\n";
}

void skaicGal(Vector<Studentas> &studentai, int pasirink) {
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    for (auto &stud : studentai) {
        stud.setGal(stud.galBalas(pasirink));
    }
    auto t1 = steady_clock::now();
    duration<double> elapsed = t1 - t0;
    cout << "skaicGal: apskaiciavimo laikas: " << elapsed.count() << " s\n";
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

void isvestIFaila(const Vector<Studentas> &studentai, int pasirink, string failoPav) {
    string failoKelias = "isvestis/" + failoPav;
    create_directories("isvestis");
    ofstream file(failoKelias);
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    file << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    file << "---------------------------------------------------------";
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    for (const auto &stud : studentai) {
        file << '\n' << stud;
    }
    auto t1 = steady_clock::now();
    duration<double> elapsed = t1 - t0;
    cout << "isvestIFaila: isvedimas i faila uztruko: " << elapsed.count() << " s\n";
}

void rusiuok(Vector<Studentas> &studentai, int rusBudas) {
    if (rusBudas == 1) {
        std::sort(studentai.begin(), studentai.end(), compare);
    }
    else if (rusBudas == 2) {
        std::sort(studentai.begin(), studentai.end(), comparePagalPavarde);
    }
    else {
        std::sort(studentai.begin(), studentai.end(), comparePagalGal);
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

    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    for (int i=0; i<studSk; i++) {
        file << left << setw(16) << "Vardas" + to_string(i + 1) << right << setw(16) << "Pavarde" + to_string(i + 1);
        file << setw(13) << " ";
        for (int j=0; j<pazSk; j++) {
            file << right << setw(10) << to_string(rand() % 10 + 1);
        }
        file << right << setw(10) << to_string(rand() % 10 + 1) << "\n";
    }
    auto t1 = steady_clock::now();
    duration<double> elapsed = t1 - t0;
    cout << "kurkFaila: failo generavimas uztruko: " << elapsed.count() << " s\n";

    return failoKelias;
}

void skirstyk(Vector<Studentas> &studentai, Vector<Studentas> &vargsiukai) {
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto t0 = steady_clock::now();
    auto mid = std::stable_partition(studentai.begin(), studentai.end(), [](const Studentas &s){ return s.getGal() < 5; });
    auto t1 = steady_clock::now();
    duration<double> partElapsed = t1 - t0;

    auto t2 = steady_clock::now();
    // mystl::Vector doesn't have range assign; copy elements manually
    vargsiukai.clear();
    for (auto it = studentai.begin(); it != mid; ++it) {
        vargsiukai.push_back(*it);
    }
    auto t3 = steady_clock::now();
    duration<double> assignElapsed = t3 - t2;

    auto t4 = steady_clock::now();
    studentai.erase(studentai.begin(), mid);
    auto t5 = steady_clock::now();
    duration<double> eraseElapsed = t5 - t4;

    cout << "skirstyk: partition=" << partElapsed.count() << " s, assign=" << assignElapsed.count() << " s, erase=" << eraseElapsed.count() << " s\n";
}
