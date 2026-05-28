/**
 * @file strukturos.h
 * @brief Pagalbinės struktūros programai.
 */

#ifndef STRUKTUROS_H
#define STRUKTUROS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief Programos nustatymai ir vartotojo pasirinkimai.
 *
 * @var ivestSaltinis 1 - įvestis iš ekrano, 2 - iš failo
 * @var isvestVieta 1 - išvesti į ekraną, 2 - į failą
 * @var pasirink Galutinio balo skaičiavimo būdas (1 - vidurkis, 2 - mediana)
 * @var rusBudas Studentų rikiavimo būdas (1 - vardas, 2 - pavardė, 3 - galutinis balas)
 * @var rndPaz Ar generuoti atsitiktinius pažymius
 * @var rndVard Ar generuoti atsitiktinius vardus/pavardes
 */
struct Nustatymai {
    int ivestSaltinis;
    int isvestVieta;
    int pasirink;
    int rusBudas;
    bool rndPaz;
    bool rndVard;
};

#endif