/**
 * @file input.cpp (my_vector kopija)
 */

#include <iostream>
#include "Vector.h"
#include <string>
#include <chrono>
#include <cctype>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <utility>
#include "funkcijos.h"

using std::string;
using mystl::Vector;
using std::cout;
using std::cin;
using std::left;
using std::setw;
using std::stoi;
using std::getline;
using std::to_string;
using std::ifstream;
using std::stringstream;
using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::exception;

void ivestEkr(Vector<Studentas> &studentai, bool rndPaz, bool rndVard) {
    int studSk = validInput("Iveskite studentu skaiciu: ");
    cout << "\n";
    using std::chrono::steady_clock;
    using std::chrono::duration;

    while (true) {
        auto startFill = steady_clock::now();
        for (int i=0; i<studSk; i++) {
            Studentas naujasStud;
            int tarpSk;
            
            if (rndVard) {
                naujasStud.setVard(rndVardas(4, 10));
                naujasStud.setPav(rndVardas(6, 12));
                cout << "Automatiskai sugeneruoto " << to_string(i + 1) << " is " << to_string(studSk) << " studento vardas ir pavarde:\n";
                cout << left << setw(16) << naujasStud.getVard() << left << setw(20) << naujasStud.getPav() << "\n";            }
            else {
                naujasStud.setVard(validLength(15, "Iveskite " + to_string(i + 1) + " is " + to_string(studSk) + " studento varda (iki 15 raidziu): "));
                naujasStud.setPav(validLength(20, "Iveskite " + to_string(i + 1) + " is " + to_string(studSk) + " studento pavarde (iki 20 raidziu): "));
            }
    
            if (rndPaz) {
                tarpSk = rand() % 16;
                cout << "Automatiskai sugeneruoti tarpiniai pazymiai ir egzamino rezultatas:\n";
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = rand() % 11;
                    naujasStud.addTarp(tarpPaz);
                    cout << tarpPaz << " ";
                }
                
                naujasStud.setEgz(rand() % 11);
                cout << "\n" << naujasStud.getEgz() << "\n\n";
            }
            else {
                tarpSk = validInput("Iveskite tarpiniu pazymiu skaiciu: ");
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = validRange(0, 10, "Iveskite " + to_string(j + 1) + " pazymi is " + to_string(tarpSk) + ": ");
                    naujasStud.addTarp(tarpPaz);
                }
                
                naujasStud.setEgz(validInput("Iveskite egzamino rezultata: "));
                cout << "\n";
            }
            
            studentai.push_back(std::move(naujasStud));
        } 
        auto endFill = steady_clock::now();
        duration<double> fillElapsed = endFill - startFill;
        cout << "ivestEkr: studentu sukureme " << studSk << " irasu per " << fillElapsed.count() << " s\n";
        
        studSk = validInput("Iveskite papildomu studentu skaiciu (jei nenorite prideti studentu, iveskite 0): ");
        cout << "\n";
        if (studSk == 0) break;
    }
}

bool isInt(string inp) {
    for (int i=0; i<inp.length(); i++) {
        if (!isdigit(inp[i])) {
            return false;   
        }
    }
    
    return inp.length() != 0 && inp.length() <= 10;
}

int validInput(string prompt) {
    string inp;
    
    cout << prompt;
    getline(cin, inp);
    while (!isInt(inp)) {
        cout << "Ivesti duomenys turi buti sveikasis neneigiamas skaicius! Bandykite is naujo.\n" << prompt;
        getline(cin, inp);
    }
    
    return stoi(inp);
}

int validRange(int from, int to, string prompt) {
    int inp = validInput(prompt);
    while (inp < from || inp > to) {
        cout << "Ivestas skaicius turi buti nuo " << from << " iki " << to << "! Bandykite is naujo.\n";
        inp = validInput(prompt);
    }
    
    return inp;
}

string validLength(int maxLength, string prompt) {
    string inp;
    
    cout << prompt;
    getline(cin, inp);
    while (inp.length() > maxLength) {
        cout << "Ivestas tekstas virsija " + to_string(maxLength) + " raidziu limita! Bandykite is naujo.\n";
        cout << prompt;
        getline(cin, inp);    
    }
    
    if (inp.length() == 0) {
        inp = "Nenurodyta";    
    }
    
    return inp;
}

