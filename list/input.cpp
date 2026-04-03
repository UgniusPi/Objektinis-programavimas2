#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <filesystem> 
#include <list>
#include "funkcijos.h"

using std::string;
using std::vector;
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
using std::list;

void ivestEkr(list<Studentas> &studentai, bool rndPaz, bool rndVard) {
    int studSk = validInput("Iveskite studentu skaiciu: ");
    cout << "\n";
    
    while (true) {
        for (int i=0; i<studSk; i++) {
            Studentas naujasStud;
            int tarpSk;
            
            if (rndVard) {
                naujasStud.vard = rndVardas(4, 10);
                naujasStud.pav = rndVardas(6, 12);
                cout << "Automatiskai sugeneruoto " << to_string(i + 1) << " is " << to_string(studSk) << " studento vardas ir pavarde:\n";
                cout << left << setw(16) << naujasStud.vard << left << setw(20) << naujasStud.pav << "\n";
            }
            else {
                naujasStud.vard = validLength(15, "Iveskite " + to_string(i + 1) + " is " + to_string(studSk) + " studento varda (iki 15 raidziu): ");
                naujasStud.pav = validLength(20, "Iveskite " + to_string(i + 1) + " is " + to_string(studSk) + " studento pavarde (iki 20 raidziu): ");
            }
    
            if (rndPaz) {
                tarpSk = rand() % 16;
                cout << "Automatiskai sugeneruoti tarpiniai pazymiai ir egzamino rezultatas:\n";
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = rand() % 11;
                    naujasStud.tarp.push_back(tarpPaz);
                    cout << tarpPaz << " ";
                }
                
                naujasStud.egz = rand() % 11;
                cout << "\n" << naujasStud.egz << "\n\n";
            }
            else {
                tarpSk = validInput("Iveskite tarpiniu pazymiu skaiciu: ");
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = validRange(0, 10, "Iveskite " + to_string(j + 1) + " pazymi is " + to_string(tarpSk) + ": ");
                    naujasStud.tarp.push_back(tarpPaz);
                }
                
                naujasStud.egz = validInput("Iveskite egzamino rezultata: ");
                cout << "\n";
            }
            
            studentai.push_back(naujasStud);
        } 
        
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

void ivestIsFailo(list<Studentas> &studentai, string failoKelias,  bool &klaida) {
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

    getline(buffer, line);
    while (getline(buffer, line)) {
        stringstream ss(line);
        Studentas naujasStud;
        string tmp;

        if (ss >> tmp) {
            naujasStud.vard = tmp;
        }
        else {
            continue;
        }

        if (ss >> tmp) {
            naujasStud.pav = tmp;
        }
        else {
            cout << "Klaidingi duomenys faile!";
            klaida = true;
            return;
        }

        vector<int> visiPaz;
        while (ss >> tmp) {
            if (!isInt(tmp)) {
                cout << "Klaidingi duomenys faile!";
                klaida = true;
                return;   
            }
            int tmpPaz = stoi(tmp);
            visiPaz.push_back(tmpPaz);
        }

        if (visiPaz.empty()) {
            cout << "Klaidingi duomenys faile!";
            klaida = true;
            return;
        }

        naujasStud.egz = visiPaz.back();
        visiPaz.pop_back();
        naujasStud.tarp = visiPaz;

        studentai.push_back(naujasStud);
    }
}

string klauskFailo(bool &klaida) {
    vector<path> failuPav;
    klaida = false;

    try {
        for (auto p: directory_iterator("ivestis")) {
            failuPav.push_back(p.path());
        }
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
