#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "funkcijos.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main() {
    srand(time(0));

    while (true) {
        vector<Studentas> studentai, vargsiukai;
        Nustatymai nustatymai;

        bool testi, klaida;
        
        klauskEigos(testi, nustatymai);
        if (!testi) break;

        if (nustatymai.ivestSaltinis == 1) {
            ivestEkr(studentai, nustatymai.rndPaz, nustatymai.rndVard);
        }
        else {
            string failoKelias = klauskFailo(klaida);
            if (klaida) return 1;

            cout << "Skaitomas failas...\n";
            auto start = high_resolution_clock::now();
            ivestIsFailo(studentai, failoKelias, klaida);
            auto end = high_resolution_clock::now();
            duration<double> elapsed = end - start;
            cout << "Duomenu nuskaitymas is failo i konteineri uztruko: " << elapsed.count() << "\n";
            if (klaida) return 1;
        }
        
        cout << "Skaiciuojami studentu galutiniai balai...\n";
        skaicGal(studentai, nustatymai.pasirink);

        cout << "Rusiuojami studentai...\n";
        auto start = high_resolution_clock::now();
        rusiuok(studentai, nustatymai.rusBudas);
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        cout << "Studentu rusiavimas konteineryje uztruko: " << elapsed.count() << "\n";

        start = high_resolution_clock::now();
        skirstyk(studentai, vargsiukai);
        end = high_resolution_clock::now();
        elapsed = end - start;
        cout << "Studentu skirstymas i grupes uztruko: " << elapsed.count() << "\n";

        if (nustatymai.isvestVieta == 1) {
            isvestEkr(studentai, nustatymai.pasirink);
        }
        else {
            cout << "Rezultatas rasomas i failus...\n";
            isvestIFaila(vargsiukai, nustatymai.pasirink, "vargsiukai.txt");
            isvestIFaila(studentai, nustatymai.pasirink, "galvociai.txt");
            cout << "\n\n";
        }
    }
    
    cout << "Programa sekmingai uzsidare.";
    return 0;
}