void klauskEigos(bool &testi, Nustatymai &nustatymai) {
    int eiga;
    testi = true;
    nustatymai.rndPaz = false;
    nustatymai.rndVard = false;
    nustatymai.ivestSaltinis = 1;

    cout << "Pasirinkite programos eiga.\n";
    cout << "1. Studentu duomenis skaityti is failo.\n";
    cout << "2. Visus studentu duomenis ivesti ranka.\n";
    cout << "3. Automatiskai generuoti studentu pazymius.\n";
    cout << "4. Automatiskai generuoti studentu vardus, pavardes ir pazymius.\n";
    cout << "5. Baigti darba.\n";
    eiga = validRange(1, 5, "Pasirinkimas: ");
    cout << "\n";
    
    if (eiga == 1) {
        nustatymai.ivestSaltinis = 2;
    }
    else if (eiga == 3) {
        nustatymai.rndPaz = true;   
    }
    else if (eiga == 4) {
        nustatymai.rndPaz = true;
        nustatymai.rndVard = true;
    }
    else if (eiga == 5) {
        testi = false;
        return;
    }

    cout << "Pasirinkite isvesties buda.\n";
    cout << "1. Isvesti i ekrana.\n";
    cout << "2. Issaugoti i faila.\n";
    nustatymai.isvestVieta = validRange(1, 2, "Pasirinkimas: ");
    cout << "\n";

    cout << "Pasirinkite galutinio rezultato skaiciavimo buda.\n";
    cout << "1. Naudojant vidurki.\n";
    cout << "2. Naudojant mediana.\n";
    nustatymai.pasirink = validRange(1, 2, "Pasirinkimas: ");
    cout << "\n";

    cout << "Pasirinkite studentu rusiavimo kriteriju.\n";
    cout << "1. Vardas\n";
    cout << "2. Pavarde\n";
    cout << "3. Galutinis balas\n";
    nustatymai.rusBudas = validRange(1, 3, "Pasirinkimas: ");
    cout << "\n";

    return;
}

void ivestIsFailo(Vector<Studentas> &studentai, string failoKelias,  bool &klaida) {
    ifstream file(failoKelias);
    stringstream buffer;
    string line;
    klaida = false;

    if (!file) {
        cout << "Klaida bandant atidaryti ivesties faila!";
        klaida = true;
        return;
    }

    buffer << file.rdbuf();
    // skip header line (if present)
    if (!getline(buffer, line)) return;
    using std::chrono::steady_clock;
    using std::chrono::duration;
    auto startRead = steady_clock::now();
    while (getline(buffer, line)) {
        stringstream ss(line);
        Studentas naujasStud;

        if (ss >> naujasStud) {
            studentai.push_back(std::move(naujasStud));
        } else {
            cout << "Klaidingi duomenys faile!";
            klaida = true;
            return;
        }
    }
    auto endRead = steady_clock::now();
    duration<double> readElapsed = endRead - startRead;
    cout << "ivestIsFailo: nuskaitymas ir push_back uztruko: " << readElapsed.count() << " s\n";
}

string klauskFailo(bool &klaida) {
    Vector<path> failuPav;
    klaida = false;
    try {
        using std::chrono::steady_clock;
        using std::chrono::duration;
        auto startDir = steady_clock::now();
        for (auto p: directory_iterator("ivestis")) {
            failuPav.push_back(p.path());
        }
        auto endDir = steady_clock::now();
        duration<double> dirElapsed = endDir - startDir;
        cout << "klauskFailo: nuskaityti katalogo failai uztruko: " << dirElapsed.count() << " s\n";
    }
    catch (exception &e) {
        cout << "Klaida skaitant aplanka:\n" << e.what() << "\n";
        klaida = true;
        return "";
    }
    
    cout << "Pasirinkite ivesties faila.\n";
    for (int i=0; i<failuPav.size(); i++) {
        cout << to_string(i + 1) << ". " << failuPav.at(i).filename().string() << "\n";
    }
    cout << to_string(failuPav.size() + 1) << ". " << "Sugeneruoti faila\n";
    int ivestFailas = validRange(1, failuPav.size() + 1, "Pasirinkimas: ");
    cout << "\n";

    if (ivestFailas == failuPav.size() + 1) {
        int studSk = validInput("Iveskite studentu skaiciu: ");
        int pazSk = validInput("Iveskite pazymiu skaiciu: ");
        
        return kurkFaila(studSk, pazSk);
    }
    else {
        return failuPav.at(ivestFailas - 1).string();
    }
    
}
